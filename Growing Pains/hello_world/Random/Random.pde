#define SWITCH 3
int value = 0;
int seed[] = {0};
int seedin = 0;
int rand0 = 0;
int rand1 = 0;
int rand2 = 0;

void setup()
{
  pinMode(seedin, INPUT);
  pinMode(SWITCH, INPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop()
{
  value = digitalRead(3);
  if (value == HIGH)
  {
   seedin = analogRead(0);
   delayMicroseconds (50);
   seed[0] = random(seedin);
   delayMicroseconds (50);
   Serial.print(seedin);
   Serial.print(",\r");
   Serial.print(seed[0]);
   Serial.println("\r");
   delay (2000);
  }
}
   
