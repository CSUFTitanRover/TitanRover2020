import time
import calendar
import paramiko
base_ubiquiti = "192.168.1.200"

from signal import signal, SIGINT
from sys import exit

def handler(signal_received, frame):
    # Handle any cleanup here
    file.close()
    print('SIGINT or CTRL-C detected. Exiting gracefully')
    exit(0)

def logBandwidthUsage():
    global file
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(base_ubiquiti, username="admin", password="titanrover17")
    first_loop = True
    with open("bandwidth_usage_"+str(calendar.timegm(time.gmtime())), "w") as file:
        while True:
            time.sleep(1)
            # file.write("bandwidth info \n")
            ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command("mca-status | grep -e 'wlan.*Rate' -e 'wlan.*Bytes'")

            network_data = ssh_stdout.readlines()
            for index, item in enumerate(network_data):
                network_data[index] = item.strip()
            if(first_loop):
                first_loop = False
                
                headers = []
                for item in network_data:
                    # item.strip()
                    title = item.split('=')[0]
                    headers.extend([title, ','])
                file.write(''.join(headers))
                file.write('\n')
                #print(''.join(headers))
                headers.clear()
            
            for item in network_data:
                value = item.split('=')[1]
                headers.extend([value, ','])
            file.write(''.join(headers))
            file.write('\n')
            #print(''.join(headers))
            headers.clear()

            
            


            # title for title in network_data
            # print(''.join(network_data))

            # signal = int('-' + ''.join(i for i in signal if i.isdigit()))
            # RSSI = signal


if __name__ == "__main__":
    signal(SIGINT, handler)
    logBandwidthUsage()
