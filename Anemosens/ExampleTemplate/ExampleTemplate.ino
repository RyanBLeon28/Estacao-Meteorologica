/* Arduino Example Template

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
int led = 2;

void setup() {
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
}

void loop() {
  Serial.println("happy");
  //delay(1000);
}
