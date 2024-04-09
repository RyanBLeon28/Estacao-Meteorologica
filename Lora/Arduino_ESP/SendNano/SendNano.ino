/* 
  
  The tachometer's code to get RPM was made by InterlinkKnight. Last update: 05/23/2019
  
  To find all of Weather Station:
    GitHub: https://github.com/RyanBLeon28/Estacao-Meteorologica
    Last update: 08/04/2024
*/

// ====================================================================================================================================
// --- Including libraries ---
#include "Wire.h"
#include <Adafruit_Sensor.h>            
#include <Adafruit_BMP280.h>
#include "DHT.h"
#include "EBYTE.h"
#include <SoftwareSerial.h>

// ====================================================================================================================================
// --- Pins declaration of Lora ---
#define PIN_RX 7                       // TX Lora module
#define PIN_TX 3                       // RX Lora module
#define PIN_M0 4                       // M0 Lora module
#define PIN_M1 5                       // M1 Lora module
#define PIN_AX 6                       // AUX Lora module

#define DHTPIN 8                       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11                  // DHT 11
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;                   // SDA - A4  ; SCL - A5 (I2C)
const int ledPin = 11;                 // Digital pin connected to the LED

// ====================================================================================================================================
// --- Interval to send data by LoRa module ---
unsigned long previousMillis = 0;   // Armazena o tempo do último print
const long interval = 5000; 
// ====================================================================================================================================
// --- Struct with station data ---
struct DATA {
  float Temp;
  float Humid;
  float Press;
  float Altitude;
  float Speed;
};

int Chan;
DATA StationA;
unsigned long Last;

// you will need to define the pins to create the serial port
SoftwareSerial ESerial(PIN_RX, PIN_TX);

// create the transceiver object, passing in the serial and pins
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

// ====================================================================================================================================
const byte PulsesPerRevolution = 3; 
const unsigned long ZeroTimeout = 500000; 
// Calibration for smoothing RPM:
const byte numReadings = 10;  // Number of samples for smoothing. The higher, the more smoothing, but it's going to
                             // react slower to changes. 1 = no smoothing. Default: 2.

volatile unsigned long LastTimeWeMeasured;  // Stores the last time we measured a pulse so we can calculate the period.
volatile unsigned long PeriodBetweenPulses = ZeroTimeout+1000;  // Stores the period between pulses in microseconds.
                       // It has a big number so it doesn't start with 0 which would be interpreted as a high frequency.
volatile unsigned long PeriodAverage = ZeroTimeout+1000;  // Stores the period between pulses in microseconds in total, if we are taking multiple pulses.
                       // It has a big number so it doesn't start with 0 which would be interpreted as a high frequency.
unsigned long FrequencyRaw;  // Calculated frequency, based on the period. This has a lot of extra decimals without the decimal point.
unsigned long FrequencyReal;  // Frequency without decimals.
unsigned long RPM;  // Raw RPM without any processing.
unsigned int PulseCounter = 1;  // Counts the amount of pulse readings we took so we can average multiple pulses before calculating the period.

unsigned long PeriodSum; // Stores the summation of all the periods to do the average.

unsigned long LastTimeCycleMeasure = LastTimeWeMeasured;  // Stores the last time we measure a pulse in that cycle.
                                    // We need a variable with a value that is not going to be affected by the interrupt
                                    // because we are going to do math and functions that are going to mess up if the values
                                    // changes in the middle of the cycle.
unsigned long CurrentMicros = micros();  // Stores the micros in that cycle.
                                         // We need a variable with a value that is not going to be affected by the interrupt
                                         // because we are going to do math and functions that are going to mess up if the values
                                         // changes in the middle of the cycle.

// We get the RPM by measuring the time between 2 or more pulses so the following will set how many pulses to
// take before calculating the RPM. 1 would be the minimum giving a result every pulse, which would feel very responsive
// even at very low speeds but also is going to be less accurate at higher speeds.
// With a value around 10 you will get a very accurate result at high speeds, but readings at lower speeds are going to be
// farther from eachother making it less "real time" at those speeds.
// There's a function that will set the value depending on the speed so this is done automatically.
unsigned int AmountOfReadings = 1;

unsigned int ZeroDebouncingExtra;  // Stores the extra value added to the ZeroTimeout to debounce it.
                                   // The ZeroTimeout needs debouncing so when the value is close to the threshold it
                                   // doesn't jump from 0 to the value. This extra value changes the threshold a little
                                   // when we show a 0.

// Variables for smoothing tachometer:
unsigned long readings[numReadings];  // The input.
unsigned long readIndex;  // The index of the current reading.
unsigned long total;  // The running total.
unsigned long average;  // The RPM value after applying the smoothing.

void Pulse_Event()  // The interrupt runs this to calculate the period between pulses:
{
  PeriodBetweenPulses = micros() - LastTimeWeMeasured;  // Current "micros" minus the old "micros" when the last pulse happens.
                                                        // This will result with the period (microseconds) between both pulses.
                                                        // The way is made, the overflow of the "micros" is not going to cause any issue.
  LastTimeWeMeasured = micros();  // Stores the current micros so the next time we have a pulse we would have something to compare with.
  if(PulseCounter >= AmountOfReadings)  // If counter for amount of readings reach the set limit:
  {
    PeriodAverage = PeriodSum / AmountOfReadings;  // Calculate the final period dividing the sum of all readings by the
                                                   // amount of readings to get the average.
    PulseCounter = 1;  // Reset the counter to start over. The reset value is 1 because its the minimum setting allowed (1 reading).
    PeriodSum = PeriodBetweenPulses;  // Reset PeriodSum to start a new averaging operation
    // Change the amount of readings depending on the period between pulses.
    // To be very responsive, ideally we should read every pulse. The problem is that at higher speeds the period gets
    // too low decreasing the accuracy. To get more accurate readings at higher speeds we should get multiple pulses and
    // average the period, but if we do that at lower speeds then we would have readings too far apart (laggy or sluggish).
    // To have both advantages at different speeds, we will change the amount of readings depending on the period between pulses.
    // Remap period to the amount of readings:
    int RemapedAmountOfReadings = map(PeriodBetweenPulses, 40000, 5000, 1, 10);  // Remap the period range to the reading range.
    // 1st value is what are we going to remap. In this case is the PeriodBetweenPulses.
    // 2nd value is the period value when we are going to have only 1 reading. The higher it is, the lower RPM has to be to reach 1 reading.
    // 3rd value is the period value when we are going to have 10 readings. The higher it is, the lower RPM has to be to reach 10 readings.
    // 4th and 5th values are the amount of readings range.
    RemapedAmountOfReadings = constrain(RemapedAmountOfReadings, 1, 10);  // Constrain the value so it doesn't go below or above the limits.
    AmountOfReadings = RemapedAmountOfReadings;  // Set amount of readings as the remaped value.
  }
  else
  {
    PulseCounter++;  // Increase the counter for amount of readings by 1.
    PeriodSum = PeriodSum + PeriodBetweenPulses;  // Add the periods so later we can average.
  }
}

void setup() {
  Serial.begin(9600);
  // ====================================================================================================================================
  // Define o pino do LED como saída
  pinMode(ledPin, OUTPUT);
  // ====================================================================================================================================
  ESerial.begin(9600);
  Transceiver.init();
  Chan = 23;
  Transceiver.SetChannel(Chan);
  Transceiver.SetAddressH(0xAA);
  Transceiver.SetAddressL(0xAA);
  Transceiver.PrintParameters();
  // ====================================================================================================================================
  // Teste BPM280
  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões.")); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  // ====================================================================================================================================
  // Teste DHT11
  //Serial.println(F("DHTxx test!"));
  delay(100);
  dht.begin();
  // ====================================================================================================================================
  attachInterrupt(digitalPinToInterrupt(2), Pulse_Event, RISING);  // Enable interruption pin 2 when going from LOW to HIGH.
  
  // ====================================================================================================================================
  // Setup is ready
  Serial.println("Setup stationA");
  delay(1000); 
}

void loop() {
  // ====================================================================================================================================
  unsigned long currentMillis = millis(); // Obtém o tempo atual

  LastTimeCycleMeasure = LastTimeWeMeasured;  // Store the LastTimeWeMeasured in a variable.
  CurrentMicros = micros();  // Store the micros() in a variable.

  if(CurrentMicros < LastTimeCycleMeasure)
  {
    LastTimeCycleMeasure = CurrentMicros;
  }
  FrequencyRaw = 10000000000 / PeriodAverage;  // Calculate the frequency using the period between pulses.
  // Detect if pulses stopped or frequency is too low, so we can show 0 Frequency:
  if(PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra)
  {  // If the pulses are too far apart that we reached the timeout for zero:
    FrequencyRaw = 0;  // Set frequency as 0.
    ZeroDebouncingExtra = 2000;  // Change the threshold a little so it doesn't bounce.
  }
  else
  {
    ZeroDebouncingExtra = 0;  // Reset the threshold to the normal value so it doesn't bounce.
  }
  FrequencyReal = FrequencyRaw / 10000;  // Get frequency without decimals.
  
  // Calculate the RPM:
  RPM = FrequencyRaw / PulsesPerRevolution * 60;  // Frequency divided by amount of pulses per revolution multiply by
                                                  // 60 seconds to get minutes.
  RPM = RPM / 10000;  // Remove the decimals.  
  total = total - readings[readIndex];  // Advance to the next position in the array.
  readings[readIndex] = RPM;  // Takes the value that we are going to smooth.
  total = total + readings[readIndex];  // Add the reading to the total.
  readIndex = readIndex + 1;  // Advance to the next position in the array.

  if (readIndex >= numReadings)  // If we're at the end of the array:
  {
    readIndex = 0;  // Reset array index.
  }
  // Calculate the average:
  average = total / numReadings;
  // (2*3,14*average) / 60 = 0.420973416
  //float freqAng = (2*3,14*average) / 60
  // Equação da reta da regressão linear: [0.17117843]x + 0.19744649996588137, onde x é freq angular
  float freqAngX = 0.017916676*average; 
  float vel = freqAngX + 0.19744649996588137;
  //float vel = ((0.17117843)((0.104667*average)) + 0.19744649996588137;
  
  // ====================================================================================================================================
  // Lora comunication
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  
    // measure some data and save to the structure
    StationA.Temp = (float(dht.readTemperature()) + float(bmp.readTemperature()) ) / 2;
    StationA.Humid = float(dht.readHumidity());
    StationA.Press =  bmp.readPressure()/100;
    StationA.Altitude = bmp.readAltitude(1013.25);
    StationA.Speed = vel; // m/s
    Transceiver.SendStruct(&StationA, sizeof(StationA));
    digitalWrite(ledPin, HIGH);
    
    Serial.println();
    Serial.println("    Enviado:  "); 
    Serial.print("Temperature: "); Serial.print(StationA.Temp);Serial.println(" ºC");
    Serial.print("Humidy:      "); Serial.print(StationA.Humid);Serial.println(" %");
    Serial.print("Press:     "); Serial.print(StationA.Press);Serial.println(" Pa");
    Serial.print("Altitude:   "); Serial.print(StationA.Altitude);Serial.println(" m");
    Serial.print("Wind speed:  "); Serial.print(StationA.Speed);Serial.println(" m/s");
    Serial.print("-------------------------------------");
    delay(300);
    digitalWrite(ledPin, LOW);
  }

  delay(100);
}
