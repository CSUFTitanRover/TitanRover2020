#!/usr/bin/env python2.7

from time import sleep
from deepstream import get
from rviewer import *
import rospy
from fake_sensor_test.msg import imuPygame

import time
startTime = int(round(time.time()))

myViewer = Viewer()

def subscriber():
    rospy.init_node('startviz', anonymous=True)
    rospy.Subscriber("imuGame", imuPygame, callback)
#    rospy.Subscriber("destination", imu, destCallback)
    rospy.spin()

def callback(data):
    motor1 = 0
    motor2 = 0
    currentHeading = data.yaw
    destination = data.destination
    targetDistance = 0
    shouldCW = 0
    headDiff = 0
    myViewer.refreshScreen(motor1, motor2, currentHeading, targetDistance, headDiff, shouldCW)

#def destCallback(data):


#def getTFFromString(str):
#    return True if str == "True" else False

#try:
#    first = get("arrival")
#    lastWaypoint = first["Waypoint"]
#except:
#    lastWaypoint = {}
#    arrival = {}

#while True:
#    sleep(0.3)
#    data = {}
#    try:
#        data = data.yaw  # get data payload
#        arrival = data.dest
#    except:
#        print("rViz could not get deepstream data")
#    if arrival != {}:
#        if arrival["arrivalTime"] != "start":
#            if arrival["Waypoint"] != lastWaypoint:
#                myViewer.flashArrivalMsg(arrival["Waypoint"], arrival["arrivalTime"])
#                lastWaypoint = arrival["Waypoint"]
#    if data == {} or data == "NO_RECORD":
#        continue
    #Then break it out into components and convert types as necessary.
#    motor1 = int(data["motor1"])
#    motor2 = int(data["motor2"])
#    currentHeading = float(data["currentHeading"])
#    targetDistance = float(data["targetDistance"])
#    shouldCW = getTFFromString(str(data["shouldCW"]))
#    headDiff = float(data["headingDifference"])
#    myViewer.refreshScreen(motor1, motor2, currentHeading, targetDistance, headDiff, shouldCW)

if __name__ == '__main__':
    subscriber()
