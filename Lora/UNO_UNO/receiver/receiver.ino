// Neste caso Arduino UNO será o emissor
#include <SoftwareSerial.h>

#define pinRx 7
#define pinTx 8

#define pinLed 11
#define msgUno "ok"

SoftwareSerial lora(pinRx,pinTx);

// #define RXD2 16
// #define TXD2 4
// int m=0;

void setup() {

  // pinMode(22,OUTPUT);
  // pinMode(19,OUTPUT);

  Serial.begin(9600);
  lora.begin(9600);

  Serial.println("Uno pronto");
  delay(100);
}

void loop() {
  // digitalWrite(22,HIGH);
  // digitalWrite(19,LOW);

  // m++;
  // Serial2.println(m);
  // Serial2.println();
  // Serial.println(m);
  // Serial.println();

  // Serial.print("mensagem uno: ");
  // Serial.println(msgUno);
  // delay(1000);

  if (lora.available()){
    String recebido = lora.readString();
    Serial.println(recebido);
  }
  delay(100);
}
