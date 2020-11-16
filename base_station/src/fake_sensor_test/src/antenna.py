#!/usr/bin/env python2.7

import rospy, time, signal, random
from fake_sensor_test.msg import antenna

antenna_pub = rospy.Publisher('/antenna', antenna, queue_size=1)
rospy.init_node('antenna')
a = antenna()

def sigint_handler(signum, frame):
    print 'CTRL+C Pressed!'
    exit()

signal.signal(signal.SIGINT, sigint_handler)

if __name__ == '__main__':
    while True:
        a.signal_strength = random.randint(1, 51)
        antenna_pub.publish(a)
        time.sleep(.2)

