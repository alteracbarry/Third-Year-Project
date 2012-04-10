#include <SoftwareSerial.h>
#define LED 13
#define rxPin 0
#define txPin 1
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
int state = LOW;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);
}

void loop()
{
  digitalWrite(LED,LOW);
  char someChar = mySerial.read();
  if(someChar=='a')
  {
  digitalWrite(LED,HIGH);
  delay(1000);
  }
  else
  {
    flicker(LED);
  }
}

void flicker(int pinNum)
{
  digitalWrite(LED,HIGH);
  delay(250);
  digitalWrite(LED,LOW);
  delay(250);
  digitalWrite(LED,HIGH);
  delay(250);
  digitalWrite(LED,LOW);
}
  
  


