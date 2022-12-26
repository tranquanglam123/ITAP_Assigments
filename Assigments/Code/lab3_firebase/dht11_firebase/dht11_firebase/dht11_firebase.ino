#include <DHT.h>
#include <DHT_U.h>

#include <FirebaseESP32.h>
#include <DHT.h>
#include  <WiFi.h>

#define FIREBASE_HOST "https://iotfirebase-ee64c-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "xyFaatQqedlT6XJLRAZlyPeqPFwux0vD6nwpM3pG"
#define WIFI_SSID "^$^" // Thay Ã„â€˜Ã¡Â»â€¢i tÃƒÂªn wifi cÃ¡Â»Â§a bÃ¡ÂºÂ¡n
#define WIFI_PASSWORD "33333333" // Thay Ã„â€˜Ã¡Â»â€¢i password wifi cÃ¡Â»Â§a bÃ¡ÂºÂ¡n
#define DHTPIN 4    
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
FirebaseData fbdo;

void setup() {

  Serial.begin(9600);
  delay(1000);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Dang ket noi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  dht.begin();
  Serial.println ("");
  Serial.println ("Da ket noi WiFi!");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Ã„ÂÃ¡Â»Âc nhiÃ¡Â»â€¡t Ã„â€˜Ã¡Â»â„¢ theo Ã„â€˜Ã¡Â»â„¢ C

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;

  }

  Serial.print("Nhiet do: ");
  Serial.print(t);
  Serial.print("*C  ");
  Serial.print("Do am: ");
  Serial.print(h);
  Serial.println("%  ");

  Firebase.setFloat( fbdo,"Nhiet do", t);

  Firebase.setFloat ( fbdo,"Do am", h);

  delay(200);

}
