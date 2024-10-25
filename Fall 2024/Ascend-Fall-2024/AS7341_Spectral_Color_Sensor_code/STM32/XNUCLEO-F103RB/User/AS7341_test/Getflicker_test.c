/*****************************************************************************
* | File      	:   Getflicker_test.c
* | Author      :   Waveshare team
* | Function    :   This is a process of detecting a specific flicker frequency. 
					This routine is used to detect whether the flicker frequency 
					of the light source is the fixed frequency.
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



void Getflicker_test(void)
{
    DEV_ModuleInit();   
    AS7341_Init(eSpm);
    while(1)
	{
	UBYTE fil_fre;
	fil_fre = AS7341_ReadFlickerData();
    if (fil_fre == 1) {
    printf("Unknown frequency\r\n");		

    } else if (fil_fre == 0 || 2) {	  
	printf("No flicker£¡\r\n");  
    } else {
    printf("%d Hz\r\n",fil_fre);
    }
	}
}
