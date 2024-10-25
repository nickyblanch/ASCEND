This routine contains three functional sections of code in the main function
It's actually described in detail in the routine and how to use it, so again, right

1. Measurement of spectral data of 10 channels. This code is implemented by default in the project
Note: The filling LED in the module is turned off by default. If you want to turn it on, please uncomment 
the LED in AS7341_init () in AS7341.cEnable function and uncomment the brightness control function of 
the LED in the main function

2. Test whether the flashing frequency of ambient light is 50Hz or 60Hz
To test this function, simply comment out the code snippet in 1 and uncomment the code snippet that measures flicker frequency
Note: The flicker frequency of ambient light is only tested by the two classical values of 50Hz or 60Hz. 
Please use the LED driven by other master chip to simulate oneThe corresponding flicker environment

3. Measurement in SYNS mode
To test this feature, you need to first set the mode to SYNS in AS7341_Init() in as7341.c and then comment the irrelevant code in the main function
Uncomment the related code
Note: In SYNS mode, a falling edge signal should be given to the GPIO pin of the sensor to trigger the measurement. 
The GPIO pin will default to low level after the chip is powered on.
So you need to first pull the GPIO up and down to generate a falling edge signal, and a falling edge signal triggers a measurement.After the measurement was done,
The chip will enter the IDLE mode and enter the low-power state.