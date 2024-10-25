/*****************************************************************************
* | File      	:   clear.c
* | Author      :   Waveshare team
* | Function    :   DisEnable all
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

void Clear_all(void)
{
  DEV_ModuleInit();
	DEV_I2C_Init(AS7341_ADDRESS<<1);
	
	AS7341_EnableLED(false);    
	AS7341_disableALL();
	printf("All enablers have been turned off ！\r\n");

}
