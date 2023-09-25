#include <Wire.h>
#include "WiFi.h"
#include <ESPAsyncWebSrv.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "DHT.h"


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Responsavel pelo Sensor Hall
const byte PulsesPerRevolution = 3; 
const unsigned long ZeroTimeout = 500000; 
// Calibration for smoothing RPM:
const byte numReadings = 100;  // Number of samples for smoothing. The higher, the more smoothing, but it's going to
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
    PeriodSum = PeriodBetweenPulses;  // Reset PeriodSum to start a new averaging operation.


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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Sensor BMP280
Adafruit_BMP280 bmp; // I2C Interface         G22 -- SCL ; G21 SDA

//Sensor DHT11
#define DHTPIN 4   // Pino DHT
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Rede e senha do Wifi
//const char* ssid     = "VETORIAL_135F";
//const char* password = "280273iara";
const char* ssid     = "Sala J13";
const char* password = "salaj132023";
// const char* ssid     = "A9";
// const char* password = "12345678";

//Cria um Assincrono Webserver na porta 80
AsyncWebServer server(80);

String readDHTTemperature() {
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

String readBMPTemperature() {
  float g = bmp.readTemperature();
  
  if (isnan(g)) {
    Serial.println("Failed to read from BMP sensor!");
    return "--";
  }
  else {
    Serial.println(g);
    return String(g);
  }
}

String readBMPPressure() {
  float d = bmp.readPressure()/100;
  
  if (isnan(d)) {
    Serial.println("Failed to read from BMP sensor!");
    return "--";
  }
  else {
    Serial.println(d);
    return String(d);
  }
}

String readBMPAltitude() {
  float e = bmp.readAltitude(1012);
  
  if (isnan(e)) {
    Serial.println("Failed to read from BMP sensor!");
    return "--";
  }
  else {
    Serial.println(e);
    return String(e);
  }
}

String readVeloc() {
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // The following is going to store the two values that might change in the middle of the cycle.
  // We are going to do math and functions with those values and they can create glitches if they change in the
  // middle of the cycle.
  LastTimeCycleMeasure = LastTimeWeMeasured;  // Store the LastTimeWeMeasured in a variable.
  CurrentMicros = micros();  // Store the micros() in a variable.

  // CurrentMicros should always be higher than LastTimeWeMeasured, but in rare occasions that's not true.
  // I'm not sure why this happens, but my solution is to compare both and if CurrentMicros is lower than
  // LastTimeCycleMeasure I set it as the CurrentMicros.
  // The need of fixing this is that we later use this information to see if pulses stopped.
  if(CurrentMicros < LastTimeCycleMeasure)
  {
    LastTimeCycleMeasure = CurrentMicros;
  }

  // Calculate the frequency:
  FrequencyRaw = 10000000000 / PeriodAverage;if(PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra)
  {  // If the pulses are too far apart that we reached the timeout for zero:
    FrequencyRaw = 0;  // Set frequency as 0.
    ZeroDebouncingExtra = 2000;  // Change the threshold a little so it doesn't bounce.
  }
  else
  {
    ZeroDebouncingExtra = 0;  // Reset the threshold to the normal value so it doesn't bounce.
  }
  FrequencyReal = FrequencyRaw / 10000;
  // Calculate the RPM:
  RPM = FrequencyRaw / PulsesPerRevolution * 60;  
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
  average = total / numReadings;  // The average value it's the smoothed result.



  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  Serial.print("Velocidade: ");
  //2*3,14*0.067 = 0.420973416
  Serial.print((RPM*0.420973416)/60);
  Serial.println(" m/s");
  
  float v = (RPM*0.420973416)/60;
  
  return String(v);
}


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Weather Station</title>

  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  
  <style>
    html {
     font-family: Arial;
     background-color: 'white';
     align-items: center;
    }
    h1 { 
      font-size: 28px; 
      text-align: center;
      align-items: center;
      background-color: #3498db;
      border-radius: 8px;
      width: 1300px;
      height: 70px;
      margin-top: 10px;
    }
    h2 { 
      font-size: 22px;
      margin-left:20px;
      background-color: #3498db;
      color: 'white';
      border-radius: 8px;
      width: 300px;
      text-align: center;
    }
    .units { 
      "font-size: 18px;
    }
    .dht-labels{
      "font-size: 18px;
      padding-bottom: 10px;
    }
    h4 { 
      font-size: 14px;
      margin-left:5px;
    }
    .div1{
      background-color: #5db8f5;
      border-radius: 8px;
      width: 250px;
      text-align: center;
      margin-top: 10px;
      margin-left:50px;
      font-size: 18px;
    }
  </style>
</head>
<body>
  <header>
    <img src="https://observatorio.furg.br/images/banners/bg-inicio-cupulas.png">
    <h1>Estacao Metereologica do Observatorio Furg</h1>
  </header>
  <h2>Dados da estacao:</h2>
    <div class="div1">
      <i class="fas fa-thermometer-half" style="color:#139135;"></i> 
      <span class="dht-labels">Temperatura..........</span> 
      <span id="temperature">%TEMPERATURE%</span>
      <sup class="units">&deg;C</sup>
    </div>
    <div class="div1">
      <i class="fas fa-thermometer-half" style="color:#139135;"></i> 
      <span class="dht-labels">Temperatura...........</span>
      <span id="TemperatureBMP">%TEMPERATUREBMP%</span>
      <sup class="units">&deg;C</sup>
    </div>
    <div class="div1">
      <i class="fas fa-tint" style="color:#139135;"></i>  
      <span class="dht-labels">Humidade...............</span>
      <span id="humidity">%HUMIDITY%</span>
      <sup class="units">&percnt;</sup>
    </div>
    <div class="div1">
      <i class="" style="color:#de0404;"></i> 
      <span class="dht-labels">Altitude.....................</span>
      <span id="Altitude">%ALTITUDEBMP%</span>
      <sup class="units">m</sup>
    </div>
    <div class="div1">
      <i class="" style="color:#de0404;"></i> 
      <span class="dht-labels">Pressao..............</span>
      <span id="Pressure">%PRESSUREBMP%</span>
      <sup class="units">hPa</sup>
    </div>
    <div class="div1">
      <i class="" style="color:#de0404;"></i> 
      <span class="dht-labels">Vel do Vento................</span>
      <span id="velocidade">%VELOCIDADE%</span>
      <sup class="units">km/h</sup>
    </div>
    <div class="div1">
      <i class="" style="color:#de0404;"></i> 
      <span class="dht-labels">Direcao do Vento................</span>
      <span id="Direcao">%Direcao%</span>
      <sup class="units">&deg;</sup>
    </div>
  
  <br>
  <br>
  <br>
  <br>
  <br>
  <br>

  <footer>
  <h4>&copy; 2023 Ryan de Leon. All rights reserved.</h4>
  </footer>
</body>

<script>1
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperatureBMP").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperatureBMP", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("pressureBMP").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/pressureBMP", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("altitudeBMP").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/altitudeBMP", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("velocidade").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/velocidade", true);
  xhttp.send();
}, 10000 ) ;

</script>
</html>)rawliteral";






// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  else if(var == "TEMPERATUREBMP"){
    return readBMPTemperature();
  }
  else if(var == "PRESSUREBMP"){
    return readBMPPressure();
  }
  else if(var == "ALTITUDEBMP"){
    return readBMPAltitude();
  }
  else if(var == "VELOCIDADE"){
    return readVeloc();
  }
  return String();
}

void setup(void) {

  Serial.begin(115200);
  
  // Inicia o Sensor Hall
  attachInterrupt(digitalPinToInterrupt(2), Pulse_Event, RISING);  // Enable interruption pin 2 when going from LOW to HIGH.

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });
  server.on("/temperatureBMP", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBMPTemperature().c_str());
  });
  server.on("/pressureBMP", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBMPPressure().c_str());
  });
  server.on("/altitudeBMP", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBMPAltitude().c_str());
  });
  server.on("/velocidade", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readVeloc().c_str());
  });

  // Start server
  server.begin();

  // //inicia o DHT
  dht.begin();

  //inicializa BMP280
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}



void loop(){

}