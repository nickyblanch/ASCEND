/*****************************************************************************
* | File      	:   INT_test.c
* | Author      :   Waveshare team
* | Function    :   This routine teaches you how to configure the upper and 
				    lower interrupt thresholds and how to detect interrupts
				    when data breaks the set threshold.
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


void INT_test(void)
{

  DEV_ModuleInit();
  AS7341_Init(eSpm);	
	AS7341_EnableSpectralInterrupt(true);
	AS7341_ATIME_config(100);
	AS7341_ASTEP_config(999);
	AS7341_AGAIN_config(6);
	AS7341_SetThreshold(300,10000);//Set the upper and lower thresholds(Notice the relation to the gain)
	AS7341_SetInterruptPersistence(0);
	AS7341_SetSpectralThresholdChannel(4);
	
	while(1){
		
	sModeOneData_t data1;
	AS7341_ClearInterrupt();
	AS7341_startMeasure(eF1F4ClearNIR);  
    data1 = AS7341_ReadSpectralDataOne();
	printf("Clear:%d\r\n",data1.CLEAR);
  	AS7341_INTerrupt();	
	printf("-----------------------\r\n");
	
	}
	
}
