//
//    FILE: AS5600_demo_two_I2C.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo two I2C busses
//     URL: https://github.com/RobTillaart/AS5600
//
//  Works only if Wire1 bus is present e.g.
//  - nano33 ble
//  - teensy 4.1
//  - RP2040
//
//  Examples may use AS5600 or AS5600L devices.
//  Check if your sensor matches the one used in the example.
//  Optionally adjust the code.


#include "AS5600.h"
#include <Wire.h>

AS5600 as5600_0(&Wire);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);

  Wire.begin();

  as5600_0.begin();  //  set direction pin.
  as5600_0.setDirection(AS5600_CLOCK_WISE);
  Serial.print("Connect device 0: ");
  Serial.println(as5600_0.isConnected() ? "true" : "false");
  delay(1000);
}


void loop()
{
  Serial.print("Direção");
  Serial.print("\t");

  float direction = as5600_0.readAngle() * 0.087912;
  Serial.print(direction);
  Serial.print("\n");
  delay(100);
}


//  -- END OF FILE --
