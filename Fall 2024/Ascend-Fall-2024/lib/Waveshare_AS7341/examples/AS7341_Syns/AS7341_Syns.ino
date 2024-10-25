/*
@describe：
In SYNS mode, a falling edge signal to the sensor's GPIO pin is needed 
to trigger the measurement.
After the measurement is completed, the chip will enter IDLE mode.

@note：
The GPIO pin needs a falling edge signal to trigger the chip to work, 
but when the GPIO is idle, it is at a low level. You need a high level signal
to turn to a low level to generate a falling edge signal.
*/
#include <Debug.h>

#include "DEV_Config.h"
#include "Waveshare_AS7341.h"

void setup() {
DEV_ModuleInit();
AS7341_Init(eSyns);
AS7341_ATIME_config(100);
AS7341_ASTEP_config(999);
AS7341_AGAIN_config(6);
}

void loop() {

  sModeOneData_t data1;
  Serial.print("Waiting for the GPIO signal...\r\n");
  AS7341_startMeasure(eF1F4ClearNIR);  
  while(!AS7341_MeasureComplete());
  data1 = AS7341_ReadSpectralDataOne();
  Serial.print("channel1(405-425nm):");
  Serial.println(data1.channel1);
  Serial.print("channel2(435-455nm):");
  Serial.println(data1.channel2);
  Serial.print("channel3(470-490nm):");
  Serial.println(data1.channel3);
  Serial.print("channel4(505-525nm):");   
  Serial.println(data1.channel4);
  Serial.print("Clear:");
  Serial.println(data1.CLEAR);
  Serial.print("NIR:");
  Serial.println(data1.NIR);
  Serial.print("-----------------------\r\n");
}
