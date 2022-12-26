#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

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


#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogReadA3( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  
  // Now set up two tasks to run independently.
  xTaskCreatePinnedToCore(
    TaskBlink
    ,  "TaskBlink"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  0);

  xTaskCreatePinnedToCore(
    TaskAnalogReadA3
    ,  "AnalogReadA3"
    ,  1024  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL 
    ,  1);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
    
  If you want to know what pin the on-board LED is connected to on your ESP32 model, check
  the Technical Specs of your board.
*/



  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  for (;;) // A Task shall never return or exit.
  {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  }
}

void TaskAnalogReadA3(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
/*
  AnalogReadSerial
  Reads an analog input on pin A3, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A3, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
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
 pinMode(MQ, OUTPUT);

  for (;;)
  {
    sensorValue= analogRead(34); 
 Serial.println("VALUE:"); 
 Serial.println(sensorValue);
 Firebase.setInt(firebaseData, path 
+"/MQ3 Sensor",sensorValue);
  }
}
