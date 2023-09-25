#include <WiFi.h>
#include  <Adafruit_BMP280.h>
#include <DHT.h>

//Sensores
Adafruit_BMP280 bmp; // I2C Interface
#define DHTPIN 27    // Pino DHT

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "VETORIAL_135F";
const char* password = "280273iara";

WiFiServer server(80);

String cabecalho = ""
  "<!DOCTYPE html><html><head><title>Weather Station</title></head>"
  "<body>"
  "<header><h1>Estacao Metereologica do Observatorio Furg</h1></header>"
  "<br>"
  "<main>"
  "<section>"
  "<h2>Dados da estacao:</h2>"
  "<\section>"
  "<style>"
    "body {"
        "background-color: #d15c08; "
    "}"
    
    "h1 {"
      "text-align: center;"
    "}"

    "h2 {"
      "margin-left: 20px;"
      "font-size: 22px;"
    "}"
    

  "</style>"
  "</body></html>";

String temperatura = ""
  "<body>"
  "<h1><p>Temperatura:</p><h1>"
    "<style>"
    " h1 {"
        "margin-left: 10px;"
        "justify-content:left;"
        "align-items: left;" 
      "}"
    "</style>"
  "</body>";


String rodape = ""
  "<footer>"
  "<p>&copy; 2023 Observatory Page. All rights reserved.</p>"
  "</footer>";


void setup(void) {

  Serial.begin(115200);
  
  //inicia o BMP280
  // Serial.println(F("BMP280 test"));

  // if  (!bmp.begin()) {
  //   Serial.println(F("Could not find a valid BMP280 sensor,  check wiring!"));
  //   while (1);}
  
  //Inicia a conexao wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
  Serial.println("HTTP server started");
}

//Variaveis
int var_velVento = 22;
int var_temperatura = 0;

void loop(){
  //var_temperatura = bmp.readTemperature();
  // Serial.print(F("Temperature  = "));
  // Serial.print(bmp.readTemperature());
  // Serial.println(" *C");
  var_temperatura += 2;
  

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print(cabecalho);
            client.print(temperatura);
            client.print(var_temperatura);

            client.print(rodape);

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }


      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  delay(3000);
}