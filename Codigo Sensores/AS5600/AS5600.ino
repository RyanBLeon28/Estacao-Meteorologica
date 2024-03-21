//#define AS5600_ADDRESS 0x36            // Endereço I2C do AS5600

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); //For As5600
}

void loop() {
  // put your main code here, to run repeatedly:
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
}
