#!/usr/bin/env python2.7
import rospy
from std_msgs.msg import String

def publisher():
	pub = rospy.Publisher('test_true', String, queue_size=10)
	rospy.init_node('test_publisher', anonymous=True)
	rate = rospy.Rate(10)
	while not rospy.is_shutdown():
		hello = "test data %s"
		rospy.loginfo(hello)
		pub.publish(hello)
		rate.sleep

if __name__=='__main__':
	publisher()
