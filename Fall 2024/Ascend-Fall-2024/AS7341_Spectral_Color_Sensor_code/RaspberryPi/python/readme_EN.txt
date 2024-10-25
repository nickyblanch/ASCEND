/*****************************************************************************
* | File      	:   Readme_EN.txt
* | Author      :   Waveshare team
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-01-15
* | Info        :   Here is an English version of the documentation for your quick use.
******************************************************************************/
This file is to help you use this Demo.
A brief description of the use of this project is here:

1. Basic information:
This Demo has been verified on the Raspberry Pi 3B+ ;
This Demo has been verified using the AS7341 Spectral Color Sensor module. 
You can view the corresponding test routines in the examples\ of the project;

2. Pin connection:
AS7341    =>    RPI(BCM)
VCC         ->    3.3V/5V
GND         ->    GND
SDA         ->    SDA
SCL         ->    SCL
INT         ->    4
GPIO    ->    -

Note: In SYNS mode, a falling edge signal should be given to the GPIO pin of the sensor to trigger the measurement. 
The GPIO pin will default to low level after the chip is powered on.
So you need to first pull the GPIO up and down to generate a falling edge signal, and a falling edge signal triggers a measurement.After the measurement was done,
The chip will enter the IDLE mode and enter the low-power state.


3.Installation library
    sudo apt-get update
    sudo apt-get install python-pip
    sudo apt-get install python-pil
    sudo apt install python-gpiozero
    sudo pip install smbus

or
    sudo apt-get update
    sudo apt-get install python3-pip
    sudo apt-get install python3-pil
    sudo apt install python3-gpiozero
    sudo pip3 install smbus

4. Basic use:
Test the program in the examples\ directory:
python2
    sudo python data.py

python3
    sudo python3 data.py