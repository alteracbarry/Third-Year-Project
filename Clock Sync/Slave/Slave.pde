unsigned long oldm = 0;
unsigned long time = 0;
unsigned long offset = 0;
unsigned long timer = 0;
char Trigger = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Trigger = Serial.read();
  if(Trigger == 's')
  {
    oldm = millis();
    do
    {
      time = Serial.read();
    } while (time == -1);
    Serial.print(hex2dec(time));
    do
    {
      offset = Serial.read();
    } while (offset == -1);
    Serial.print(hex2dec(time));
  }
  if(millis() - timer >= 1000)
  {
  Serial.println(millis() - oldm + hex2dec(time) + hex2dec(offset), DEC);
  timer = millis();
  }
}

int hex2dec(byte c)
{
  if (c >= '0' && c <= '9')
  {
    return c - '0';
  }
  else if (c >= 'A' && c <= 'F')
  {
    return c - 'A' + 10;
  }
}
