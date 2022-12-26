#include <WiFi.h>
//#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#define SECRET_SSID "TV CLC"
#define SECRET_PASS "khongchoo"
#define SECRET_CH_ID 1988805
#define SECRET_WRITE_APIKEY "0AX538EB5JISXTNF"
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
float sensorValue;
#define MQ 18
#define SENSOR 34
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int number = 0;

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
   pinMode(SENSOR, INPUT);
  Serial.println("sensor start");
  pinMode(MQ, OUTPUT);
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
    sensorValue= analogRead(34);
    Serial.println("VALUE:"); 
    Serial.println(sensorValue);
    if( sensorValue>2000){
      digitalWrite(18,1);
      delay(50);
      digitalWrite(18,0);
      delay(30);   
  }
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, sensorValue, myWriteAPIKey);
    Serial.println("Channel update successful.");

  delay(200); // Wait 20 seconds to update the channel again
}
