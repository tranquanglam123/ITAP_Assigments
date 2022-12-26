               // Data ---> D3 VCC ---> 3V3 GND ---> GND
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
// WiFi parameters
#define WLAN_SSID       "TV CLC"
#define WLAN_PASS       "khongchoo"
// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "quanglam123"
#define AIO_KEY       "aio_ENln00FH1wxcf4yNDWFNczEQPscR"
#define LED 2 // LED on Board là GPIO 2.
#define PIN 34
//#include <AdafruitIO_WiFi.h>
#include <Adafruit_MQTT_Client.h>
uint32_t x=0;
float value;
int a=0;
WiFiClient client;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/digital");
Adafruit_MQTT_Publish Sensor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Sensor");
void MQTT_connect();

void setup() {
  pinMode(LED, OUTPUT);


  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff & slider feed.
  mqtt.subscribe(&onoffbutton);
  
}


void loop() {

  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
   value= analogRead(34); 
          Serial.println("VALUE:"); 
          Serial.println(value);
           if (! Sensor.publish(value)) {                     //Publish to Adafruit
             Serial.println(F("Failed"));}
        
            else {
             Serial.println(F("Sent!"));
                      }
               delay(500);

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    // Check if its the onoff button feed
    if (subscription == &onoffbutton) {
      Serial.print(F("On-Off button: "));
      Serial.println((char *)onoffbutton.lastread);
      
      if (strcmp((char *)onoffbutton.lastread, "0") == 0) {
        
        Serial.print(F("On-Off "));
        digitalWrite(LED, 0); 
      }
      if (strcmp((char *)onoffbutton.lastread, "1") == 0) {
        digitalWrite(LED, 1); 
        
       
        
        }
       
    
    // check if its the slider feed
    
    
  }

  // ping the server to keep the mqtt connection alive

}
}
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
