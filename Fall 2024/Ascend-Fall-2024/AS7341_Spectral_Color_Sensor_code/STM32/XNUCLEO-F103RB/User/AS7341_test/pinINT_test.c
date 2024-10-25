/*****************************************************************************
* | File      	:   pinINT_test.c
* | Author      :   Waveshare team
* | Function    :  The purpose of this program is to teach you how to determine if an interrupt
                   has occurred by the level jump of the pin INT. The interrupt occurs after each 
				   ADC has converted data.
*----------------
* |	This version:   V1.0
* | Date        :   2021-1-21
******************************************************************************/


#include "test.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

#include "DEV_Config.h"
#include <time.h>
#include "Waveshare_AS7341.h"


void pinINT_test(void)
{
  DEV_ModuleInit();
  AS7341_Init(eSpm);
	AS7341_EnableSpectralInterrupt(true);
	AS7341_ATIME_config(20);//set Integration Time 1s
	AS7341_ASTEP_config(17999);
	AS7341_AGAIN_config(1);//set gain X1

	while(1){
	sModeOneData_t data1;
	AS7341_ClearInterrupt();//Interrupt must be cleared
	
	if(DEV_Digital_Read(INT_PIN) == 1)
		printf("pinINT is high\r\n"); 
    else
		printf("pinINT is low\r\n"); 	

	AS7341_startMeasure(eF1F4ClearNIR);  
    data1 = AS7341_ReadSpectralDataOne();
	printf("Clear:%d\r\n",data1.CLEAR);		
	
	if(DEV_Digital_Read(INT_PIN) == 1)
		printf("pinINT is high\r\n"); 
    else
		printf("pinINT is low\r\n"); 
	printf("-----------------------\r\n");
	
	}
		
}
