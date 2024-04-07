
void setup() 
{
  Serial.begin(9600);
  delay(50);
  Serial.print("\n FOR loop example starting");
}

void loop()
 {
  int example = 0; //always starts at 0;
  while(Serial.available())
  {
    example = Serial.parseInt();
    for(int i = example; i>0; i--) // syntax is starting value, ending value, increment
    {
      Serial.print("\n");
      Serial.print(i);
      delay(400);
    }
  Serial.print("\n");
  }
  
}
