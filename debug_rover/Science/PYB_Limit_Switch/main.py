# main.py -- put your code here!
from pyb import Pin, ExtInt
import pyb

RED = pyb.LED(1)
BOOL = True


# Interrupt Handler
def callback(line):
    RED.on()
    pyb.delay(200)
    RED.off()
    global BOOL
    BOOL = False


# External Interrupt Object for the Limit Switch
ext = ExtInt(Pin('X4'), ExtInt.IRQ_FALLING, Pin.PULL_UP, callback)


pyb.LED(2).on()

# Script will not end until limit switch triggers the interrupt
while BOOL:
    pyb.delay(100)

pyb.LED(2).off()