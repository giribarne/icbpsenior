#!/usr/bin/env python
#
#Here goes nothing...

import time
import sys
import spidev
import struct

####Command array####

#####################

####Set Up###########

#####################

connect = False;

voltage = [0,0,0,0]
current = [0,0,0,0]
power = [0,0,0,0]
raw = 0
raw2 = 0
raw3 = 0
#value =[]
#value2 = []
#value3 = []

##### Breaker 1 #####

#indicate GPIO pin
spi = spidev.SpiDev()
speed = 2000000
spi.open(0,0)
spi.max_speed_hz = speed

connect = True;
while connect:
#voltage
    print ("Voltage: ")
    voltage[0] = spi.xfer2([0x03])
    print ("1: ")
    print (voltage[0])
    voltage[1] = spi.xfer2([0x02])
    print ("2: ")
    print (voltage[1])
    voltage[2] = spi.xfer2([0x01])
    print ("3: ")
    print (voltage[2])
    voltage[3] = spi.xfer2([0x04])
    print ("4: ")
    print (voltage[3])
    print (" ")
#convert
    raw = [int(i[0]) for i in voltage]
    #value = [s.replace('0b', '') for s in raw]
    #value = [s.rjust(8, '0') for s in value]
    #value = '//'.join(map(bin, raw))
    #struct.unpack('>f', raw)[0]

    print ("Float value: ")
    print(raw)
    print ("\n")
    
#current
    current[0] = spi.xfer2([0x07])
    print ("1: ")
    print (current[0])
    current[1] = spi.xfer2([0x06])
    print ("2: ")
    print (current[1])
    current[2] = spi.xfer2([0x05])
    print ("3: ")
    print (current[2])
    current[3] = spi.xfer2([0x08])
    print ("4: ")
    print (current[3])
#convert
    raw2 = [bin(i[0]) for i in current]
    print(raw2)
    
    value2 = ''.join(map(str, raw2))
    print ("Float value: ")
    print (float(int(value2, 16)))
    print ("\n")

#power
    power[0] = spi.xfer2([0x09])
    print ("1: ")
    print (power[0])
    power[1] = spi.xfer2([0x0A])
    print ("2: ")
    print (power[1])
    power[2] = spi.xfer2([0x0B])
    print ("3: ")
    print (power[2])
    power[3] = spi.xfer2([0x0C])
    print ("4: ")
    print (power[3])
#convert
    raw3 = [bin(i[0]) for i in power]
    print(raw3)
    
    value3 = ''.join(map(str, raw3))
    print ("Float value: ")
    print (float(int(value3, 16)))
    print ("\n")
    connect = False;
    
spi.close()

#Breaker 2#
####################
