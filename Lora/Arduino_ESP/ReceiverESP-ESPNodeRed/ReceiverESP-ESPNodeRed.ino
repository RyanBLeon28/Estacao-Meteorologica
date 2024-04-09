#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "EBYTE.h"

/*
WARNING: IF USING AN ESP32
DO NOT USE THE PIN NUMBERS PRINTED ON THE BOARD
YOU MUST USE THE ACTUAL GPIO NUMBER
*/
#define PIN_RX 16   // Serial2 RX (connect this to the EBYTE Tx pin)
#define PIN_TX 17   // Serial2 TX pin (connect this to the EBYTE Rx pin)

#define PIN_M0 4    // D4 on the board (possibly pin 24)
#define PIN_M1 19   // D2 on the board (possibly called pin 22)
#define PIN_AX 18   // D15 on the board (possibly called pin 21)

#define SCREEN_WIDTH 128 // Largura do display em pixels
#define SCREEN_HEIGHT 64 // Altura do display em pixels

// ====================================================================================================================================
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ====================================================================================================================================
// --- Struct with station data
struct DATA {
  float Temp;
  float Humid;
  float Press;
  float Altitude;
  float Speed;
};

int Chan;
DATA StationA;
DATA StationB;
unsigned long Last;

// create the transceiver object, passing in the serial and pins
EBYTE Transceiver(&Serial2, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  // this init will set the pinModes for you
  Transceiver.init();

  // all these calls are optional but shown to give examples of what you can do

  // Serial.println(Transceiver.GetAirDataRate());
  // Serial.println(Transceiver.GetChannel());
  Transceiver.SetAddressH(0x01);
  Transceiver.SetAddressL(0x01);
  Chan = 23;
  Transceiver.SetChannel(Chan);
  // save the parameters to the unit,
  // Transceiver.SetPullupMode(1);
  // Transceiver.SaveParameters(PERMANENT);

  Transceiver.PrintParameters();

  //Wire.begin();
  
  // Inicialização do display OLED com endereço 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  Serial.println("Starting Reader");

  // Limpa o buffer do display
  display.clearDisplay();

  // Desenha alguns textos e formas geométricas
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0,0);     
  display.println("Station controladora");
  display.display();
  delay(1500);
  display.clearDisplay();
}

void loop() {
  if (Serial2.available()) {
    Transceiver.GetStruct(&StationA, sizeof(StationA));

    Serial.println();
    Serial.println("Received from StationA:  "); 
    Serial.print("Temperature: "); Serial.print(StationA.Temp);Serial.println(" ºC");
    Serial.print("Humidy:      "); Serial.print(StationA.Humid);Serial.println(" %");
    Serial.print("Press:     "); Serial.print(StationA.Press);Serial.println(" Pa");
    Serial.print("High:   "); Serial.print(StationA.Altitude);Serial.println(" m");
    Serial.print("wind speed:   "); Serial.print(StationA.Speed);Serial.println(" m/s");
    //Serial.println(Transceiver.GetAddressH());
    //Serial.print("Endereço: "); Serial.println(StationA.Adress);
    Serial.print("-------------------------------------");

    //Transceiver.GetStruct(&StationB, sizeof(StationB));
    Last = millis();
  }
  else {
    if ((millis() - Last) > 4000) {
      Serial.println();
      Serial.println("Searching data: ");
      Last = millis();
    }
  }
  // ====================================================================================================================================
  // --- Show data in display ---
  displayFunction(StationA.Temp, StationA.Humid, StationA.Speed, StationA.Altitude, StationA.Press);

  delay(100);
}

void displayFunction(float temp, float humid, float speed, float altitude, float press){
  display.clearDisplay();
  display.setCursor(40,0);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); 
  display.print("MASTER");

  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0,20);     
  display.print("T:"); display.print(temp); display.print("C");

  display.setCursor(70,20);     
  display.print("H: "); display.print(humid); display.println("%");
  
  display.setCursor(0,35);   
  display.print("S:"); display.print(speed); display.print("m/s");

  display.setCursor(70,35);     
  display.print("A:"); display.print(altitude); display.println("m");

  display.setCursor(0,50);     
  display.print("P:"); display.print(press); display.println("Pa");

  display.display();
}