/* Script for Master Node :-
   Implements a seperate ASCII-to-long capture method and uses
   interrupts to write flags
   Areas for Improvement: use a higher precision, code for display instead of Serial
*/
//#include <SoftwareSerial.h>
#include <stdlib.h>
#include <stdio.h>
int Sensor = 8; // Ultrasonic Transducer at pin 4
unsigned long RTTd2 = 0; // Half of the round-trip time; not necessarily a constant (ms)
unsigned long Dist = 0; // Distance 
long Toffset = 0; // Master and Slave clock difference (ms)
char flag = 0;
char conf = 0;
unsigned long Trec = 0;
unsigned long Tsend = 0;
unsigned long Tpulse = 0;
//SoftwareSerial mySerial = SoftwareSerial(8, 7);


void setup()
{
  attachInterrupt(0, Sync, RISING); // IRQ0 attached to pin 2 on Duemilanove
  attachInterrupt(1, Pulse, RISING); // IRQ1 attached to pin 3 " "
  Serial.begin(19200);
  //mySerial.begin(19200);
}

void loop()
{
  switch (flag)
  {
    case 'a':
      digitalWrite(13, HIGH);
      Serial.print("z");
      Tsend = millis(); // Take sent time
      confirm();
      Trec = millis(); // and receive time
      RTTd2 = (Trec - Tsend)/2;
      Toffset = capture() - RTTd2 - Tsend;
      conf = 0;
      Trec = 0;
      Tsend = 0;
      flag = 0;
      //digitalWrite(13, LOW);
      //break;
    case 'b':
      //digitalWrite(13, HIGH);
      Tpulse = millis(); // Timestamp pulse
      tone(Sensor, 40000, 1); // 40 KHz transducer pulse for 1 ms
      unsigned long Tsense = capture(); // Capture time of reception
      long Tprop = (Tsense - (Tpulse + Toffset));
      float Dist = (Tprop/3); // Speed of sound = ~330m/s = ~1/3 m/ms
      if (Tsense == 0)
      {  
        Serial.println("No signal");
      } 
      else 
      {
        //Serial.println(Tpulse);
        //Serial.println(Tsense);
        //Serial.println(Toffset);
        Serial.print("Distance :- ");
        Serial.print(Dist);
        Serial.println(" metres");
      }      
      Tpulse = 0;
      flag = 0;
      digitalWrite(13, LOW);
      break;
  }
  Serial.read();
}

void Sync()
{
  flag = 'a';
}

void Pulse()
{
  flag = 'b';
}

void confirm()
{
  while (conf != 'c')
  {
    conf = Serial.read();
  }
}

long int capture()
{
  unsigned long lin = 0;
  char buffer[] = "";
  Serial.readBytes(buffer,7); // reads 7 digits: up to 166 minutes
  Serial.setTimeout(1000);
  lin = strtoul(buffer,NULL,10);
  return lin;
}
