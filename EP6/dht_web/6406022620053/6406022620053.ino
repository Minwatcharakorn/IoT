/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/
*********/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

const char* ssid = "....";
const char* password = "88888888";

#define DHTPIN D5
#define DHTTYPE DHT22
const int analogPin = A0; // กำหนดขาที่ต่อสัญญาณ Analog


DHT dht(DHTPIN, DHTTYPE);

float t = 0.0;
float f = 0.0;
float h = 0.0;
float a = 0.0;

AsyncWebServer server(80);

unsigned long previousMillis = 0;
const long interval = 10000;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <link rel="stylesheet" href="path/to/font-awesome/css/font-awesome.min.css">
  <style>
    html {
      font-family: Arial;
      display: inline-block;
      margin: 0px auto;
      text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    
  </style>
</head>
<body>
  <h2>Watcharakorn Yentaweesub</h2>
  <img src="https://upload.wikimedia.org/wikipedia/th/thumb/b/be/Seal_of_KMUTNB.svg/1200px-Seal_of_KMUTNB.svg.png"width="200"height:"200">
  <p>
    <i class="fa fa-male" aria-hidden="true" style="color:#059e8a;"></i> 
    <span class="dht-labels">AnalogValue</span> 
    <span id="analogValue">%ANALOGVALUE%</span>
  </p>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-thermometer-half" style="color:#ff0000;"></i> 
    <span class="dht-labels">Fahrenheit</span> 
    <span id="fahrenheit">%Fahrenheit%</span>
    <sup class="units">&deg;F</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>

</body>
<script>
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
      document.getElementById("fahrenheit").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/fahrenheit", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("analogValue").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/analogValue", true);
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


</script>
</html>)rawliteral";

String processor(const String& var){
  if(var == "TEMPERATURE"){
    return String(t);
  }
  else if(var == "ANALOGVALUE"){
    return String(a);
  }
  if(var == "FAHRENHEIT"){
    return String(f);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }

  return String();
}

void setup(){
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t).c_str());
  });
  server.on("/fahrenheit", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(f).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(h).c_str());
  });
  server.on("/analogValue", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(a).c_str());
  });

  server.begin();
}
 
void loop(){  

  a = analogRead(analogPin); // อ่านค่า Analog จากขาที่กำหนด
  Serial.print("Analog Value: "); // พิมพ์ข้อความ "Analog Value: "
  Serial.println(a); // พิมพ์ค่า Analog ที่อ่านได้
  delay(10000); // หน่วงเวลา 1 วินาที

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float newT = dht.readTemperature();
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      Serial.println(t);
    }

    float newF = dht.readTemperature(true);
    if (isnan(newF)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      f = newF;
      Serial.println(f);
    }

    float newH = dht.readHumidity();
    if (isnan(newH)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      h = newH;
      Serial.println(h);
    }

    
  }
}
