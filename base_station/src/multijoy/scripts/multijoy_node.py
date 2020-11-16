#!/usr/bin/env python
import rospy, socket, struct, serial, threading, paramiko
import message_filters as mf
from sensor_msgs.msg import Joy
from multijoy.msg import Multi
from time import sleep
base_ubiquiti = "192.168.1.200"
hostName = socket.gethostname()
print("Host: " + hostName)
global RSSI
RSSI = 0

def getRSSI():
    global RSSI
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(base_ubiquiti, username="admin", password="titanrover17")
    while not rospy.is_shutdown():
        ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command("mca-status | grep signal")
        signal = ssh_stdout.readlines()[0]
        signal = int('-' + ''.join(i for i in signal if i.isdigit()))
        RSSI = signal

        '''
def putSock(oData):
    try:
        port = 8888  # Make sure it's within the > 1024 $$ <65535 range
        rover = "192.168.1.2"
        antenna = "192.168.1.168"
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print("s")
        s.connect((antenna, port))
        print("connected")
        s.send(oData)
        print('Sent: ' + oData)
        s.close()
    except Exception as e:
        print("Error in putSock()")
        print(e)
        '''
def packDEEZNUTZ(message, joyNum): #object to bytes
    print("set joystick values")
    try:
        return struct.pack(\
        '2i18b',\
        message.header.stamp.secs,\
        message.header.stamp.nsecs,\
        int(message.joys[joyNum].axes[0]),\
        int(message.joys[joyNum].axes[1]),\
        int(message.joys[joyNum].axes[2]),\
        int(message.joys[joyNum].axes[3]),\
        int(message.joys[joyNum].axes[4]),\
        int(message.joys[joyNum].axes[5]),\
        message.joys[joyNum].buttons[0],\
        message.joys[joyNum].buttons[1],\
        message.joys[joyNum].buttons[2],\
        message.joys[joyNum].buttons[3],\
        message.joys[joyNum].buttons[4],\
        message.joys[joyNum].buttons[5],\
        message.joys[joyNum].buttons[6],\
        message.joys[joyNum].buttons[7],\
        message.joys[joyNum].buttons[8],\
        message.joys[joyNum].buttons[9],\
        message.joys[joyNum].buttons[10],\
        message.joys[joyNum].buttons[11])
    except:
        print("Error in D")

class MultiJoyParser(object):
    
    def __init__(self):

        # Retrieve parameters
        self.ns=rospy.get_name()
	self.param_name_debug=self.ns+'/debug'
        self.param_name_njoys=self.ns+'/njoys'
        
	print "before"
        if rospy.has_param(self.param_name_debug):
            print "in"
            self.debug=rospy.get_param(self.param_name_debug)
        else:
            self.debug=False
        print "after"
        #print rospy.get_param(self.param_name_njoys)
        self.njoys=rospy.get_param(self.param_name_njoys)

        if self.debug:
            rospy.loginfo('debug={}'.format(self.debug))
            rospy.loginfo('njoys={}'.format(self.njoys))

        # Setup ros publisher
        self.multijoy_pub=rospy.Publisher('/multijoy', Multi, queue_size=1)

        # Setup ros subscribers
        self.joy_subs=[mf.Subscriber('/joy/'+str(i),Joy, queue_size=1) for i in xrange(self.njoys)]
        self.timeSync=mf.ApproximateTimeSynchronizer(self.joy_subs, 10, self.njoys*100)
        self.timeSync.registerCallback(self.update)



    def update(self, *args):
        global RSSI
        msg=Multi()
        msg.header.stamp=rospy.Time.now()
        if (hostName == "rover"):
            msg.source = 0
        else:
            msg.source = 1
        msg.njoys.data=self.njoys
        msg.joys=args
        print(msg)

        print(RSSI)
        if True: #hostName == "rover": #(RSSI > -90) or hostName == "tegra-ubuntu":
            self.multijoy_pub.publish(msg)
        else:
            pass
            #putSock(packDEEZNUTZ(msg, 0)) #send to pi to send to radio
            #sleep(0.1)
        if self.debug:
            rospy.loginfo('joys retrieved and published')

if __name__=='__main__':
    RSSI = 0
    #if(hostName != "rover"): #toggle true/false for debuggingg
    #    threading.Thread(target=getRSSI).start()

    rospy.init_node('multijoy_node')
    parser=MultiJoyParser()
    rospy.spin()
    #usb-Silicon_Labs_CP2102_USB_to_UART_Bridge_Controller_0001-if00-port0
