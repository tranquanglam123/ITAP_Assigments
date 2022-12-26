TaskHandle_t Task1; 
TaskHandle_t Task2;  
const int led_1 = 2; 
const int led_2 = 4;  
void setup() 

{ 

Serial.begin(115200); 

pinMode(led_1, OUTPUT);

pinMode(led_2, OUTPUT);  

xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,0);  delay(500);   

xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,1,&Task2,1);  delay(500); 

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

}
