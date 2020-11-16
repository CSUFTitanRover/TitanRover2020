#!/usr/bin/env python3.5
import rospy
from sensor_msgs.msg import LaserScan
from finalimu.msg import fimu as imu

def callback(data):
    print('+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++')
    print(data.ranges)

def cccccc(data):
    print('====================================================================================')
    print(data.yaw.yaw)

def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("scan", LaserScan, callback)
    rospy.Subscriber("imu", imu, cccccc)
    rospy.spin()

if __name__ == '__main__':
    listener()

