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

try:
    while True:
       
        fil_fre = obj.AS7341_ReadFlickerData()
        if (fil_fre == 0 or fil_fre == 2): 	   
            print('No flicker!\r\n') 
        elif (fil_fre == 1): 	  
            print('Unknown frequency\r\n')
        else: 
            print('%d Hz\r\n'%fil_fre)

except KeyboardInterrupt:    
    logging.info('ctrl + c:')
    exit()

