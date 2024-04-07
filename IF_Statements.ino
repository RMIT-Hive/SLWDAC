
int selection = 0;
int attempts = 0;
void setup() 
{
  // put your setup code here, to run once:
Serial.begin(9600);
delay(50); //gives the program time to print the below statement, code needs time to perform certain operations
Serial.print("\n IF statement example is starting: ");
}

void loop() 
{
 while(Serial.available()) //if the serial terminal is ready to accept new inputs
 {
  
    selection = Serial.parseInt(); //selection is the user input from the serial plotter
    if(selection == 1)
    {
      Serial.print(" \n Option 1 has been selection \n");
      attempts++; // the variable attempts is incremented by 1
    }
    else if(selection == 2)
    {
       Serial.print(" \n Option 2 has been selection \n");
       attempts++;
    }
    else if(selection == 3)
    {
        Serial.print("\n The amount of correct options that have been entered: "); //We are printing a string to the serial monitor
        Serial.print(attempts); //print the variable attempts to the serial monitor
        attempts = 0; //attempts resets
    }
    else //if none of the conditions are met, the code below is performed
    {
      Serial.print(" \n Please input a valid option \n");
       //resets the amount of attempts during an incorrect input
       
    }


 } 
}
