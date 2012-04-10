/* Script for Master Node :-
 Implements a seperate ASCII-to-long capture method and uses
 interrupts for interaction (no use of loop)
 Areas for Improvement: Optimise, test, code for display instead of Serial
 */
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <stdio.h>
#define rxPin 4 // not in use
#define txPin 7
int Sensor = 8; // Ultrasonic Transducer at pin 8
unsigned long RTT = 999;
unsigned long Dist = 0; // Distance 
long Toffset = 0; // Master and Slave clock difference (ms)
char flag = 0;
char conf = 0;
unsigned long Trec = 0;
unsigned long Tsend = 0;
unsigned long Tpulse = 0;
int i = 0;
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);


void setup()
{
  attachInterrupt(0, Sync, RISING); // IRQ0 attached to pin 2 on Duemilanove
  Serial.begin(19200);
  mySerial.begin(19200);
}

void loop()
{
  switch (flag)
  {
  case 'a':
    digitalWrite(13, HIGH);
    //for (i; i < 5; i++);
    //{
    Serial.print("z");
    Tsend = micros()/100; // Take sent time
    confirm();
    Trec = micros()/100; // and receive time
    //if ((Trec - Tsend) < RTT)
    //{
    RTT = (Trec - Tsend);
    //}
    //}
    Toffset = capture() - (RTT/2) - Tsend;
    Tpulse = micros()/100; // Timestamp pulse
    tone(Sensor, 40000, 1); // 40 KHz transducer pulse for 1 ms
    unsigned long Tsense = capture(); // Capture time of reception
    long Tprop = ((Tsense - Toffset) - Tpulse);
    float Dist = (Tprop * 0.033); // Speed of sound = ~330m/s
    if (Tsense == 0)
    {  
      mySerial.println("No signal");
    } 
    else 
    {
      //Serial.println(Tpulse);
      //Serial.println(Tsense);
      //Serial.println(Toffset);
      mySerial.print("Distance : ");
      mySerial.print(Dist);
      //mySerial.println(" metres");
    }      
    Tpulse = 0;
    conf = 0;
    RTT = 999;
    Trec = 0;
    Tsend = 0;
    flag = 0;
    i = 0;
    digitalWrite(13, LOW);
    break;
  }
  Serial.read();
}

void Sync()
{
  flag = 'a';
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

