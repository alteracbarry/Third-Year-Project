// Analogue Hardware IRQ

void setup() 
{
  ACSR = 
  (0<<ACD) |   // Analog Comparator: Enabled
  (0<<ACBG) |   // Analog Comparator Bandgap Select: AIN0 is applied to the positive input
  (0<<ACO) |   // Analog Comparator Output: Off
  (1<<ACI) |   // Analog Comparator Interrupt Flag: Clear Pending Interrupt
  (1<<ACIE) |   // Analog Comparator Interrupt: Enabled
  (0<<ACIC) |   // Analog Comparator Input Capture: Disabled
  (1<<ACIS1) | (1<<ACIS0);   // Analog Comparator Interrupt Mode: Comparator Interrupt on Rising Output Edge
}

void loop() 
{
  // Nothing
}

ISR(ANALOG_COMP_vect)
{
  // Code run when during IRQ
}

