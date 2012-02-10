/* Script for Master Node :-
   Implements a seperate ASCII-to-long capture method and uses
   interrupts for interaction (no use of loop)
   Areas for Improvement: Optimise, test, code for display instead of Serial
*/
#include <stdlib.h>
#include <stdio.h>
int Sensor = 4; // Ultrasonic Transducer at pin 4
unsigned long RTTd2 = 0; // Half of the round-trip time; not necessarily a constant (ms)
unsigned long Dist = 0; // Distance 
long Toffset = 0; // Master and Slave clock difference (ms)
char someChar = 0;
char conf = 0;
unsigned long Trec = 0;
unsigned long Tsend = 0;


void setup()
{
  attachInterrupt(0, Sync, RISING); // IRQ0 attached to pin 2 on Duemilanove
  attachInterrupt(1, Pulse, RISING); // IRQ1 attached to pin 3 " "
  Serial.begin(9600);
}

void loop()
{
  switch (someChar)
  {
    case 'a':
      digitalWrite(13, HIGH);
      Serial.print("z");
      Tsend = millis(); // Take sent time
      confirm();
      Trec = millis(); // and receive time
      RTTd2 = (Trec - Tsend)/2;
      Toffset = capture() - RTTd2;
      Serial.println("Sync DONE!");
      Serial.print("Half RTT is: ");
      Serial.println(RTTd2);
      Serial.print("Tsend is: ");
      Serial.println(Tsend);
      Serial.print("Trec is: ");
      Serial.println(Trec);
      Serial.print("Offset is: ");
      Serial.println(Toffset);
      conf = 0;
      Trec = 0;
      Tsend = 0;
      someChar = 0;
      digitalWrite(13, LOW);
      break;
    case 'b':
      digitalWrite(13, HIGH);
      unsigned long Tpulse = millis(); // Timestamp pulse
      tone(Sensor, 40000, 1); // 40 KHz transducer pulse for 1 ms
      confirm();
      unsigned long Tsense = capture(); // Capture time of reception
      unsigned long Tprop = (Tsense - (Tpulse + Toffset));
      float Dist = (Tprop/3); // Speed of sound = ~330m/s = ~1/3 m/ms
      Serial.print("Distance (m): ");
      Serial.println(Dist);
      someChar = 0;
      digitalWrite(13, LOW);
      break;
  }
}

void Sync()
{
  someChar = 'a'; // flag for sync routine
}

void Pulse()
{
  someChar = 'b'; // flag for pulse routine
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
