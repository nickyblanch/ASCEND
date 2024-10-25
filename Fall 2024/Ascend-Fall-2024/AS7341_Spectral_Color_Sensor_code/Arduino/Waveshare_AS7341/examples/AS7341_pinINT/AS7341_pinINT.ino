#include <Debug.h>

#include "DEV_Config.h"
#include "Waveshare_AS7341.h"

void setup() {
DEV_ModuleInit();
AS7341_Init(eSpm);
AS7341_EnableSpectralInterrupt(true);
AS7341_ATIME_config(20);//set Integration Time 1s
AS7341_ASTEP_config(17999);
AS7341_AGAIN_config(1);//set gain X1
}

void loop() {

  sModeOneData_t data1;
  AS7341_ClearInterrupt();//Interrupt must be cleared
  if(DEV_Digital_Read(INT_PIN) == 1)
		Serial.print("pinINT is high\r\n"); 
  else
		Serial.print("pinINT is low\r\n"); 	
  AS7341_startMeasure(eF1F4ClearNIR);  
  data1 = AS7341_ReadSpectralDataOne();
  Serial.print("Clear:"); 
  Serial.println(data1.CLEAR);	
	
  if(DEV_Digital_Read(INT_PIN) == 1)
		Serial.print("pinINT is high\r\n"); 
  else
		Serial.print("pinINT is low\r\n"); 
  Serial.print("-----------------------\r\n");
}
