unsigned long time = 0;
unsigned long prev = 0;
int drift = 0;

void setup(){
  Serial.begin(9600);
}
void loop(){
  prev = time;
  time = millis();
  drift = (time - prev);
  Serial.println(drift);
  delay(2000);
}
