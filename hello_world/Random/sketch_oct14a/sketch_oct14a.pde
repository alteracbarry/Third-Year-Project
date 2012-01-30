int adc = 0;
int adcc = 0;
int count = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  count = count + 1;
  adc = analogRead(0);
  adcc = ((adc*5)/1024);
  Serial.print(count);
  Serial.print(": ");
  Serial.println(adcc);
  delay (1000);
}
