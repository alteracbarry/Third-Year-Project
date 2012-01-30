#define LED 13
#define SWITCH 2
#define Echo 8
#define Trigger 7
int val = LOW;
int SWITCH_ON = LOW;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(Trigger, OUTPUT);
  pinMode(SWITCH, INPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600); 
}

void loop()
{
  SWITCH_ON = digitalRead(SWITCH);
  if (SWITCH_ON == HIGH)
  {  
    digitalWrite(Trigger, HIGH);
    
    val = digitalRead(Echo);
    Serial.print(digitalRead(Echo));
    delayMicroseconds(10);
      if (val == HIGH)
    {
      digitalWrite(LED, LOW);
      delay(10000);
    }
    else
    {
      digitalWrite(LED, HIGH);
      delay(1000);
    }
    digitalWrite(Trigger, LOW);
  }
  else
  {
    val = LOW;
  }

}  
    
    
    
    
