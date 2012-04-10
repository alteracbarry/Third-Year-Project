// ASCII-to-long converter :-
// Concatenates digits arriving individually through Serial
// into a singular long integer

char buffer[9];
unsigned long numbers[9];
unsigned long factor[9] = {1,10,100,1000,10000,100000,1000000,10000000};
int i = 0;
int j = 0;
int k = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while(Serial.available() > 0)
  {
    i++;
    buffer[i] = Serial.read();
    delay(10); // cannot remove!!!
  }
  for(i; i > 0; i--)
  {
    numbers[i] = ((conv(buffer[i])) * factor[j]);
    j += 1;
    k = 1;
  }
  if(k == 1)
  {
    unsigned long BIG = 0;
    for(j+1; j > 0; j--)
    {
     BIG += numbers[j];
    }
    Serial.println(BIG);
    k = 0;
  }
i = 0;
j = 0;
}

int conv(byte c)
{
  return c - '0';
}  
