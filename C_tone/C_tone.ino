// Objective: Produce a Middle C tone with a speaker
// Completed: Works

int pitch = 2;

void setup()
{
  pinMode(8, OUTPUT); 
}
void loop()
{
  //digitalWrite(8, HIGH);
  PORTB|=_BV(0);
  delay(pitch);
  //digitalWrite(8, LOW);
  PORTB&=~_BV(0);
  delay(pitch); 
}

