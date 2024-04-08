# Hardware / boards
## Microcontroller
ATMega328a, installed onto Littlebird (purple) board.

## Sensor
BMP280 installed onto Adafruit board. Acts as a pressure and temperature sensor. The altitude above sealevel can be determined based on the air pressure.

Altitude = 44330 * (1 - (P / P_s)^1/5.255)

- P -> Measured pressure
- P_s -> Sea level pressure (at given temperature)
- 44330, 5.225 are both constants

# Pinout

| BMP280 (Black board) pin | Littlebird (Purple board) pin | Purpose |
| --- | --- | --- |
| Vin | 5V | Power connection. Supplies 5V to power BMP280 from USB connector.|
| GND | GND | Ground connection. Can be any GND on the Littlebird Board. |
| SDI | A4 | Serial data line. Used to express stream of data (1s and 0s) by changing voltage (3V to 0V) at a set frequency. |
| SCK | A5 | Serial clock line. Used to provide a clock signal to synchronise serial data line. |
