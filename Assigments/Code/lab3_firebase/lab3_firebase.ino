#include <WiFi.h>

#define SSID "TV CLC"
#define PASSWORD "khongchoo"

#include "FirebaseESP32.h"

#define FIREBASE_HOST "esp32-mq3-e3874-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "BiaTmqy4oayP8ZmcxX58NCu07dGkyDOiiVwfNXua"

#include "DHT.h"
FirebaseData firebaseData;
FirebaseData fbdo;
FirebaseJson json;
String path="/";
float sensorValue;
float sensorDHTValue;
#define MQ 18
#define SENSOR 34
#define DHTTYPE DHT11
#define DHTPIN 4
DHT dht(DHTPIN, DHTTYPE);
void setup() 
{
 Serial.begin(115200); // Khởi tạo kết nối Serial để truyền dữ liệu đến máy tính
 WiFi.begin(SSID, PASSWORD); // Kết nối vào mạng WiFi
 Serial.print("Connecting to ");
 // Chờ kết nối WiFi được thiết lập
 while (WiFi.status() != WL_CONNECTED) {
 delay(1000);
 Serial.print(".");
 }
 dht.begin();
 Serial.println("\n");
 Serial.println("Connection established!");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
 Firebase.reconnectWiFi(true);
 if (!Firebase.beginStream(firebaseData, path))
 Serial.println("REASON: " + 
firebaseData.errorReason());
 Serial.println();
 pinMode(SENSOR, INPUT);
 Serial.println("sensor start");
 pinMode(MQ, OUTPUT);}
 
 void loop() {
 sensorValue= analogRead(34); 
 Serial.println("VALUE:"); 
 Serial.println(sensorValue);
 if( sensorValue>2500){
 digitalWrite(18,1);
 delay(50);
 float h = dht.readHumidity();
 float t = dht.readTemperature();  // Ã„ÂÃ¡Â»Âc nhiÃ¡Â»â€¡t Ã„â€˜Ã¡Â»â„¢ theo Ã„â€˜Ã¡Â»â„¢ C

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;

  }
 }
 Firebase.setInt(firebaseData, path 
+"/MQ:",sensorValue);
 
  Firebase.setFloat( fbdo,"Nhiet do", t);

  Firebase.setFloat ( fbdo,"Do am", h);

  delay(200);
}
