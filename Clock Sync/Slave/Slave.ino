/*  Slave node code:-
    Lightweight code for slave node(s)
    - Need to change to account for 'bufferUntil' compiler error
    - Need to amend Master to "flush" confirmation character
*/
unsigned long Tdetect = 0;

void setup() 
{
  ACSR = 
  (0<<ACD) |   // Analog Comparator: Enabled
  (0<<ACBG) |   // Analog Comparator Bandgap Select: Disabled (Using both reference pins)
  (0<<ACO) |   // Analog Comparator Output: Off
  (1<<ACI) |   // Analog Comparator Interrupt Flag: Clear Pending Interrupt
  (1<<ACIE) |   // Analog Comparator Interrupt: Enabled
  (0<<ACIC) |   // Analog Comparator Input Capture: Disabled
  (1<<ACIS1) | (1<<ACIS0);   // Analog Comparator Interrupt Mode: Comparator Interrupt on Rising Output Edge
  
  Serial.begin(9600);
  Serial.bufferUntil('z');
}

void loop() 
{
  // Nothing
}

void serialEvent()
{
  Tdetect = millis(); // save detection time
  Serial.print("c"); // some arbitrary character that lets master node continue
  Serial.print(Tdetect);
}

ISR(ANALOG_COMP_vect)
{
  Serial.print(millis());
}

