// Neste caso Arduino nano será o transmissor

#include <SoftwareSerial.h>

#define pinRx 6
#define pinTx 7

#define pinLed 11
#define msgNano "guilherme"

SoftwareSerial lora(pinRx,pinTx);

void setup() {
  // put your setup code here, to run once:
  // pinMode(pinLde,OUTPUT);
  // pinMode(D8,OUTPUT);

  Serial.begin(9600);
  lora.begin(9600);
  
  Serial.println("Nano Pronto");
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(D7,LOW);
  // digitalWrite(D8,HIGH);

  Serial.print("\nmensagem nano: ");
  Serial.println(msgNano);
  
  lora.println(msgNano);
  delay(1000);

  // if (lora.available()){
  //   String recebido = lora.readString();
  //   Serial.println(recebido);
  // }

  delay(100);
}
