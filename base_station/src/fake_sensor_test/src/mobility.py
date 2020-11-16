#!/usr/bin/env python2.7

import rospy, time, signal, random
from fake_sensor_test.msg import mobility

mobility_pub = rospy.Publisher('/mobility', mobility, queue_size=1)
rospy.init_node('ultrasonic')
m = mobility()

def sigint_handler(signum, frame):
    print 'CTRL+C Pressed!'
    exit()

signal.signal(signal.SIGINT, sigint_handler)

if __name__ == '__main__':
    while True:
        m.current_draw = random.randint(1, 76)
        mobility_pub.publish(m)
        time.sleep(.2)
