//learning variable types

#include <stdint.h> // this expands upon common variable types for increased control of size
//Different variable types have different intrinsic properties of how a value is stored in memory
int integer = 2000; //
char character = 123;
float float_val = 100.87;
double dbl= 3145;
bool true_or_false = true;
long long_val = -203;
unsigned long pos_long = 2302;


//these variable will NOT be displayed correctly
int false_float = 100.87; // integers cannot store decimal point values
char false_char = 265; // chars will have this value go from 255 to 0 due to its size in memory

//These variable types below are from the special library <stdint.h> 
int8_t byte_int; // stores values from: -128 to 127
uint8_t unsigned_1_byte_int; //1 byte -> stores values from 0 to 255
int16_t two_byte_int; 
uint16_t two_byte_unsigned_int; 
//this is only used if we want to limit the size of certain integer values in memory

void setup() 
{

Serial.begin(9600);
delay(60);
Serial.print("\n How different variable types are stored in memory: \n");
delay(500);

Serial.print(" What is the int value: ");
Serial.print(integer);
Serial.print("\n The size of an int is: ");
Serial.print(sizeof(integer));
delay(500);
Serial.print("\n What is the char value: ");
Serial.print(character);
Serial.print("\n The size of an char is:");
Serial.print(sizeof(character));
delay(500);
Serial.print(" \n What is the float value: ");
Serial.print(float_val);
Serial.print("\n The size of an float is: ");
Serial.print(sizeof(float_val));
delay(500);
Serial.print("\n What is the double value: ");
Serial.print(dbl);
Serial.print("\n The size of an double is: ");
Serial.print(sizeof(dbl));
delay(500);
Serial.print("\n What is the boolean value: ");
Serial.print(true_or_false);
Serial.print("\n The size of an boolean is: ");
Serial.print(sizeof(true_or_false));
delay(500);
Serial.print("\n What is the long value: ");
Serial.print(long_val);
Serial.print("\n The size of an long is: ");
Serial.print(sizeof(long_val));
delay(500);
Serial.print("\n What is the unsigned long value: ");
Serial.print(pos_long);
Serial.print("\n The size of an unsigned long is: ");
Serial.print(sizeof(pos_long));
delay(500);


}
void loop() 
{
  // put your main code here, to run repeatedly:

}
