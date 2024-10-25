/*****************************************************************************
* | File      	:   Getdata_test.c
* | Author      :   Waveshare team
* | Function    :   Read data of all channels
*----------------
* |	This version:   V1.0
* | Date        :   2021-1-15
******************************************************************************/


#include "test.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

#include "DEV_Config.h"
#include <time.h>
#include "Waveshare_AS7341.h"



void Getdata_test(void)
{   
	
  AS7341_Init(eSpm);
	AS7341_ATIME_config(100);
	AS7341_ASTEP_config(999);
	AS7341_AGAIN_config(6);
	AS7341_EnableLED(false);// LED Enable
  while(1)
	{
		AS7341_ControlLed(true,10);//Turn on or off the LED and set the brightness of the LED
		sModeOneData_t data1;
		sModeTwoData_t data2;
		AS7341_startMeasure(eF1F4ClearNIR);
		data1 = AS7341_ReadSpectralDataOne();
		printf("channel1(405-425nm):\r\n");
		printf("%d\r\n",data1.channel1);
		printf("channel2(435-455nm):\r\n");
		printf("%d\r\n",data1.channel2);
		printf("channel3(470-490nm):\r\n");
		printf("%d\r\n",data1.channel3);
		printf("channel4(505-525nm):\r\n");   
		printf("%d\r\n",data1.channel4);
		AS7341_startMeasure(eF5F8ClearNIR);
		data2 =AS7341_ReadSpectralDataTwo();
		printf("channel5(545-565nm):\r\n");
		printf("%d\r\n",data2.channel5);
		printf("channel6(580-600nm):\r\n");
		printf("%d\r\n",data2.channel6);
		printf("channel7(620-640nm):\r\n");
		printf("%d\r\n",data2.channel7);
		printf("channel8(670-690nm):\r\n");
		printf("%d\r\n",data2.channel8);
		printf("Clear:\r\n");
		printf("%d\r\n",data2.CLEAR);
		printf("NIR:\r\n");
		printf("%d\r\n",data2.NIR);
		printf("--------------------------\r\n");
		DEV_Delay_ms(500);
	}

}
