/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with user
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-12-23
* | Info        :   Here is a Chinese version of the documentation for your quick use.
******************************************************************************/
This file is to help you use this routine.

1.Basic Information：
This routine was developed based on Arduino, and the routines were verified on the Arduino UNO.
This routine is verified by using the AS7341 Spectral Color Sensor module.

2. Code introduction:
You can see that this routine has three test code, its purpose is to test 10 channels of spectral data 
measurement, testWhether the ambient light flicker frequency is 50Hz or 60Hz (ambient light flicker
 requires you to control the LED simulation with other master controlsOne ambient light flicker), 6 
channel spectral data measurement in SYNS mode (need to give the pin of the sensor a down
The falling edge signal triggers the measurement, and the measurement should be done once 
the trigger is triggered. Note that the GPIO pin is low level after the module is powered on, so
GPIO pins need to be pulled up and down to generate a falling edge signal.



3.Basic use：
Since this project is a comprehensive project, you may need to read the following for use:
method 1:
    Copy the entire EPD folder to the libraries folder under the Arduino installation path.
        ..\Arduino\libraries
Method 2:
    Copy the src folder in the EPD folder to
        C:\Users\user_name\Documents\Arduino\libraries
        or ..\document\Arduino\libraries

Then open the corresponding project burn in the examples folder.
