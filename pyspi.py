#!/usr/bin/env python
#
#Here goes nothing...

import time
import sys
import spidev

####Command array####
commands = bytes([0x61, 0x62, 0x63, 0x64])
#####################


##### Breaker 1 #####

#indicate GPIO pin
spi = spidev.SpiDev()
spi.open(0,0)
while True:
    resp = spi.xfer2(commands)
    print(resp[0])
    time.sleep(1)

#####################
