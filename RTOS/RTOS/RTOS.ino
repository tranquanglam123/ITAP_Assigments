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
TaskHandle_t Task1; 
TaskHandle_t Task2;  
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
const int led_1 = 2; 
const int led_2 = 4;  
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

Serial.begin(115200); 

pinMode(led_1, OUTPUT);

pinMode(led_2, OUTPUT);  

xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,0);  delay(500);   

xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,1,&Task2,1);  delay(500); 

dht.begin();
  timer.setInterval(1000L, sendSensor);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}  

void Task1code( void * parameter )

{

Serial.print("Task1 is running on core "); 

Serial.println(xPortGetCoreID()); 

for(;;){

digitalWrite(led_1, HIGH);

vTaskDelay(1000); 

digitalWrite(led_1, LOW); 

vTaskDelay(1000);

}

}  

void Task2code( void * parameter )

{ 

Serial.print("Task2 is running on core ");

Serial.println(xPortGetCoreID());  

for(;;)

{ digitalWrite(led_2, HIGH); 

vTaskDelay(1000);


}

}  

void loop()

{  
sendSensor();
  Blynk.run();
}
