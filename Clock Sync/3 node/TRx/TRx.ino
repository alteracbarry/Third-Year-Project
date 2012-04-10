/* Ultrasonic Range Finder (3+ nodes) - Transceiver slave

 */

unsigned long serial_time = 0; // holds latest serial event time
unsigned long sensor_time = 0; // holds latest sensor send or receive event time
int identifier = 'T'; // an ID assigned to nodes
int mode = 0; // 0: no event; T [ID]: sync request & serial_time; z: request sensor_time; u: send pulse
int sensor_pin = 10; // 555 oscillator circuit attached to this pin

void setup() 
{
  ACSR = 
    (1<<ACD) |   // Analog Comparator: (0 = Enabled, 1 = Disabled)
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
  switch(mode)
  {
  case 'T':
    Serial.print('T');
    Serial.print((serial_time/100)); // division performed AFTER sync reply
    mode = 0;
    serial_time = 0;
    break;
  case 't':
    Serial.print((sensor_time/100));
    mode = 0;
    sensor_time = 0;
    break;
  case 'u': // may need to disable ACSR or implement a seperate register
    sensor_time = micros(); 
    digitalWrite(sensor_pin, HIGH);
    delay(1000);
    digitalWrite(sensor_pin, LOW);
    mode = 0;
  }
}

void serialEvent()
{
  serial_time = micros();
  mode = Serial.read();
}

ISR(ANALOG_COMP_vect)
{
  sensor_time = micros();
}


