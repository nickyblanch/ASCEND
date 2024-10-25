/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-12-23
* | Info        :   Here is an English version of the documentation for your quick use.
******************************************************************************/
This file is to help you use this Demo.
A brief description of the use of this project is here:

1. Basic information:
This Demo has been verified on the Raspberry Pi 3B+ ;
This Demo has been verified using the e-paper Driver HAT module. 
You can view the corresponding test routines in the examples\ of the project;

2. Introduction of code:
The examples contains all the test C files.
All library files are in lib.


Note: In SYNS mode, a falling edge signal should be given to the GPIO pin of the sensor to trigger the measurement. 
The GPIO pin will default to low level after the chip is powered on.
So you need to first pull the GPIO up and down to generate a falling edge signal, and a falling edge signal triggers a measurement.After the measurement was done,
The chip will enter the IDLE mode and enter the low-power state.

3.Installation library
Raspberry Pi
    Installation BCM2835
        1.	wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz
        2.	tar zxvf bcm2835-1.60.tar.gz 
        3.	cd bcm2835-1.60/
        4.	sudo ./configure
        5.	sudo make
        6.	sudo make check
        7.	sudo make install
        8.	# More can refer to the official website：http://www.airspayce.com/mikem/bcm2835/
    
    Installation wiringPi
        1.	sudo apt-get install wiringpi
        2.	#For Raspberry Pi 4B you may need to upgrade:
        3.	cd /tmp
        4.	wget https://project-downloads.drogon.net/wiringpi-latest.deb
        5.	sudo dpkg -i wiringpi-latest.deb
        6.	gpio -v
        7.	# Running gpio -v will appear version 2.52, if there is no error, the installation is wrong.
        
    
In the Makefile
    # USELIB = USE_BCM2835_LIB
    # USELIB = USE_WIRINGPI_LIB
    USELIB = USE_DEV_LIB
Raspberry Pi stand by BCM2835, WIRINGPI and DEV_LIB


4. Basic use:
Test the program in the examples\ directory:
    make clean 
    make
    sudo ./main