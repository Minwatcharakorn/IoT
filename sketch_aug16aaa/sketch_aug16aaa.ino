/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6twgCqxG9"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "xj0Xw5kNIiNs3mHM5X25FazTKeQ375UW"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define LED_green D5

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Minny (2)";
char pass[] = "88888888";

BlynkTimer timer;
int count = 0;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  Blynk.virtualWrite(V1, value);
  digitalWrite(LED_green,count);
  if (value == 1)
    {
      count++;
    }
    else
    {
      count = 0;
    }
  
  // Update LED_green status based on count value
  digitalWrite(LED_green, count); // Toggle the LED on and off based on even/odd count
  
  // Update state
  Blynk.virtualWrite(V4, count);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
  
  // Read temperature from D4 and send it to Virtual Pin 5 (V5)
  

}

// Simulate reading temperature from D4 (replace this with actual reading code)
float readTemperatureFromD4()
{
  // Replace this with your actual temperature reading code
  // For now, let's just simulate a random temperature value
  return random(20, 30); // Simulate temperature between 20°C and 30°C
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(LED_green, OUTPUT);
  
  // Correct the line below from ssiad to ssid
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
    float temperature = readTemperatureFromD4(); // Replace this with your actual temperature reading code
  Blynk.virtualWrite(V5, temperature);

  float humidity = readTemperatureFromD4();
  Blynk.virtualWrite(V6, humidity);
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
