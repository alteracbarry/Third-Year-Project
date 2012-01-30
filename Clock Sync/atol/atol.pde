#include <stdio.h>
#include <stdlib.h>
long int li;
char szInput [256];
int i = 0;
int k = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Enter a long number: ");
  while(Serial.available() > 0);
  {
    szInput[i] = Serial.read();
    i++;
    k = 1;
  }
  gets (szInput);
  li = atol (szInput);
  if (k = 1)
  {
    Serial.print("The value entered is");
    Serial.print(li);
    Serial.print(". The double is");
    Serial.println(li*2);
    delay(500);
  }
}
