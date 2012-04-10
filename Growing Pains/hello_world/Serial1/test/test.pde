int seedin = 0;
int count = 0;
int value = 0;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop()
{
  char someChar = Serial.read();
  switch (someChar)
  {
    case 'a':
      seedin = analogRead(0);
      value = random(seedin);
      count = count +1;
      Serial.print("Random Sample ");
      Serial.print(count);
      Serial.print(": ");  
      Serial.println(value);
      delay(200);
      break;
    case 'c':
      count = 0;
      Serial.println("*cleared count*");
      break;
  }
}
