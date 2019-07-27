# obtained from https://pythonprogramming.net/gpio-example-raspberry-pi/
import RPi.GPIO as gpio
import time

gpio.setmode(gpio.BCM)
gpio.setup(18, gpio.OUT)

while True:
    gpio.output(18, gpio.HIGH)
    entry = raw_input("We build a: ")
	
    if entry == "rover":
        gpio.output(18, gpio.LOW)
        time.sleep(4)
    else:
        gpio.output(18, gpio.HIGH)
        print("Wrong!")	