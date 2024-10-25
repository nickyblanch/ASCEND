import time
import sys
import os

libdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'lib')
if os.path.exists(libdir):
    sys.path.append(libdir)

import logging
from waveshare_AS7341 import AS7341

logging.basicConfig(level=logging.INFO)

obj = AS7341.AS7341()
obj.measureMode = 0
obj.AS7341_EnableSpectralInterrupt(1)
obj.AS7341_ATIME_config(100)
obj.AS7341_ASTEP_config(999)
obj.AS7341_AGAIN_config(6)
obj.AS7341_SetThreshold(300,10000)
obj.AS7341_SetInterruptPersistence(0)
obj.AS7341_SetSpectralThresholdChannel(4)
	
try:
    while True:
        obj.AS7341_ClearInterrupt() 
        obj.AS7341_startMeasure(0)
        obj.AS7341_ReadSpectralDataOne()        
        print('Clear:%d\r\n'%obj.CLEAR)
        obj.AS7341_INTerrupt()
        print('-----------------------\r\n')        
        
except KeyboardInterrupt:    
    logging.info('ctrl + c:')
    exit()

