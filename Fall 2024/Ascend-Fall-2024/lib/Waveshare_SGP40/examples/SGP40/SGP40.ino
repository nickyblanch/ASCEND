#include "DEV_Config.h"
#include "SGP40.h"

UBYTE voc = 0;
void setup() {
  if(SGP40_Init() != 0){
      Serial.print("init err!!!");
      return 0;
  }
  
}

void loop() {
  //SGP40_MeasureRaw(25, 50);
  voc = SGP40_MeasureVOC(25, 50);
  Serial.print("voc = ");
  Serial.println(voc);
  
}
