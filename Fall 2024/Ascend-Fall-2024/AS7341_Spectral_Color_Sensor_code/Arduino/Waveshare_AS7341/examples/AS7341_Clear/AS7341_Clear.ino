#include <Debug.h>

#include "DEV_Config.h"
#include "Waveshare_AS7341.h"

void setup() {
DEV_ModuleInit();
DEV_I2C_Init(AS7341_ADDRESS);	
AS7341_EnableLED(false);    
AS7341_disableALL();
Serial.print("All enablers have been turned off ！\r\n");
}

void loop()
{
	
}


