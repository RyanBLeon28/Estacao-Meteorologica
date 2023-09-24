#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>  //https://github.com/bbx10/WebServer_tng

WebServer server ( 80 );

const char* ssid     = "VETORIAL_135F";
const char* password = "280273iara";

#define strip1_Pin 16             //  Pino de sinal

float temperature = 0;
float humidity = 0;
float pressure = 0;


void setup()
{
  Serial.begin(9600);

  //initSensor();

  connectToWifi();

  beginServer();

}

void loop() {

  server.handleClient();

  // getTemperature();
  // getHumidity();
  // getPressure();
  
  delay(1000);

}

void connectToWifi()
{
  WiFi.enableSTA(true);

  delay(2000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void beginServer()
{
  server.on ( "/", handleRoot );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void handleRoot() {
  //if ( server.hasArg("LED") || server.hasArg("COLOR")) {
  if ( server.hasArg("COLOR")) {
    handleSubmit();
  } else {
    server.send ( 200, "text/html", getPage() );
  }
}

void handleSubmit() {

  
  server.send ( 200, "text/html", getPage() );

}

String getPage() {
  String page = "<html lang=en-EN><head><meta http-equiv='refresh' content='60'/>";
  page += "<title>Anemometro Page</title>";
  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }</style>";
  page += "</head><body><h1>Welcome to Observatory Page</h1>";
  page += "<li>Humidity: ";
  page += humidity;
  page += "%</li>";
  page += "<li>Barometric Pressure: ";
  page += pressure;
  page += " hPa</li></ul>";
  page += "<form action='/' method='POST'>";
  page += "<ul><li>LED";
  page += "";
  page += "</form>";
  page += "</body></html>";
  return page;
}
