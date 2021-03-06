#####################################################################################
#    Filename: driver.py
#    Authors:      Chary Vielma / Shripal Rawal
#    Emails:       chary.vielma@csu.fullerton.edu / rawalshreepal000@gmail.com
#    Description: Autonomous traversal module - TitanRover2019
#         Given a single GPS coordinate, the Rover will drive to this point (within a
#         predetermined threshold). Driving occurs in a linear fashion.
#         Given a heading and distance (cm), GPS coordinate will be generated and
#         the Rover will drive to this point.
#         Give a heading, the Rover will rotate in place to face this direction.
######################################################################################
import sys
import math
import numpy as np # remove if no longer needed
from decimal import Decimal
import rospy
# 5/30 10:49pmfrom pysaber import DriveEsc
from gnss.msg import gps
from finalimu.msg import fimu
from multijoy.msg import MultiJoy
from sensor_msgs.msg import Joy
from mobility.msg import driver_Status
from time import time, sleep
# 5/30 10:49pm wheels = DriveEsc(128, "mixed")

MINFORWARDSPEED = 20
MAXFORWARDSPEED = 30
TARGETTHRESHOLD = 150  # In cm
CORRECTIONTHRESHOLD = 15  # In degrees
HEADINGTHRESHOLD = 15 # In degrees

class Driver:

    def __init__(self):

        '''
        # Tailored to Runt Rover
        self.__angleX = [5, 15, 25]
        self.__rotateY = [40, 50, 90]
        self.__distanceX = [60, 120]
        self.__speedY = [65, 110]
        '''
        print("Initializing Driver Class")

        # Tailored to Rover
        self.__angleX = [5, 15, 25]
        self.__rotateY = [30, 45, 60]
        self.__distanceX = [30, 45]
        self.__speedY = [30, 45]

        self.__gps = (0.00, 0.00)
        self.__nextWaypoint = (0.00, 0.00)
        self.__heading = 0.0
        self.__targetHeading = 0.0
        self.__headingDifference = 0.0
        self.__clockwise = None
        #self.__deltaDirection = 0.0
        self.__distance = 0.0
        self.__motor1 = 0
        self.__motor2 = 0
        self.__pitch = 0
        
        #create publisher and message objects to publish
        self.driver_pub = rospy.Publisher('/multijoy', MultiJoy, queue_size=1)   #publisher for multijoy
        self.telecommand = Multijoy()
        self.t_joy = Joy() #joy to add to Multijoy
        #variables to mirror the driver_Status topic
        self.autoActive = False
        self.goto_coord = (0.0, 0.0)


    def calculateGps(self, origin, heading, distance):
        '''
        Description:
            Takes a GPS point, heading, and distance and calculates the next GPS point
        Args:
            Heading, Origin --> (lat, lon), and distance in cms
        Returns:
            A tuple (lat, lon)
        '''

        if type(heading) != float or type(heading) != int or type(distance) != int or type(distance) != float:
            print("Only Int or Float allowed") #raise TypeError("Only Int or Float allowed")
            #return

        if type(origin) != tuple:
            print("Only Tuples allowed") # raise TypeError("Only Tuples allowed")
            #return

        heading = math.radians(heading)
        radius = 6371 # km
        dist =  distance / 100000.0
        lat1 , lon1 = origin

        lat1 = math.radians(lat1)
        lon1 = math.radians(lon1)

        lat2 = math.asin( math.sin(lat1)*math.cos(dist/radius) + math.cos(lat1)*math.sin(dist/radius)*math.cos(heading))
        lon2 = lon1 + math.atan2(math.sin(heading)*math.sin(dist/radius)*math.cos(lat1), math.cos(dist/radius)-math.sin(lat1)*math.sin(lat2))

        lat2 = round(math.degrees(lat2), 9)
        lon2 = round(math.degrees(lon2), 9)

        #print("Next GPS", lat2, lon2)
        return (lat2, lon2)
    
    def spiralPoints(self, origin, radius):
        '''
        Description:
            Calculates a set of points located in Concentric circles in order to search the tennis ball
        Args:
            Origin --> (lat, lon), radius in Cms
        Returns:
            A list of waypoints that starts from the farthest point from the center
        '''

        if type(radius) != float or type(radius) != int:
            #raise TypeError("Only Int or Float allowed")
            #return
            print("spiralPoints break - invalid radius", radius)

        if type(origin) != tuple or type(origin[0]) != float or type(origin[0]) != int or type(origin[1]) != float or type(origin[1]) != int:
            #raise TypeError("Only Tuples allowed")
            #return
            print("not float or int")

        center = origin
        spiral = []
        if (radius / 100) % 2 != 0:
            rad = radius - 100
        else:
            rad = radius
        #print(self.calculateGps(center, 0, rad))
        while rad > 0:
            counter =  math.ceil(2 * math.pi * rad / 200)

            #print("Counter = ", counter)
            diff = round(360 / counter, 2)
            head = 0
            while counter > 0:
                point = self.calculateGps(center, head, rad)
                spiral.append(point)
                #print("AT heading ", head)
                head = round(head + diff, 2)
                counter -= 1
            rad -= 200
        return spiral

    def setShouldTurnClockwise(self):
        '''
        Description:
            Sets self.__clockwise to True if shorter turn is clockwise, else False for counterclockwise
        Args:
            None
        Returns:
            Nothing
        '''
        myDict = {}
        myDict[abs(self.__targetHeading - self.__heading)] = self.__targetHeading - self.__heading
        myDict[abs(self.__targetHeading - self.__heading + 360)] = self.__targetHeading - self.__heading + 360 
        myDict[abs(self.__targetHeading - self.__heading - 360)] = self.__targetHeading - self.__heading - 360 
        b = myDict[min(myDict.keys())]
        self.__clockwise = True if b > 0 else False

    def setHeadingDifference(self):
        '''
        Description:
            Calculates and sets self.__headingDifference to degress between self.__heading and self.__targetHeading
        Args:
            None
        Returns:
            Nothing
        '''
        self.__headingDifference = (self.__targetHeading - self.__heading + 360) % 360
        #self.__headingDifference = self.__headingDifference + 360 if self.__headingDifference < -180 else self.__headingDifference
        #print("setHeadingDifference ", self.__headingDifference)

    def setTargetHeading(self):
        '''
        Description:
            Code adapted from https://gist.github.com/jeromer
            Calculates and sets self.__targetHeading given self.__gps and self.__nextWaypoint
        Args:
            None
        Returns:
            Nothing
        '''
        if (type(self.__gps) != tuple) or (type(self.__nextWaypoint) != tuple):
            print("Only tuples allowed") #raise TypeError("Only tuples allowed")

        lat1 = math.radians(self.__gps[0])
        lat2 = math.radians(self.__nextWaypoint[0])

        diffLong = math.radians(self.__nextWaypoint[1] - self.__gps[1])

        x = math.sin(diffLong) * math.cos(lat2)
        y = math.cos(lat1) * math.sin(lat2) - (math.sin(lat1)
                * math.cos(lat2) * math.cos(diffLong))

        initial_heading = math.atan2(x, y)

        initial_heading = math.degrees(initial_heading)
        compass_heading = (initial_heading + 360) % 360

        self.__targetHeading = compass_heading
        #print("setTargetHeading ", self.__targetHeading)

    def setDistance(self):
        '''
        Description:
            Haversine formula - Calculates and sets self.__distance (in cm) given self.__gps 
            and self.__nextWaypoint
        Args:
            None
        Returns:
            Nothing
        '''
        a1, b1 = self.__gps
        a2, b2 = self.__nextWaypoint
        radius = 6371 # km

        da = math.radians(a2-a1)
        db = math.radians(b2-b1)
        a = math.sin(da/2) * math.sin(da/2) + math.cos(math.radians(a1)) \
            * math.cos(math.radians(a2)) * math.sin(db/2) * math.sin(db/2)
        c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
        d = radius * c
        self.__distance = d * 100000
	#print("setDistance ", self.__distance)

    def calculatePitch(self, data):
        if int(data.yaw.pitch) < 0:
            self.__pitch = abs(data.yaw.pitch)
        else:
            self.__pitch = 0

    def sendMotors(self):
        '''
        Description:
        Args:
        Returns:
        '''
        try:
            rospy.Subscriber("imu", fimu, self.calculatePitch)
            #print(self.__pitch, int(self.__motor1 + self.__pitch * self.__motor1 / 50), int(self.__motor2 + self.__pitch * self.__motor2 / 50))
            #wheels.driveBoth(int(self.__motor1 + self.__pitch * self.__motor1 / 60) , int(self.__motor2 + self.__pitch * self.__motor2 / 60))
            self.telecommand.header.stamp.secs = int(time())             #set multijoy timestamp
            self.telecommand.header.stamp.nsecs = time() - int(time())
            self.telecommand.source = 3
            self.telecommand.njoys = 1
            self.t_joy.header = self.telecommand.header   #copy multijoy timestamp
            self.t_joy.axes.append(int(self.__motor1 + self.__pitch * self.__motor1 / 60)/2)        #only set the motors for driving
            self.t_joy.axes.append(int(self.__motor2 + self.__pitch * self.__motor2 / 60)/2)
            for i in range(4):          #all other values set to 0
                self.t_joy.axes.append(0)
            for i in range(18):
                self.t_joy.buttons.append(0)
            self.telecommand.joys.append(self.t_joy)
            self.driver_pub.publish(self.telecommand)

        except:
            print("Error Sending to PySaber")

    def setGps(self, data):
        '''
        Description:
            Retrieves current GPS location, sets self.__gps 
        Args:
            None
        Returns:
            Nothing
        '''
        try:
            self.__gps = (float(data.roverLat), float(data.roverLon))
            #print("setGps ", self.__gps)
        except:
            print("GPS error")

    def setHeading(self, data):
        '''
        Description:
            Retrieves current heading, sets self.__heading
        Args:
            None
        Returns:
            Nothing
        '''
        try:
            self.__heading = float(data.yaw.yaw)
            #print("setHeading", self.__heading)
        except:
            print("Heading error")

    def calculateMotors(self):
        '''
        Description:
            Uses self.__deltaDirection and self.__distance to calculate and set speed and turn values
            for self.__motor1 and self.__motor2.
        Args:
            None
        Returns:
            Nothing
        '''
        self.__motor2 = int(np.interp(self.__headingDifference, self.__angleX, self.__rotateY))
        self.__motor1 = np.interp(self.__distance, self.__distanceX, self.__speedY)
        self.__motor1 = int(self.__motor1 * np.interp(self.__headingDifference,[3,30],[1,0]))
        if not self.__clockwise:
            self.__motor2 = -self.__motor2

    def setMinMaxFwdSpeeds(self, min, max):
        '''
        Description:
            Method overwrites default speedY[min, max] speeds. Confined to MINFORWARDSPEED
            and MAXFORWARDSPEED.
        Args:
            min (int): desired minimum forward speed, max (int): desired maximum forward speed
        Returns:
            Nothing
        '''
        if type(min) != int or type(max) != int:
            raise TypeError("Only integers allowed")
            return

        if max > MAXFORWARDSPEED:
            max = MAXFORWARDSPEED
        if min < MINFORWARDSPEED:
            min = MINFORWARDSPEED
        self.__speedY = [min, max]

    def rotateToHeading(self, newHeading):
        '''
        Description:
            Given a desired heading, Rover will rotate in place until oriented in the given direction
            (within a predetermined threshold).
        Args:
            heading (float): The desired heading the Rover will face.
        Returns:
            Nothing
        '''
        if type(newHeading) != float or type(newHeading) != int:
            raise TypeError("Only float/int allowed")
            #return

        self.__targetHeading = newHeading
        self.setHeading()
        self.setHeadingDifference()
        #self.setDeltaDirection()
        self.setShouldTurnClockwise()
        while self.__headingDifference > HEADINGTHRESHOLD:
            motor2 = ROTATESPEED
            if not self.__clockwise:
                motor2 = -ROTATESPEED
            motor1 = 0
            self.sendMotors()
            sleep(0.04)
            self.setHeading()
            self.setHeadingDifference()
            #self.setDeltaDirection()
            self.setShouldTurnClockwise()

    def goTo(self, point):
        '''
        Description:
            Given one GPS point, method will continuously update GPS, heading, distance, delta direction to reach point (within a predetermined threshold).
        Args:
            point (tuple): Destination waypoint in the form (lat, lon).
            Ex: ( lat (float), lon (float) )
        Returns:
            Nothing
        '''
        if type(point) != tuple:
            print("Only tuple form allowed - exiting goTo") #raise TypeError("Only tuples allowed")
            return
        if type(point[0]) != float and type(point[1]) != float:
            print("Only float/int allowed - exiting goTo") #raise TypeError("Only floats allowed as tuple values")
            return
        self.__nextWaypoint = point
        rospy.Subscriber("gnss", gps, self.setGps)
        rospy.Subscriber("imu", fimu, self.setHeading)
        self.setDistance()
        print(self.__heading, self.__gps)
        while self.__distance > TARGETTHRESHOLD:
            self.setTargetHeading()
            self.setHeadingDifference()
            #self.setDeltaDirection()
            self.setShouldTurnClockwise()
            self.calculateMotors()
            if self.__headingDifference < CORRECTIONTHRESHOLD:
                self.__motor2 = 0
                self.__headingDifference = None
            #else:
            #    rotateToHeading(self.__targetHeading)

            self.sendMotors()
            print("------------------------------------------------")
            print("destWaypoint: ", self.__nextWaypoint, "\ncurrentGPS: ", self.__gps, "\ndist(cm): ", self.__distance, "\ncurrentHeading: ", self.__heading, "\ntargetHeading: ", self.__targetHeading, "\nmotor1: ", self.__motor1, "\nmotor2: ", self.__motor2, "\nclockwise: ", self.__clockwise, "\nheadingDiff: ", self.__headingDifference, "\ntime: ", int(time()), "\n")    
            print("------------------------------------------------")
            sleep(0.04)
            rospy.Subscriber("gnss", gps, self.setGps)
            rospy.Subscriber("imu", fimu, self.setHeading)            
            #print(self.__heading, self.__gps)
            self.setDistance()

        return 0
    def update_Status(self, data):
        self.autoActive = data.autoActive
        self.goto_coord = (data.goto_lat, data.goto_lon)
        if self.autoActive:
            self.goTo(self.goto_coord)
if __name__ == '__main__':
    try:
        rospy.init_node('driver', anonymous=True)
        driver = Driver()
        rospy.Subscriber("/driver_Status", driver_Status, driver.update_Status)
        rospy.spin()
    except rospy.ROSInterruptException:
        quit()
