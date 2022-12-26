TaskHandle_t Task1;
TaskHandle_t Task2;
const int RedLED = 2;
const int GreenLED = 4;
void setup() {
Serial.begin(115200); 
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  xTaskCreatePinnedToCore(
                    Task1code,
                    "Task1",  
                    10000,       
                    NULL,
                    1,   
                    &Task1,   
                    0);   
xTaskCreatePinnedToCore(
                    Task2code, 
                    "Task2", 
                    10000, 
                    NULL,     
                    1,       
                    &Task2,     
                    1);     
}
void Task1code( void * pvParameters ){
  while(1)
  {
    digitalWrite(RedLED, HIGH);
    delay(700);
    digitalWrite(RedLED, LOW);
    delay(700);
  } 
}
void Task2code( void * pvParameters ){
   while(1)
  {
    digitalWrite(GreenLED, HIGH);
    delay(500);
    digitalWrite(GreenLED, LOW);
    delay(500);
  }
}
void loop(){
  
}
