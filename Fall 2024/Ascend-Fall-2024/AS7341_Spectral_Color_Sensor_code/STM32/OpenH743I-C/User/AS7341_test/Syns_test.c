/*****************************************************************************
* | File      	:   syns_test.c
* | Author      :   Waveshare team
* | Function    :   In SYNS mode, pin GPIO are used to trigger the measurement. 
					Once a falling edge signal is obtained by GPIO, the measurement
					will be triggered.You need to pull the pin GPIO up and down to 
					create a falling edge.
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



void Syns_test(void)
{
    DEV_ModuleInit();
    AS7341_Init(eSyns);

	AS7341_ATIME_config(100);
	AS7341_ASTEP_config(999);
	AS7341_AGAIN_config(6);
	
	while(1){
	sModeOneData_t data1;
	printf("Waiting for the GPIO signal...\r\n");
	AS7341_startMeasure(eF1F4ClearNIR);  
	while(!AS7341_MeasureComplete());	
  data1 = AS7341_ReadSpectralDataOne();
	printf("channel1(405-425nm):\r\n");
	printf("%d\r\n",data1.channel1);
	printf("channel2(435-455nm):\r\n");
  printf("%d\r\n",data1.channel2);
	printf("channel3(470-490nm):\r\n");
	printf("%d\r\n",data1.channel3);
	printf("channel4(505-525nm):\r\n");   
	printf("%d\r\n",data1.channel4);
	printf("Clear:\r\n");
	printf("%d\r\n",data1.CLEAR);
	printf("NIR:\r\n");
	printf("%d\r\n",data1.NIR);
	printf("-----------------------\r\n");
	}
	
}
