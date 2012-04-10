#define BUTTON 2

char Reg1 = 0;
unsigned long millis

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  attachInterrupt(BUTTON, detect, RISING);
}

void loop()
{
  Reg1 = Serial.read();
  if (Reg1 == "A")
  {
    noInterrupts();
    while (oldm == 0)
    {
    oldm = Serial.read();
    }
    Serial.print(millis() - oldm);
    Reg1 = 0;
    interrupts();
  }
  Serial.print(millis());
  
  void detect()
  {
    Reg1 = "A";
    Serial.print(millis())
  }
