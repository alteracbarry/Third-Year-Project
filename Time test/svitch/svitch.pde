#define SWITCH 4
int s0 = LOW;
long unsigned time = 0;
long interval = 999;
unsigned long prev = 0;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  if (millis()-prev > interval)
  {
    prev = millis();
    s0 = digitalRead(SWITCH);
    Serial.print(s0);
    Serial.print(", ");
    Serial.println(millis());
  }
}
    
