#include <Debug.h>

#include "DEV_Config.h"
#include "Waveshare_AS7341.h"

void setup() {
DEV_ModuleInit();
AS7341_Init(eSpm);
}

void loop() {

    UBYTE fil_fre;
	fil_fre = AS7341_ReadFlickerData();
    if (fil_fre == 0 || 2) {	
	Serial.println("No flicker!");  
  } else if (fil_fre == 1) {	  
    Serial.println("Unknown frequency");
  } else {
    Serial.print(fil_fre);
    Serial.println("Hz");
  }
}
