// ASCII-to-unsigned long converter
// Concatenates digits arriving individually through Serial
// into a singular unsigned long number

char buffer[9];
unsigned long numbers[9] = {0,0,0,0,0,0,0,0};
unsigned long BIG = 0;
int i = 0;
int j = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while(Serial.available() > 0 || )
  {
    i++;
    buffer[i] = Serial.read();
  }
  for(i; i > 0; i--)
  {
    switch(j)
    {
      case 0:
        numbers[i] = (hex2dec(buffer[i]));
        break;
      case 1:
        numbers[i] = ((hex2dec(buffer[i])) * (10));
        break;
      case 2:
        numbers[i] = ((hex2dec(buffer[i])) * (100));
        break;
      case 3:
        numbers[i] = ((hex2dec(buffer[i])) * (1000));
        break;
      case 4:
        numbers[i] = ((hex2dec(buffer[i])) * (10000));
        break;
      case 5:
        numbers[i] = ((hex2dec(buffer[i])) * (100000));
        break;
      case 6:
        numbers[i] = ((hex2dec(buffer[i])) * (1000000));
        break;
      case 7:
        numbers[i] = ((hex2dec(buffer[i])) * (10000000));
        break;
    }
    j += 1;
    Serial.println(numbers[i]);
    delay(2000);
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
