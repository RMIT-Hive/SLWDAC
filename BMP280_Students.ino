

#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h> //this is needed to write and read from EEPROM
#include <stdint.h> // this expands upon common variable types for increased control of size
#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp; // 
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();
unsigned int status;
uint8_t state = 0;
//variables for events

//storage needed in variables
float max_altitude;
float pressure; //4 bytes also 
float temperature;
unsigned long time;

//post flight analysis
float pressure_at_max;
float apogee_event[4]; //will be used to store pressure, temperature and timestamp, and predicted altitude

//address offsets
uint8_t pressure_offset = 0;
uint8_t temperature_offset = 4;
uint8_t time_addr_offset = 8;
uint8_t pressure_max_offset = 12;
uint8_t temperature_max_offset = 16;
uint8_t time_at_max_offset = 20;



void setup() {
 
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb

  Serial.println(F("BMP280 Sensor event test"));;

  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(); // gets the sensor ID from an SPI read operation
  if (!status) { //if the status has failed or is 0 or is not the value it should be. 
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  //needs to be set inside the setup function (default pressure at sea level)
  /* Default settings from datasheet. -> On sensor filtering */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */ //500 is the most stable and accurate

  bmp_temp->printSensorDetails();

}

void loop() {

  //bmp_pressure->getEvent get event creates a list of operations that include:
  //confirming 
//raw measurement from Pressure
switch(state)
{
  case 0: 
  Serial.print("Case 0 \n");
  //error checking again
  status = bmp.sensorID(); //reconfiguring from pressure and temperature
  while(!status) //if status isn't 0 or invalid, if invalid, the switch case will never leave this loop
  { 
    Serial.print("Please check wiring, air pressure sensor not working!\n");
    delay(50); // prevents checks from constantly happening.
    break; 
  }
  state++;
  break;

  case 1:
  //acquire temperature, pressure and time stamp
  temperature = bmp.readTemperature();
  delay(500);
  pressure = bmp.readPressure();
  Serial.print("\n Current Pressure is: ");
  Serial.print(pressure);
  Serial.print("\n");
  Serial.print("\n Current Temperature is: ");
  Serial.print(temperature);
  Serial.print("\n");
  delay(500); //readings from the temp ->delay is due to standby time required for appropriate sampling
  time = millis();
  state++;
  break;

case 2:
delay(10);
if(pressure_at_max == 0) // the variable inside will already be 
//by default this value is 0, we need an initial value provided by the pressure readings
{
 pressure_at_max = pressure;
  Serial.print("\n This should only occur once \n");
  state = 0;
  delay(100);
  break;
}
if(pressure<pressure_at_max) // if the pressure is less than the current max means the sensor is higher than previously
{
  pressure_at_max = pressure;
  Serial.print("\n Ends up at new max \n");
  EEPROM_Write_Event(pressure_max_offset, pressure, temperature_max_offset, temperature, time_at_max_offset, time);
//for the new max being written to the EEPROM
   delay(100);
  break;
}
else
{ //if current event has same or more pressure than the lowest pressure event
 EEPROM_Write_Event(pressure_offset, pressure, temperature_offset, temperature, time_addr_offset, time);// it works holy fuck!
  //extract_eeprom_GET(apogee_event); //extracts EEPROM
  state = 0; 
  delay(100);
break;
}
//End of switch case statement
}
 //end of void loop()
}
//uint8_t pressure_offset = 0;
//uint8_t time_addr_offset = 8;
//uint8_t temperature_offset = 4;
//uint8_t pressure_max_offset = 12;
//uint8_t temperature_max_offset = 16;
//uint8_t time_at_max_offset = 20;

//EEPROM structure -> 
//0-3 will store current pressure
//4-7 will store time stamp of current event
//8-11 will store current temperature
//12-15 will store max pressure
//16-19 will store max temperature (bytes)
//20-23 will be time stamp of lowest pressure

void EEPROM_Write_Event(uint8_t addr_offset_pressure, float pressure, uint8_t addr_offset_temperature, float temperature , uint8_t addr_offset_time, float time)
{
  EEPROM.put(addr_offset_pressure, pressure);
  Serial.print("\n temporary testing PUT: ");
  Serial.print(pressure);
  Serial.print("\n ");
  EEPROM.put(addr_offset_temperature, temperature);
  Serial.print("\n temporary testing PUT: ");
  Serial.print(temperature);
  Serial.print("\n ");
  EEPROM.put(addr_offset_time, time);
  Serial.print("\n temporary testing PUT: ");
  Serial.print(time);
  Serial.print("\n ");
}

void extract_eeprom_GET(float apogee_event[4]) 
//we want the apogee to determine how high we went
{
  float test_float[6];
  for (int i = 0; i<6;i++)
  {
  EEPROM.get(4*i,test_float[i]); //bc float values offset the address by 4 
  }
  apogee_event[0] = test_float[3];
  apogee_event[1] = test_float[4];
  apogee_event[2] = test_float[5];

  apogee_event[3] = 44330*(1-pow(apogee_event[0]/101325,1/5.255)); //equation for altitude
  Serial.print("\n Maximum altitude of flight Event: ");
  Serial.print(apogee_event[3]);
  Serial.print("\n ");
  delay(1000);
}


