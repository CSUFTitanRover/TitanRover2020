#!/usr/bin/env python2.7
import time
import signal
import rospy
from telemetry.msg import led

def sigint_handler(signum, frame):
    print("CTRL+C Pressed!")
    exit()

signal.signal(signal.SIGINT, sigint_handler)

ledSet = led()
def sendLightValues():
    pub = rospy.Publisher('/led', led, queue_size = 1)
    rospy.init_node('ledPublisher')
    mode = 10
    freq = 10
    while True:
        mode = input("Enter the rover mode: ")
        freq = input("Enter the rover freq: ")
        ledSet.mode = mode
        ledSet.freq = freq
        pub.publish(ledSet)
        time.sleep(1)

if __name__=='__main__':
    sendLightValues()