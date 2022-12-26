#define BUTTON_PIN  GPIO_NUM_5
#define ledred  GPIO_NUM_2
#define ledgreen  GPIO_NUM_4
unsigned long time1=0;
int input_state = HIGH;
bool doo=true;
int i=0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledred, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  time1=millis();
}

// the loop function runs over and over again forever
void loop() {
 if ((unsigned long)(millis()-time1)>500)
 {
  if (digitalRead(ledred)==0)
  {
    digitalWrite(ledred,HIGH);
  }
  else
  {
    digitalWrite(ledred,LOW);
  }
  time1=millis();
 }
 input_state=digitalRead(BUTTON_PIN);
 delay(100);
 if(input_state==0)
 {
  digitalWrite(ledgreen,!digitalRead(ledgreen));
 }
}
