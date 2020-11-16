#!/usr/bin/env python
import rospy
from gnss.msg import gps

def callback(data):
    print(data)
    
def listener():

    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("gnss", gps, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()