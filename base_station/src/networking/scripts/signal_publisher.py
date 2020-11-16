#!/usr/bin/env python
import rospy, socket, struct, serial, threading, paramiko, os, errno
from functools import wraps
from std_msgs.msg import Int32
from networking.msg import signal
#import message_filters as mf
#from multijoy.msg import MultiJoy
#from sensor_msgs.msg import Joy
from time import sleep

# Import to use DiscoverMasters service
from multimaster_msgs_fkie.srv import DiscoverMasters

base_ubiquiti = "192.168.1.200"
hostName = socket.gethostname()
print("Host: " + hostName)

'''

def talker():
    global RSSI
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    print("sshing into the antenna")
    ssh.connect(base_ubiquiti, username="admin", password="titanrover17")
    #RSSI = 0
    pub = rospy.Publisher('base-sigstrength', Int32, queue_size=1)
    print("making base-sigstrength node")
    rospy.init_node('base-signalstrength', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command("mca-status | grep signal")
        signal = ssh_stdout.readlines()[0]
        signal = int('-' + ''.join(i for i in signal if i.isdigit()))
        RSSI = signal
        print("in while not rospy.is shutdown loop")
        rospy.loginfo(RSSI)
        pub.publish(RSSI)
        rate.sleep()
'''
def main():
    global RSSI
    rate = rospy.Rate(10)
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    print("sshing into the antenna")
    ssh.connect(base_ubiquiti, username="admin", password="titanrover17")
    
    # Wait for the service to be available
    rospy.wait_for_service('/master_discovery/list_masters')

    # Get a handle to the service for multiple calls
    srv = rospy.ServiceProxy('/master_discovery/list_masters', DiscoverMasters)

    # Call DiscoverMasters service
    discovered_masters = srv()

    # Output the number of masters discovered
    print(len(discovered_masters.masters))        
    
    while not rospy.is_shutdown():
        now = rospy.get_time()
        #print("shoot da whoop in da loop")
        ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command("mca-status | grep signal")
        signal_val = ssh_stdout.readlines()[0]
        signal_val = int('-' + ''.join(i for i in signal_val if i.isdigit()))
        msg.base_ubiq=signal_val
        msg.timestamp=now
        rover_pub.publish(msg)
        rospy.loginfo(msg) #loginfo will print the contents of the topic to the local console that ran the command 
        rate.sleep()






if __name__ == '__main__':
    msg = signal()
    rospy.init_node('base_signal_strength', anonymous=True)
    rover_pub = rospy.Publisher('/base_signal_strength', signal, queue_size=1)
    main()
