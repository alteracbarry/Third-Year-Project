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


void setup()
{
  attachInterrupt(0, Sync, RISING); // IRQ0 attached to pin 2 on Duemilanove
  attachInterrupt(1, Pulse, RISING); // IRQ2 attached to pin 3 " "
  Serial.begin(9600);
}

void loop()
{
  // Do Nothing
}

void Sync()
{
  Serial.print("z");
  unsigned long Tsend = millis(); // Take sent time
  while (Serial.available() == 0)
  {
    // Loop Nothing until Serial arrives.
  }
  unsigned long Trec = millis(); // and receive time
  RTTd2 = (Trec - Tsend)/2;
  Toffset = capture() - RTTd2;
  Serial.println("Sync DONE!");
}

void Pulse()
{
  unsigned long Tpulse = millis(); // Timestamp pulse
  tone(Sensor, 40000, 1); // 40 KHz transducer pulse for 1 ms
  unsigned long Tsense = capture(); // Capture time of reception
  unsigned long Tprop = (Tsense - (Tpulse + Toffset));
  float Dist = (Tprop/3); // Speed of sound = ~330m/s = ~1/3 m/ms
  Serial.print("Distance (m): ");
  Serial.println(Dist);
}

long int capture()
{
  int k = 0;
  int i = 0;
  unsigned long lin = 0;
  char buffer[] = "";
  delay(500); // little bit of insurance for now, won't affect Toffset as there is no time-dependency
   while(Serial.available() > 0)
   {
     buffer[i] = Serial.read();
     delay(10); // cannot remove!!! Needs to wait for slow serial stream >.<
     i++;
   }
   lin = strtoul(buffer,NULL,10);
   return lin;
}

 
