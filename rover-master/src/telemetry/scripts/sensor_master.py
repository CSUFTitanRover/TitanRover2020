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
'''
import serial 
ser=serial.Serial("/dev/ttyUSB0")
ser.baudrate=9600
try:
    ser.open()
except:
    print "error opening serial"
'''
# Global variable declarations
roverMode = 0
frequency = 0
#home = 0
new_pan = False
new_tilt = False
#new_home = False

def writeToBusLights(roverMode, frequency):
    #if roverMode not in range(11) or frequency not in range(11):
    #return False
    #if type(mode) != int or type(freq) != int:
    #return False
    with SMBusWrapper(8) as bus:
#        print(roverMode)
#        print(frequency)
        bus.write_byte_data(ADDRESS_LIGHTS, frequency, roverMode)

def writeToBusCamera(pan, tilt):
    #if roverMode not in range(11) or frequency not in range(11):
    #return False
    #if type(mode) != int or type(freq) != int:
    #return False
     #print "before write", pan, tilt
     with SMBusWrapper(8) as bus:
#        print(home)
#        print(pan)
#        print(tilt)
#        print(' ')
#        bus.write_i2c_block_data(ADDRESS_DRVCAM, home, [pan, tilt])
        bus.write_byte_data(ADDRESS_DRVCAM, pan, tilt)
#        print(pan, tilt)
#        time.sleep(0.2)
#     time.sleep(0.2)

def callback(data):
#    global new_pan, new_tilt
#    print(data)
    #print(" ")
    pan = data.data[1]
    tilt = data.data[2]
#    with SMBusWrapper(8) as bus:
#        print(home)
#        print(pan)
#        print(tilt)
#        print(' ')
#        bus.write_i2c_block_data(ADDRESS_DRVCAM, home, [pan, tilt])
#        bus.write_byte_data(ADDRESS_DRVCAM, data.data[1], data.data[2])
#        print(pan, tilt)
#        time.sleep(0.2)
    #     pass
    if pan == -1:
      pan = 2
    if tilt == -1:
      tilt = 2
    time.sleep(0.01)
    print pan,tilt
    writeToBusCamera(pan, tilt)
    #ser.write(pan)
    #ser.write(tilt)
#    roverMode = data.mode
#    frequency = data.freq
#    roverMode = data.data[-1]
#    frequency = data.data[-1]
#    roverMode = data.data[3]
#    frequency = data.data[4]
#    writeToBusLights(roverMode, frequency)

# Camera
#    home = data.data[0]
    #pan = data.data[1]
    #tilt = data.data[2]

#    writeToBusLights(roverMode, frequency)

# if the function parameters  are 0 then reset the boolean variables  
#    if home == 0:
#        new_home = False
#    if pan == 0:
#        new_pan = False
#    if tilt == 0:
 #       new_tilt = False

# This if-elif chain is to check for excess 1s and -1s
#    if not new_home:
#        if home == 1:
#            new_home = True
#    writeToBusCamera(1,0) #data.data[1], data.data[2])

#    if not new_pan:
#        if pan == 1:
#            new_pan = True
#            writeToBusCamera(pan, tilt)
#        elif pan == -1:
#            new_pan = True
#            writeToBusCamera(pan, tilt)
    
#    if not new_tilt:
#        if tilt == 1:
#            new_tilt = True
#            writeToBusCamera(pan, tilt)
#        elif tilt == -1:
#            new_tilt = True
#            writeToBusCamera(pan, tilt)
'''
def led_sub():
    rospy.init_node('leds', anonymous = True)
#    rospy.Subscriber("/led", led, callback)
#    rospy.Subscriber("/parser", dev_cmds, callback)
    rospy.Subscriber("/telem", telem_cmds, callback)
#dev_cmds
    rospy.spin()
'''

def main():
#    led_sub()
    rospy.init_node('leds', anonymous = True)
#    rospy.Subscriber("/led", led, callback)
#    rospy.Subscriber("/parser", dev_cmds, callback)
    rospy.Subscriber("/telem", telem_cmds, callback, queue_size=1)
    rospy.spin()

if __name__ == '__main__':
    try:
        main()
    except(KeyboardInterrupt, SystemExit):
        rospy.signal_shutdown("scheduled")
        raise
#while True:
#    roverMode = input("Enter mode: ")
#    frequency = input("Enter frequency: ")
#    writeToBusLights(roverMode, frequency)
#    if __name__ == '__main__':
#        main()
#while True:
#    pan = input("Enter pan: ")
#    tilt = input("Enter tilt: ")
#    writeToBusCamera(pan, tilt)
