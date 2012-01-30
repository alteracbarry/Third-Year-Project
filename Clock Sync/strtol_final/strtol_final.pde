// ASCII-to-long converter :-
// Concatenates digits arriving individually through Serial
// into a singular long integer
#include <stdlib.h>
#include <stdio.h>
int i = 0;
int k = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  char buffer[] = "";
  while(Serial.available() > 0)
  {
    buffer[0 + i] = Serial.read();
    delay(10); // cannot remove!!!
    k = 1;
    i++;
  }
  if(k == 1)
  {
    long int lin = strtol(buffer,NULL,10);
    Serial.println(lin);
    delay(1000);
    k = 0;  
  }
i = 0;
}
