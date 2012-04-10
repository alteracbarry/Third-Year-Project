#define LED 3
int state = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop()
{
   char value = Serial.read();
   switch (value)
   {
     case 'Y':
       digitalWrite(LED,HIGH);
       delay(50);
       break;
     case 'N':
       digitalWrite(LED,LOW);
       delay(50);
       break;
     default:
       digitalWrite(LED,LOW);
       delay(50);
       break;
   }
}
     
   

