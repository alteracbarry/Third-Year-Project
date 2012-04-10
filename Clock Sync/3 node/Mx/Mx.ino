/* Ultrasonic Range Finder (3+ nodes) - Master Node
 
 */


#include <SoftwareSerial.h>
#include <stdlib.h>
#include <stdio.h>
char ID[3] = {
  'R','T'}; // IDs given to Rx and TRx units (respectively)
unsigned long Offset[3];
volatile float distance[4];
boolean flag = false;

#define txPin 4
#define rxPin 7
SoftwareSerial PC_Serial = SoftwareSerial(rxPin,txPin);

void setup()
{
  attachInterrupt(0,Sync,RISING);
  Serial.begin(19200);
  PC_Serial.begin(19200);
}

void loop()
{
  // synchonise clocks with other nodes
  if(flag)
  {
    digitalWrite(13,HIGH); // turn Duemilanove LED ON
    Serial.read(); // flush serial buffer
    unsigned long Time[2];
    long RTT;
    for(int i; i < 2; i++)
    {
      char conf;
      Serial.print(ID[i]);
      Time[0] = micros();
      while(conf != ID[i])
      {
        conf = Serial.read();
      }
      Time[1] = micros();
      RTT = ((Time[1]/100) - (Time[0]/100));
      Offset[i] = capture() - (RTT/2) - (Time[0]/100);
    }
    // determine distance from other nodes
    Time[0] = micros();
    tone(8, 40000, 1); // oscillate sensor on Pin 8 at 40 KHz for 1 ms
    for(int i; i < 2; i++)
    {
      char x = ID[i] + 32; // lower-case ID letter set to receive sensor time
      Serial.print(x);
      Time[1] = capture();
      distance[i] = (((Time[1] - Offset[i]) - Time[0]) * 0.033);
      if(distance[i] < 0 || distance[i] > 1000)
      {
        distance[i] = 0; // PC can read as an error
      }
    }
    // call TRx to send a pulse
    Serial.print('u');
    delay(100);
    for(int i; i < 2; i++)
    {
      char x = ID[i] + 32; // lower-case ID letter set to receive sensor time
      Serial.print(x);
      Time[i] = capture() - Offset[i];
    }
    distance[3] = ((Time[0] - Time[1])  * 0.033);
    if(distance[3] < 0 || distance[3] > 1000)
    {
      distance[3] = 0; // PC can read as an error
    }
    flag = false;
    digitalWrite(13, LOW); // Turn Duemilanove LED OFF
  }
  // check if a message has been recieved from PC
  if(PC_Serial.available() > 0)
  {
    digitalWrite(13, HIGH); // Turn Duemilanove LED ON
    char PC_buffer = PC_Serial.read();
    if(PC_buffer == '*') // if asterix then read out distance data
    {
      for(int i; i < 3; i++)
      {
        Serial.print(distance[i]);
        Serial.print('n');
      }
    }
    digitalWrite(13, LOW); // turn Duemilanove LED OFF
  }
}

void Sync() // interrupt method called when button at Pin 2 is pushed
{
  flag = true;
}

long int capture() // concatenates arriving ASCII characters into a long integer
{
  unsigned long lin = 0;
  char buffer[] = "";
  Serial.readBytes(buffer,7);
  Serial.setTimeout(1000);
  lin = strtoul(buffer, NULL, 10);
  return lin;
}

