void setup() 
{
Serial.begin(9600);
Serial.println("Please make an initial choice: ");
}

void loop() 
{
  while(Serial.available())
    {
      int menuchoice = Serial.parseInt();

      switch(menuchoice)
    {
      case 1:
      Serial.print("\n Choice one was selected. You want to read the pressure at the highest recorded altitude. \n");
      break;

      case 2:
      Serial.print("\n Choice two was selected. You want to read the temperature at the highest altitude. \n");
      break;

      case 3:
      Serial.print("\n Choice three was selected. You want to read the time stamp at the highest altitude. \n");
      break;

      case 4:
      Serial.print("\n Choice three was selected. You want to read the highest altitude. \n");
      break;
4
      default: 
      Serial.print("\n Do you want to read either pressure(1), temperature(2), the time(3) or the altitude(4) at apogee? \n");
      break;
    }

    }
}