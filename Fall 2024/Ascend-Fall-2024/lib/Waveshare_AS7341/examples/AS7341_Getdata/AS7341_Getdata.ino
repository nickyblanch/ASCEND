#include <Debug.h>

#include "DEV_Config.h"
#include "Waveshare_AS7341.h"

void setup() {
DEV_ModuleInit();
Serial.print("IIC ready! Now start initializing AS7341!\r\n");
AS7341_Init(eSpm);
AS7341_ATIME_config(100);
AS7341_ASTEP_config(999);
AS7341_AGAIN_config(6);
AS7341_EnableLED(true);// LED Enable
}

void loop() {
  AS7341_ControlLed(false,10);//Turn on or off the LED and set the brightness of the LED
  sModeOneData_t data1;
  sModeTwoData_t data2;
  AS7341_startMeasure(eF1F4ClearNIR);
  data1 = AS7341_ReadSpectralDataOne();
  Serial.print("channel1(405-425nm):");
  Serial.println(data1.channel1);
  Serial.print("channel2(435-455nm):");
  Serial.println(data1.channel2);
  Serial.print("channel3(470-490nm):");
  Serial.println(data1.channel3);
  Serial.print("channel4(505-525nm):");   
  Serial.println(data1.channel4);
  AS7341_startMeasure(eF5F8ClearNIR);
  data2 =AS7341_ReadSpectralDataTwo();
  Serial.print("channel5(545-565nm):");
  Serial.println(data2.channel5);
  Serial.print("channel6(580-600nm):");
  Serial.println(data2.channel6);
  Serial.print("channel7(620-640nm):");
  Serial.println(data2.channel7);
  Serial.print("channel8(670-690nm):");
  Serial.println(data2.channel8);
  Serial.print("Clear:");
  Serial.println(data2.CLEAR);
  Serial.print("NIR:");
  Serial.println(data2.NIR);
  Serial.print("--------------------------\r\n"); 
  DEV_Delay_ms(500);  
}
