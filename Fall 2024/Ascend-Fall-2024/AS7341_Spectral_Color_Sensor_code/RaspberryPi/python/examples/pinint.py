import time
import sys
import os
import gpiozero

INI_PIN = 4

libdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'lib')
if os.path.exists(libdir):
    sys.path.append(libdir)

import logging
from waveshare_AS7341 import AS7341

logging.basicConfig(level=logging.INFO)

obj = AS7341.AS7341()

GPIO_INI_PIN = gpiozero.Button(INI_PIN, pull_up = False)

obj.measureMode = 0
obj.AS7341_EnableSpectralInterrupt(1)
obj.AS7341_ATIME_config(20)
obj.AS7341_ASTEP_config(17999)
obj.AS7341_AGAIN_config(1)

try:
    while True:
        obj.AS7341_ClearInterrupt()   
        
        if(GPIO_INI_PIN.value == 1):
            print ('pinINT is high\r\n')
        else:
            print ('pinINT is low\r\n')
            
        obj.AS7341_startMeasure(0)
        obj.AS7341_ReadSpectralDataOne()        
        print('Clear:%d\r\n'%obj.CLEAR)
        obj.AS7341_INTerrupt()

        if(GPIO_INI_PIN.value == 1):
            print ('pinINT is high\r\n')
        else:
            print ('pinINT is low')
            
        print('-----------------------')        
        
except KeyboardInterrupt:    
    logging.info('ctrl + c:')
    exit()
