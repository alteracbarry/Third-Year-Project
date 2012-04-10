int ROne = LOW;
int RTwo = LOW;
int RThree = LOW;
int RFour = LOW;

void setup()
{
  pinMode(7, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(7, LOW);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(8, LOW);
  
  if ((ROne == HIGH) && (RTwo == HIGH) && (RThree == HIGH))
  {
    RFour = 1-RFour;
  }
  if ((ROne == HIGH) && (RTwo == HIGH))
  { 
    RThree = 1-RThree;
  }
  if (ROne == HIGH)
  {
    RTwo = 1-RTwo;
  }
  
  ROne = 1-ROne;
  digitalWrite(7, ROne);
  digitalWrite(2, RTwo);
  digitalWrite(4, RThree);
  digitalWrite(8, RFour);
  
  Serial.print(RFour);
  Serial.print(RThree);
  Serial.print(RTwo);
  Serial.println(ROne);
  
  delay (1000);
}
