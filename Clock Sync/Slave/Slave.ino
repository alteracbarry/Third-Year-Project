/*  Slave node code:-
    Lightweight code for slave node(s)
*/
unsigned long Tdetect = 0;
char flag = 0;
int i = 0;


void setup() 
{
  ACSR = 
  (0<<ACD) |   // Analog Comparator: (0 = Enabled, 1 = Disabled)
  (0<<ACBG) |   // Analog Comparator Bandgap Select: Disabled (Using both reference pins)
  (0<<ACO) |   // Analog Comparator Output: Off
  (1<<ACI) |   // Analog Comparator Interrupt Flag: Clear Pending Interrupt
  (1<<ACIE) |   // Analog Comparator Interrupt: Enabled
  (0<<ACIC) |   // Analog Comparator Input Capture: Disabled
  (1<<ACIS1) | (1<<ACIS0);   // Analog Comparator Interrupt Mode: Comparator Interrupt on Rising Output Edge
  
  Serial.begin(19200);
}

void loop() 
{
  switch (flag)
  {
    case 'a':
      Tdetect = millis(); // save detection time
      Serial.print("c"); // some arbitrary character that lets master node continue
      i++;
      if (i < 5)
      {
        Serial.print(Tdetect); // send detection time
        i = 0;
      }        
      flag = 0;
      Serial.read();
      break;
    case 'b':
      Serial.print(millis());
      delay(1000);
      flag = 0;
      break;
  }
}

void serialEvent()
{
   flag = 'a';
}

ISR(ANALOG_COMP_vect) // AIN0 & 1 on pins 6  & 7
{
   flag = 'b';
}
