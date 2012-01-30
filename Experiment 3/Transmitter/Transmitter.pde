#define VSS 8
#define SWITCH 12
int value = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(SWITCH, INPUT);
  pinMode(VSS, OUTPUT);
}

void loop()
{
  VSS == HIGH;
  value = digitalRead(SWITCH);
  if (value == HIGH)
  {
   Serial.print("Y");
  }
  else
  {
    Serial.print("N");
  }
     delay (50);
}
   
