#include <Adafruit_Sensor.h>           //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP280.h>           //INCLUSÃO DE BIBLIOTECA
#include "Wire.h"
Adafruit_BMP280 bmp; // I2C Interface

void setup()  {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));

  // if  (!bmp.begin()) {
  //   Serial.println(F("Could not find a valid BMP280 sensor,  check wiring!"));
  //   while (1);
  // }

  // /* Default settings from datasheet.  */
  // bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
  //                 Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
  //                 Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
  //                 Adafruit_BMP280::FILTER_X16,      /* Filtering. */
  //                 Adafruit_BMP280::STANDBY_MS_500);  /* Standby time. */
  // Teste BPM280
  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões.")); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
}

void loop() {
    Serial.print(F("Temperature  = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure()/100);  //displaying the Pressure in hPa, you can change the unit
    Serial.println("  hPa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1019.66));  //The "1019.66" is the pressure(hPa) at sea level in day in your region
    Serial.println("  m");                    //If you don't know it, modify it until you get your current  altitude

    Serial.println();
    delay(2000);
}