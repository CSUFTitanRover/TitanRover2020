#!/usr/bin/env python
import time
import socket
import rospy
import sys
import signal
from gnss.msg import gps

global base_gps
global rover
global base

global oldTime
global newTime

def sigint_handler(signum, frame):
    print 'CTRL+C Pressed!'
    exit()

signal.signal(signal.SIGINT, sigint_handler)

def connect():
    global base_gps, rover, base

    #connect to the Base Reach
    base = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    while True:
        try:
            base.connect(('base_tr.local', 9092))
#           dataB = base.recv(256).split(" ")
#           base_gps = (data[4], data[5])
#    	    msg.baseLat = str(data[4])
#           msg.baseLon = str(data[5])
	    print("Connection Successful")
#            base.close()
            break
        except:
            print("Connecting to Base Reach")
            time.sleep(2)
    # connect to the Rover Reach
 
#    rover = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#    while True:
#        try:
#            rover.connect(('rover_tr.local', 9091))
#            break
#        except:
#            print("Connecting to Rover Reach")
#            time.sleep(2)


def main():
   global rover, base_gps, base, oldTime, newTime

   while True:
#	newTime = time.time()
#	print(newTime)
#	print(oldTime)
#	if newTime - oldTime > 10:
#		oldTime = newTime
#		print(oldTime)
		try:
		   dataB = base.recv(256).split(" ")
#		   dataR = rover.recv(256).split(" ")
	#		print("Data Received")
		   if dataB is not None and dataR is not None:
			msg.baseLat = str(float(dataB[4]))
		        msg.baseLon = str(float(dataB[5]))
	#		msg.baseLat = str(33.881873)
	#		msg.baseLon = str(-117.882779)
#	                msg.roverLat = str(float(dataR[4])) # str(float(data[4]))
#	                msg.roverLon = str(float(dataR[5])) # str(float(data[5]))
	#		msg.tennisLat = str(float(data[4])) 
	# 		msg.tennsiLat = str(float(data[5]))
	#		print("Publish Message")
		        gps_pub.publish(msg)
	                print(msg)
#			rate.sleep()
	        except:
#		    print(data)
	            print("Error Publishing to ROS")

if __name__ == "__main__":
    msg = gps()
    rospy.init_node('gnss')
    gps_pub = rospy.Publisher('/gnss', gps, queue_size=1)
    rate = rospy.Rate(20) # 10hz
#    oldTime = time.time()
#    newTime = time.time()
    connect()
    main()

