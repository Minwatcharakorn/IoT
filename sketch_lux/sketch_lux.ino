/*
  Example of BH1750 library usage. This example initialises the BH1750 object using the default high resolution continuous mode and then makes a light level reading every second.
*/
#define BLYNK_TEMPLATE_ID           "TMPL6twgCqxG9"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "xj0Xw5kNIiNs3mHM5X25FazTKeQ375UW"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>
#include <BH1750.h>

char ssid[] = "Minny (2)";
char pass[] = "88888888";
BlynkTimer timer;
BH1750 lightMeter;

void setup(){
  Serial.begin(9600);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use Wire.begin(D2, D1);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  Blynk.run();
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  Blynk.virtualWrite(V1, lux);
  delay(1000);
}