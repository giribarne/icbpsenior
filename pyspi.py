#!/usr/bin/env python
#
#Here goes nothing...

import time
import sys
import spidev

####Command array####

#####################

####Set Up###########

#####################

connect = False;

raw = 1
data = 1
collection = 1
test = 1

string = ""

##### Breaker 1 #####

#indicate GPIO pin
spi = spidev.SpiDev()
speed = 2000000
spi.open(0,0)
spi.max_speed_hz = speed

connect = True;
while connect:
    raw = spi.xfer2([2])
    print ("1: ")
    print (raw)
    data = spi.xfer2([3])
    print ("2: ")
    print (data)
    collection = spi.xfer2([4])
    print ("3: ")
    print (collection)
    test = spi.xfer2([1])
    print ("4: ")
    print (test)
    connect = False;
    
spi.close()
#####################
