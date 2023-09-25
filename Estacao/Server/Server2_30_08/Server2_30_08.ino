#include "WiFi.h"
#include <ESPAsyncWebSrv.h>
//#include <ESPAsyncTCP.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

//Sensores
Adafruit_BMP280 bmp; // I2C Interface

#define DHTPIN 27    // Pino DHT
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Rede e senha do Wifi
const char* ssid     = "VETORIAL_135F";
const char* password = "280273iara";

//Cria um Assincrono Webserver na porta 80
AsyncWebServer server(80);

String readDHTTemperature() {
  //float t = dht.readTemperature();
  float t = 21;
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //float h = dht.readHumidity();
  float h = 80;
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

String readBMPPressure() {
  //float g = bmp.readPressure()/100;
  float g = 10;
  if (isnan(g)) {
    Serial.println("Failed to read from BMP sensor!");
    return "--";
  }
  else {
    Serial.println(g);
    return String(g);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Weather Station</title>

  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     background-color: #85c7f2;
    }
    h1 { 
      "font-size: 24px; 
      text-align: center;
    }
    h2 { 
      "font-size: 22px;
      margin-left:20px;
    }
    p { 
      "font-size: 18px;
      margin-left:20px; 
    }
    .units { 
      "font-size: 18px;
    }
    .dht-labels{
      "font-size: 18px;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <header><h1>Estacao Metereologica do Observatorio Furg</h1></header>
  <br>
  <h2>Dados da estacao:</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Pressure</span>
    <span id="Pressure">%PRESSURE%</span>
    <sup class="units">hPa</sup>
  </p>
  
  <br>
  <br>
  <br>
  <br>
  <br>
  <br>
  <br>
  
  <footer>
  <p>&copy; 2023 Observatory Page. All rights reserved.</p>
  </footer>;
</body>
<script>1
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("pressure").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/pressure", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  else if(var == "PRESSURE"){
    return readBMPPressure();
  }
  return String();
}

void setup(void) {

  Serial.begin(115200);
  
  //inicia o BMP280
  // Serial.println(F("BMP280 test"));
  // if  (!bmp.begin()) {
  //   Serial.println(F("Could not find a valid BMP280 sensor,  check wiring!"));
  //   while (1);}
  
  //inicia o DHT
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });

  // Start server
  server.begin();
}



void loop(){

}