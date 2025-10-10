#ifndef _SGP40_H_
#define _SGP40_H_

#include "DEV_Config.h"
#include "Debug.h"
#include "DEV_Config.h"

extern "C" {
#include "sensirion_arch_config.h"
#include "sensirion_voc_algorithm.h"
};


#define SGP40_ADDR       (0x59)

/***********************************************************************************/
UBYTE SGP40_Init(void);
UBYTE SGP40_MeasureRaw(float temp, float humi);
UBYTE SGP40_MeasureVOC(float temp, float humi);

#endif
