#!/usr/bin/env python2.7
from smbus2 import SMBusWrapper
import time
import rospy
import signal
#from telemetry.msg import led
from mobility.msg import dev_cmds
from mobility.msg import telem_cmds
ADDRESS_LIGHTS = 0x04
ADDRESS_DRVCAM = 0x05

# Global variable declarations
roverMode = 0
frequency = 0
home = 0
pan = 0
tilt = 0
new_pan = False
new_tilt = False
new_home = False

def sigint_handler(signum, frame):
    print("CTRL+C Pressed!")
    exit()

signal.signal(signal.SIGINT, sigint_handler)

def writeToBusLights(roverMode, frequency):
    #if roverMode not in range(11) or frequency not in range(11):
    #return False
    #if type(mode) != int or type(freq) != int:
    #return False
    with SMBusWrapper(1) as bus:
        print(roverMode)
        print(frequency)
        bus.write_byte_data(ADDRESS_LIGHTS, frequency, roverMode)

def writeToBusCamera(home, pan, tilt):
    #if roverMode not in range(11) or frequency not in range(11):
    #return False
    #if type(mode) != int or type(freq) != int:
    #return False
     with SMBusWrapper(1) as bus:
        print(home)
        print(pan)
        print(tilt)
        print(' ')
        bus.write_i2c_block_data(ADDRESS_DRVCAM, home, [pan, tilt])

def callback(data):
    global new_home, new_pan, new_tilt

# Lights
#    roverMode = data.mode
#    frequency = data.freq
#    roverMode = data.data[-1]
#    frequency = data.data[-1]
    roverMode = data.data[3]
    frequency = data.data[4]

# Camera
    home = data.data[0]
    pan = data.data[1]
    tilt = data.data[2]

#    writeToBusLights(roverMode, frequency)

# if the function parameters  are 0 then reset the boolean variables  
    if home == 0:
        new_home = False
    if pan == 0:
        new_pan = False
    if tilt == 0:
        new_tilt = False

# This if-elif chain is to check for excess 1s and -1s
    if not new_home:
        if home == 1:
            new_home = True
            writeToBusCamera(home, pan, tilt)
    
    if not new_pan:
        if pan == 1:
            new_pan = True
            writeToBusCamera(home, pan, tilt)
        elif pan == -1:
            new_pan = True
            writeToBusCamera(home, pan, tilt)
    
    if not new_tilt:
        if tilt == 1:
            new_tilt = True
            writeToBusCamera(home, pan, tilt)
        elif tilt == -1:
            new_tilt = True
            writeToBusCamera(home, pan, tilt)

def led_sub():
    rospy.init_node('leds')
#    rospy.Subscriber("/led", led, callback)
#    rospy.Subscriber("/parser", dev_cmds, callback)
    rospy.Subscriber("/telem", telem_cmds, callback)
#dev_cmds
    rospy.spin()


def main():
    led_sub()

main()
#    if __name__ == '__main__':
#        main()
