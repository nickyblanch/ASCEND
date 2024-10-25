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
#obj.AS7341_disableALL()
obj.measureMode = 1
obj.AS7341_ATIME_config(100)
obj.AS7341_ASTEP_config(999)
obj.AS7341_AGAIN_config(6)
try:
    while True:

        print('Waiting for the GPIO signal...\r\n')
        obj.AS7341_startMeasure(0)
        while( obj.AS7341_MeasureComplete()== 0):
            time.sleep(0.1)
        obj.AS7341_ReadSpectralDataOne()        
        print('channel1(405-425nm):\r\n')
        print('%d\r\n'%obj.channel1)
        print('channel2(435-455nm):\r\n')
        print('%d\r\n'%obj.channel2)
        print('channel3(470-490nm):\r\n')
        print('%d\r\n'%obj.channel3)
        print('channel4(505-525nm):\r\n')   
        print('%d\r\n'%obj.channel4)
        print('Clear:\r\n')
        print('%d\r\n'%obj.CLEAR)
        print('NIR:\r\n')
        print('%d\r\n'%obj.NIR) 
        print('-----------------------\r\n')        
except KeyboardInterrupt:    
    logging.info('ctrl + c:')
    exit()

