#!/usr/bin/env python2.7

import rospy, time, signal, random
from fake_sensor_test.msg import ultrasonic

ultrasonic_pub = rospy.Publisher('/ultrasonic', ultrasonic, queue_size=1)
rospy.init_node('ultrasonic')
u = ultrasonic()

def sigint_handler(signum, frame):
    print 'CTRL+C Pressed!'
    exit()

signal.signal(signal.SIGINT, sigint_handler)

if __name__ == '__main__':
    while True:
        u.max_distance = random.uniform(1.00, 21.00)
        ultrasonic_pub.publish(u)
        time.sleep(.2)

