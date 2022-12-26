#define BLYNK_TEMPLATE_ID "TMPLh97p-aAU"
#define BLYNK_DEVICE_NAME "DHT11"
#define BLYNK_AUTH_TOKEN "JiVaTyhB-UaHC1IubsRafuzMmrTeFO2b"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "DHT.h"
char ssid[] = "TV CLC";
char pass[] = "khongchoo";

#define DHTTYPE DHT11
#define DHTPIN 5

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  

  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
void loop()
{
  sendSensor();
  Blynk.run();
}
