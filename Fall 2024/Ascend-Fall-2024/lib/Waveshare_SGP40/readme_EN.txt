/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with user
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-07-14
* | Info        :   Here is a Chinese version of the documentation for your quick use.
******************************************************************************/
This file is to help you use this routine.

1.Basic Information：
This routine was developed based on Arduino, and the routines were verified on the Arduino UNO.
This routine is verified by using the SGP40 VOC Sensor.

2. Code introduction:
DEV_Config.cpp/h is the interface
SGP40.cpp/h is the driver file
sensirion_xxx.c/h:  a calculation file provided by sensirion company

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
