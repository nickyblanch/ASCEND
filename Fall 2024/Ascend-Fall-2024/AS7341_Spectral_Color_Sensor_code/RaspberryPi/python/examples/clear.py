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
    obj.AS7341_EnableLED(0)#turn off LED
    obj.AS7341_disableALL()
    print('All enablers have been turned off !')    

except KeyboardInterrupt:    
    logging.info('ctrl + c:')
    exit()

