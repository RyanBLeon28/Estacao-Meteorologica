#include <Wire.h>

#define AS5600_ADDRESS 0x36 // Endereço I2C do AS5600

const char* ssid     = "VETORIAL_135F_5GHZ";
const char* password = "280273iara";

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // Solicitar leitura da posição angular
  Wire.beginTransmission(AS5600_ADDRESS);
  Wire.write(0x0E); // Registro de leitura de ângulo (0x0E)
  Wire.endTransmission();
  
  // Ler os dados de resposta do sensor
  Wire.requestFrom(AS5600_ADDRESS, 2);
  
  if (Wire.available() >= 2) {
    int angleData = (Wire.read() << 8) | Wire.read(); // Ler os dois bytes de dados
    float angleDegrees = map(angleData, 0, 4095, 0, 360); // Mapear para graus
    Serial.print("Ângulo: ");
    Serial.print(angleDegrees);
    Serial.println(" graus");
  }
  
  delay(1000); // Esperar um segundo antes da próxima leitura
}
