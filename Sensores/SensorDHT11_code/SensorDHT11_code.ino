#include "DHT.h"
#define DHTPIN 8                       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11                  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL
    // Teste DHT11
  Serial.println(F("DHTxx test!"));
  dht.begin();

  delay(2000); //INTERVALO DE 2 SEGUNDO ANTES DE INICIAR
}
 
void loop(){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  Serial.println();
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  delay(2000); //INTERVALO DE 2 SEGUNDOS * NÃO DIMINUIR ESSE VALOR
}
