# main.py -- put your code here!
from pyb import Pin, Timer, UART, ADC
import pyb
import time
import _thread
#import cmd

fluidicsPins = { 0 : { 0 : {3 : 'X3',   #PWM - CH3 Timer 2
                            4 : 'X9',   #DIR
                            5 : 'X10'}, #EN
                       1 : {3 : 'X4',   #PWM - CH4 Timer 2
                            4 : 'X11',  #DIR
                            5 : 'X12'}  #EN
                     },
                 1 : { 0 : {3 : 'Y1',   #DC Motor 1 Pin 1
                            4 : 'Y2'},  #DC Motor 1 Pin 2
                       1 : {3 : 'Y3',   #DC Motor 2 Pin 1
                            4 : 'Y4'},  #DC Motor 2 Pin 2
                       2 : {3 : 'Y5',   #DC Motor 3 Pin 1
                            4 : 'Y6'},  #DC Motor 3 Pin 2
                       3 : {3 : 'Y7',   #DC Motor 4 Pin 1
                            4 : 'Y8'}   #DC Motor 4 Pin 2
                     },
                 2 : { 0 : {3 : 'Y9'} }
               }

            #Steppers; 0: Stepper One, 1: Stepper Two
fluidics = { 0 : { 0 : {0 : Pin(fluidicsPins[0][0][5], Pin.OUT_PP).high, #OFF
                        1 : Pin(fluidicsPins[0][0][4], Pin.OUT_PP).high, #CCW
                        2 : Pin(fluidicsPins[0][0][4], Pin.OUT_PP).low,   #CW
                        #'cmd' : 0
                       },
                   1 : {0 : Pin(fluidicsPins[0][0][5], Pin.OUT_PP).high, #OFF
                        1 : Pin(fluidicsPins[0][0][4], Pin.OUT_PP).high, #CCW
                        2 : Pin(fluidicsPins[0][0][4], Pin.OUT_PP).low,   #CW
                        #'cmd' : 0
                       }
                 }, #last is last state
            #Motors; 0: Motor One, 1: Motor Two, 2: Motor Three, 3: Motor Four
            #Only change the second pin to either True or False
             1 : { 0 : {0 : Pin(fluidicsPins[1][0][4], Pin.OUT).high(),  #ON
                        1 : Pin(fluidicsPins[1][0][4], Pin.OUT).low(),   #OFF
                        'cmd' : 0
                        },
                   1 : {0 : Pin(fluidicsPins[1][1][4], Pin.OUT).high(),  #ON
                        1 : Pin(fluidicsPins[1][1][4], Pin.OUT).low(),   #OFF
                        'cmd' : 0
                       },
                   2 : {0 : Pin(fluidicsPins[1][2][4], Pin.OUT).high(),  #ON
                        1 : Pin(fluidicsPins[1][2][4], Pin.OUT).low(),   #OFF
                        'cmd' : 0
                       },
                   3 : {0 : Pin(fluidicsPins[1][3][4], Pin.OUT).high(),  #ON
                        1 : Pin(fluidicsPins[1][3][4], Pin.OUT).low(),   #OFF
                        'cmd' : 0
                       }
                 },
             #Solenoid toggles either on or off
             2 : { 0 : {0 : Pin(fluidicsPins[2][0][3], Pin.OUT).high(),  #ON
                        1 : Pin(fluidicsPins[2][0][3], Pin.OUT).low(),   #OFF
                        'cmd' : 0
                        }
                 }
           }

def run_steppers(fm_cw, fm_ccw, sm_cw, sm_ccw):
    #check all four buttons, first_motor cw, first_motor ccw, second_motor cw, second_motor ccw
    if fm_cw == 1:
        #run first stepper cw
        fluidics[0][0][2]()
    elif fm_ccw == 1:
        #run first stepper ccw
        fluidics[0][0][1]()
    elif sm_cw == 1:
        #run second stepper cw
        fluidics[0][1][2]()
    elif sm_ccw == 1:
        #run second stepper ccw
        fluidics[0][1][1]()
    else:
        #don't run them
        fluidics[0][0][0]()
        fluidics[0][1][0]()

def run_dc(f_m, s_m, t_m, fr_m):
    #check the buttons values to figure out which one to press
    if f_m == 1: #received first 1, but before had 0
        fluidics[1][0][0]()
    else:
        fluidics[1][0][1]()

    if s_m == 1: #received first 1, but before had 0
        fluidics[1][1][0]()
    else:
        fluidics[1][1][1]()

    if t_m == 1: #received first 1, but before had 0
        fluidics[1][2][0]()
    else:
        fluidics[1][2][1]()

    if fr_m == 1: #received first 1, but before had 0
        fluidics[1][3][0]()
    else:
        fluidics[1][3][1]()

'''
    #check to run first motor
    if f_m == 1 and fluidics[1][0]['cmd'] == 0: #received first 1, but before had 0
        fluidics[1][0][1]()
        fluidics[1][0]['cmd'] = 1
    elif f_m == 1 and fluidics[1][0]['cmd'] == 1: #still receving trail of 1's
        pass
    else:
        fluidics[1][0][1]()
        fluidics[1][0]['cmd'] = 0

    #check to run second motor
    if s_m == 1 and fluidics[1][1]['cmd'] == 0: #received first 1, but before had 0
        fluidics[1][1][1]()
        fluidics[1][1]['cmd'] = 1
    elif s_m == 1 and fluidics[1][1]['cmd'] == 1: #still receving trail of 1's
        pass
    else:
        fluidics[1][1][1]()
        fluidics[1][1]['cmd'] = 0

    #check to run third motor
    if t_m == 1 and fluidics[1][2]['cmd'] == 0: #received first 1, but before had 0
        fluidics[1][2][1]()
        fluidics[1][2]['cmd'] = 1
    elif t_m == 1 and fluidics[1][2]['cmd'] == 1: #still receving trail of 1's
        pass
    else:
        fluidics[1][2][1]()
        fluidics[1][2]['cmd'] = 0

    #check to run fourth motor
    if t_m == 1 and fluidics[1][3]['cmd'] == 0: #received first 1, but before had 0
        fluidics[1][3][1]()
        fluidics[1][3]['cmd'] = 1
    elif t_m == 1 and fluidics[1][3]['cmd'] == 1: #still receving trail of 1's
        pass
    else:
        fluidics[1][3][1]()
        fluidics[1][3]['cmd'] = 0
'''


def run_sol(button_val):
'''
    if button_val == 1 and fluidics[2][0]['cmd'] == 0: #received first 1, but before had 0
        fluidics[2][0][1]()
        fluidics[2][0]['cmd'] = 1
    elif button_val == 1 and fluidics[2][0]['cmd'] == 1: #still receving trail of 1's
        pass
    else:
        fluidics[2][0][1]()
        fluidics[2][0]['cmd'] = 0
'''
if button_val == 1: #received first 1, but before had 0
    fluidics[2][0][0]()
else:
    fluidics[2][0][1]()

#use below for reading the serial
'''
def getcommand():
    ser = UART(6, 115200)
    while True:
        try:
            data = ser.read(1)
            if str(data.decode('utf-8')) == 's':
                move = ser.read(4)
                move = move.decode('utf-8')
                if str(move[0]) == 0:
                    if str(move[3]) == 'e':
                        #have the fluidics movement run twice if detected
                        #steppers
                        steppers(move[2], move[3])
                elif str(move[1]) == 1:
                    if str(move[3]) == 'e':
                        #have fluids movement run one if not stepper

        except:
            pass
'''
for i in range(2):
    Pin(fluidicsPins[i][i][5], Pin.OUT_PP).high() #initialize EN to high
    Pin(fluidicsPins[i][i][4], Pin.OUT_PP).high() #initilize DIR to high
    Timer(2, freq=100).channel(i+3, Timer.PWM, pin=Pin(fluidicsPins[i][i][3])).pulse_width_percent(50)

#initizlize both DC motor pins to False, to prevent movement
for i in range(4):
    Pin(fluidicsPins[1][i][3], Pin.OUT).low()
    Pin(fluidicsPins[1][i][4], Pin.OUT).low()

#initializes the solenoid to have a false value so it doesn't moves
Pin(fluidicsPins[2][0][3], Pin.OUT).low()

pyb.LED(2).toggle()
time.sleep(1)
pyb.LED(2).toggle()
while True:
    run_steppers(fm_cw, fm_ccw, sm_cw, sm_ccw)
    run_dc(f_m, s_m, t_m, fr_m)
    run_sol(button_val)

#if __name__ == "__main__":
    #first initializes steppers, sets EN to high to prevent motor from moving
