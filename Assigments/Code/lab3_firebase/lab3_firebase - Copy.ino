#include <WiFi.h>
#define SSID "TV CLC"
#define PASSWORD "khongchoo"
#include "FirebaseESP32.h"
#define FIREBASE_HOST "esp32-mq3-e3874-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "BiaTmqy4oayP8ZmcxX58NCu07dGkyDOiiVwfNXua"
FirebaseData firebaseData;
FirebaseJson json;
String path="/";
float sensorValue;
#define MQ 18
#define SENSOR 34
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
 }
 Firebase.setInt(firebaseData, path 
+"/sensor",sensorValue);
}
