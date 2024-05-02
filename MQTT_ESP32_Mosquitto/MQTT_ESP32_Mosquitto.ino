/*
  Receiving data from another station through LoRa module and sending to NodeRed
*/
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "EBYTE.h"

#define PIN_RX 16  // Serial2 RX (connect this to the EBYTE Tx pin)
#define PIN_TX 17  // Serial2 TX pin (connect this to the EBYTE Rx pin)

#define PIN_M0 4   // D4 on the board (possibly pin 24)
#define PIN_M1 19  // D2 on the board (possibly called pin 22)
#define PIN_AX 18  // D15 on the board (possibly called pin 21)

#define SCREEN_WIDTH 128  // Largura do display em pixels
#define SCREEN_HEIGHT 64  // Altura do display em pixels

// ====================================================================================================================================
// --- Oled configuration ---
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ====================================================================================================================================
// --- Struct with station data
struct DATA {
  float Temp;
  float Humid;
  float Press;
  float Altitude;
  float Speed;
  float Direction;
};

int Chan;
DATA StationA;
DATA StationB;
unsigned long Last;
unsigned long intervalSearching = 8000; //time to start to serching data

// create the transceiver object, passing in the serial and pins
EBYTE Transceiver(&Serial2, PIN_M0, PIN_M1, PIN_AX);
// ====================================================================================================================================
// --- Conect wifi ---
// const char* ssid     = "Sala_J13";
// const char* password = "salaj132023";
const char* ssid = "VETORIAL_11_5GHZ";
const char* password = "07072022";
// const char* ssid = "A9";
// const char* password = "12345678";

const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//Conecta-se com o Wifi
void setup_wifi(unsigned long Last) {
  unsigned long interval = 6000;  //interval to return from loop
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if ((millis() - Last) >= interval) {
      Serial.println("Failure to connect to Wifi :(");
      delay(500);
      return;
    }
  }
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


//Esp recebe informações
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

//Conecta-se com o MQTT
void reconnect(unsigned long Last) {
  unsigned long interval = 6000;  //interval to return from loop
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting to Wifi");
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if ((millis() - Last) >= interval) {
      Serial.println("Failure to connect to wifi :(");
      delay(500);
      return;
    }
  }
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "espClient";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");

      client.subscribe("estacao");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying

      if ((millis() - Last) >= interval) {
        Serial.println("Failure to connect :(");
        delay(500);
        return;
      }
      delay(5000);
    }
  }
}

void displayFunction(float temp, float humid, float speed, float altitude, float press,float direction) {
  display.clearDisplay();
  display.setCursor(45, 0);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.print("MASTER");

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.print("T:"); display.print(temp); display.print("C");

  display.setCursor(70, 20);
  display.print("H: "); display.print(humid); display.println("%");

  display.setCursor(0, 35);
  display.print("S:"); display.print(speed); display.print("m/s");

  display.setCursor(70, 35);
  display.print("A:"); display.print(altitude); display.println("m");

  display.setCursor(0, 50);
  display.print("P:"); display.print(press); display.println("Pa");

  display.setCursor(70, 50);
  display.print("D:"); display.print(direction); display.println("º");
  
  display.display();
}

void displaySearchingData(){
  display.clearDisplay();
  display.setCursor(45, 0);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.print("MASTER");

  display.setCursor(10, 20);
  display.println("Searching for         data...");
  display.display();
  delay(1500);
  display.clearDisplay();
}

void setup() {
  Serial.begin(9600);

  Last = millis();
  setup_wifi(Last);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial2.begin(9600);
  Serial.println("Starting Reader");

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
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Limpa o buffer do display
  display.clearDisplay();

  // Desenha alguns textos e formas geométricas
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Master Station");
  display.display();
  delay(1500);
  display.clearDisplay();
}

int b = 0;
void loop() {
  //if (Serial2.available()) {
  if (b == 0) {
  
    StationA.Temp = 0;
    StationA.Humid = 0;
    StationA.Press = 0;
    StationA.Altitude = 0;
    StationA.Speed = 0;
    Transceiver.GetStruct(&StationA, sizeof(StationA));

    Serial.println();
    Serial.println("Received from StationA:  ");
    Serial.print("Temperature: "); Serial.print(StationA.Temp); Serial.println(" ºC");
    Serial.print("Humidy:      "); Serial.print(StationA.Humid); Serial.println(" %");
    Serial.print("Press:     "); Serial.print(StationA.Press); Serial.println(" Pa");
    Serial.print("High:       "); Serial.print(StationA.Altitude); Serial.println(" m");
    Serial.print("wind speed:  "); Serial.print(StationA.Speed); Serial.println(" m/s");
    Serial.print("Wind direc:  "); Serial.print(StationA.Direction);Serial.println(" Degrees");
    Serial.print("-------------------------------------");
    //Serial.println(Transceiver.GetAddressH());
    //Serial.print("Endereço: "); Serial.println(StationA.Adress);

    delay(100);  //just to received data before send to cloud
    
    // ====================================================================================================================================
    // --- Publicando em cada tópico ---
    sprintf(msg, "%.2f", StationA.Temp);
    client.publish("estacao/temperatura", msg);

    sprintf(msg, "%.2f", StationA.Humid);
    client.publish("estacao/umidade", msg);

    sprintf(msg, "%.2f", StationA.Press);
    client.publish("estacao/pressao", msg);

    sprintf(msg, "%.2f", StationA.Altitude);
    client.publish("estacao/altitude", msg);

    sprintf(msg, "%.2f", StationA.Speed);
    client.publish("estacao/velocidade", msg);

    sprintf(msg, "%.2f", StationA.Direction);
    client.publish("estacao/direcao", msg);

    //Transceiver.GetStruct(&StationB, sizeof(StationB));

    // ====================================================================================================================================
    // --- Show data in display ---
    displayFunction(StationA.Temp, StationA.Humid, StationA.Speed, StationA.Altitude, StationA.Press, Station.Direction);

    // ====================================================================================================================================
    // --- if is not connecteed to broker
    if (!client.connected()) {
      Serial.println();
      Serial.println("Connecting to MQTT");
      reconnect(Last);  //caso passe 5s retorna a receber o valor das outras estações
    }
    client.loop();
    Last = millis();
  } else { //if is not receiving data from a LoRa module
    if ((millis() - Last) > intervalSearching) {
      Serial.println();
      Serial.println("Searching data: ");
      displaySearchingData();
      Last = millis();
    }
  }
}  // end loop
