#include <Debug.h>

#include "DEV_Config.h"
#include "Waveshare_AS7341.h"

void setup() {
DEV_ModuleInit();
AS7341_Init(eSpm);
AS7341_EnableSpectralInterrupt(true);
AS7341_ATIME_config(100);
AS7341_ASTEP_config(999);
AS7341_AGAIN_config(6);
AS7341_SetThreshold(300,10000);//Set the upper and lower thresholds(Notice the relation to the gain)
AS7341_SetInterruptPersistence(0);
AS7341_SetSpectralThresholdChannel(4);

}

void loop() {

  sModeOneData_t data1;
  AS7341_ClearInterrupt();
  AS7341_startMeasure(eF1F4ClearNIR);
  data1 = AS7341_ReadSpectralDataOne();
 // Serial.print("Clear:%d\r\n",data1.CLEAR);  
  Serial.print("Clear:"); 
  Serial.println(data1.CLEAR);
  AS7341_INTerrupt();
  Serial.print("-----------------------\r\n");  
  
}
