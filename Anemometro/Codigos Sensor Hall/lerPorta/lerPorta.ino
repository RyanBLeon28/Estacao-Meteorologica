

void setup() {  
  
  //Wire.begin();
  Serial.begin(115200);
  Serial.write("Setup ready");

  delay(100);
}

void loop() {
  Serial.write(int(digitalRead(2)));
  
}