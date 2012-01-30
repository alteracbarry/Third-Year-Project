// ASCII-to-unsigned long converter
// Concatenates digits arriving individually through Serial
// into a singular unsigned long number

char string1[9] = "12345678";
unsigned long numbers0[9] = {0,0,0,0,0,0,0,0};
unsigned long numbers1[9] = {0,0,0,0,0,0,0,0};
unsigned long BIG = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for(int i = 0; i < 8; i++)
  {
    do
    {
      string1[i] = Serial.read();
    } while (string1[i] == -1);
    Serial.println(string1[i]);
  }
  for(int i = 0; i < 8; i++)
  {
    if (i > 0)
    {
      numbers1[i] = (hex2dec(string1[i]) * (pow(10,i)));
    }
    else
    {
      numbers1[i] = hex2dec(string1[i]);
    }
  }
  for(int i = 0; i < 8; i++)
  {
    Serial.println(numbers1[i]);
    delay(500);
  }
  delay(2000);
  BIG = (numbers1[8] + numbers1[7] + numbers1[6] + numbers1[5]
  + numbers1[4] + numbers1[3] + numbers1[2] + numbers1[1] + numbers1[0]);
  Serial.print(BIG);
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
