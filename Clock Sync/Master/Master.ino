// Script for Master Node
// Waits for Hardware IRQ and sends semaphore "HIGH" which
// starts code in the main loop
#define BUTTON 2

volatile int Sem = LOW;
unsigned long timer = 0;
unsigned long incomingByte[4] = {0, 0, 0};

void setup()
{
  attachInterrupt(0, detect, RISING);
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
}

void loop()
{
  if(Sem == HIGH)
  {
    do
    {
      incomingByte[1] = Serial.read();
    } while (incomingByte[1] == -1);
    Serial.println(a2d(incomingByte[1]) - millis());
  }
  Serial.println(millis());
}

int a2d(byte c)
{
    return c - '0';
}


void detect()
{
  Sem = HIGH;
  Serial.print("s");
  Serial.print(millis());
}

 
 
