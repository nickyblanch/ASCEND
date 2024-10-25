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
obj.AS7341_ATIME_config(100)
obj.AS7341_ASTEP_config(999)
obj.AS7341_AGAIN_config(6)
obj.AS7341_EnableLED(False)      #LED Enable
try:
    while True:
        obj.AS7341_ControlLed(True,10)
        obj.AS7341_startMeasure(0)
        obj.AS7341_ReadSpectralDataOne()
        print('channel1(405-425nm):\r\n')
        print('%d\r\n'%obj.channel1)
        print('channel2(435-455nm):\r\n')
        print('%d\r\n'%obj.channel2)
        print('channel3(470-490nm):\r\n')
        print('%d\r\n'%obj.channel3)
        print('channel4(505-525nm):\r\n')   
        print('%d\r\n'%obj.channel4)
        obj.AS7341_startMeasure(1)
        obj.AS7341_ReadSpectralDataTwo()
        print('channel5(545-565nm):\r\n')
        print('%d\r\n'%obj.channel5)
        print('channel6(580-600nm):\r\n')
        print('%d\r\n'%obj.channel6)
        print('channel7(620-640nm):\r\n')
        print('%d\r\n'%obj.channel7)
        print('channel8(670-690nm):\r\n')
        print('%d\r\n'%obj.channel8)
        print('Clear:\r\n')
        print('%d\r\n'%obj.CLEAR)
        print('NIR:\r\n')
        print('%d\r\n'%obj.NIR)
        print('------------------------\r\n')        
        time.sleep(1)
        '''
        Adjust the brightness of the LED lamp     
        '''
        
except KeyboardInterrupt:    
    logging.info('ctrl + c:')
    exit()

