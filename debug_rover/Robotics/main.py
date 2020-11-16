# main.py -- put your code here!
from pyb import Pin, Timer, UART, ADC
import pyb
import time
#import _thread
#First driver EN: X12, DIR: X11, Pwm: X1
#Second driver EN: X10, DIR: X9, Pwm: X2
#Third driver EN: X8, DIR: X7, Pwm: X3
#4th driver: EN: X5, Dir: X6, PWM: X4
                   # Pwm      # Dir      # Enab (HIGH = Disable)
armAction = { 0 : {4 : 'X1',  5 : 'X11',  6 : 'X12'},               # CH1 TIM2    Joint 1 ===> low = CLKW,    high = CCW,     freq = 1250  (Top)
              1 : {4 : 'X2',  5 : 'X9',  6 : 'X10'},               # CH2 TIM2    Joint 2 ===> low = DOWN,    high = UP,      freq = 1250  (Front)
              2 : {4 : 'X3',  5 : 'X7',  6 : 'X8'},              # CH3 TIM2    Joint 3 ===> low = CLKW,    high = CCW      freq = 1250  (Top)
              3 : {4 : 'X4',  5 : 'X6', 6 : 'X5'},               # CH4 TIM2    Joint 4 ===> low = OPEN/CLOSE, high = OPEN/CLOSE    freq = 1250  (Front)
              4 : {4 : 'Y7',  5 : 'X19', 6 : 'X20'}               # CH1 TIM12    Joint 5 ===> low = CLKW, high = CCW    freq = 1250  (Front)
              #note: X1 to X12 currently taken up
            }
                       # Counter Clockwise / Left                  # Clockwise / Right                          # Stop                                       # Start
movements = { 0 : {4 : Pin(armAction[0][5], Pin.OUT_PP).high, 5 : Pin(armAction[0][5], Pin.OUT_PP).low, 6 : Pin(armAction[0][6], Pin.OUT_PP).high, 7 : Pin(armAction[0][6], Pin.OUT_PP).low},
                       # UP                                         # Down                                      # Stop                                       # Start
              1 : {4 : Pin(armAction[1][5], Pin.OUT_PP).high, 5 : Pin(armAction[1][5], Pin.OUT_PP).low, 6 : Pin(armAction[1][6], Pin.OUT_PP).high, 7 : Pin(armAction[1][6], Pin.OUT_PP).low},
                       # Counter Clockwise / Left                  # Clockwise / Right                          # Stop                                       # Start
              2 : {4 : Pin(armAction[2][5], Pin.OUT_PP).high, 5 : Pin(armAction[2][5], Pin.OUT_PP).low, 6 : Pin(armAction[2][6], Pin.OUT_PP).high, 7 : Pin(armAction[2][6], Pin.OUT_PP).low},
                       # Close / Open                               # Close / Open                              # Stop                                       # Start
              3 : {4 : Pin(armAction[3][5], Pin.OUT_PP).high, 5 : Pin(armAction[3][5], Pin.OUT_PP).low, 6 : Pin(armAction[3][6], Pin.OUT_PP).high, 7 : Pin(armAction[3][6], Pin.OUT_PP).low},
                       # Counter Clockwise / Left                  # Clockwise / Right                          # Stop                                       # Start
              4 : {4 : Pin(armAction[4][5], Pin.OUT_PP).high, 5 : Pin(armAction[4][5], Pin.OUT_PP).low, 6 : Pin(armAction[4][6], Pin.OUT_PP).high, 7 : Pin(armAction[4][6], Pin.OUT_PP).low}
            }
                   # CCW / Left           # Clockwise / Right    # Stop                 # Start
ledMove = { 0 : {4 : pyb.LED(1).on, 5 : pyb.LED(1).on, 6 : pyb.LED(1).off, 7 : pyb.LED(1).on},
                   # UP                   # Down                 # Stop                 # Start
            1 : {4 : pyb.LED(2).on, 5 : pyb.LED(2).on, 6 : pyb.LED(2).off, 7 : pyb.LED(2).on},
                   # CCW / Left           # Clockwise / Right    # Stop                 # Start
            2 : {4 : pyb.LED(3).on, 5 : pyb.LED(3).on, 6 : pyb.LED(3).off, 7 : pyb.LED(3).on},
                   # Close / Open         # Close / Open         # Stop                 # Start
            3 : {4 : pyb.LED(4).on, 5 : pyb.LED(4).on, 6 : pyb.LED(4).off, 7 : pyb.LED(4).on}
                   # CCW / Left           # Clockwise / Right    # Stop                 # Start
            #4 : {4 : pyb.LED(4).on, 5 : pyb.LED(4).on, 6 : pyb.LED(4).off, 7 : pyb.LED(4).on}
            }
#  SAMPLE COMMAND READ 8##9

def getcommand():
    ser = UART(6, 115200)
    while True:
        try:
            data = ser.read(1)
            if str(data.decode('utf-8')) == 's':
                move = ser.read(3)
                move = move.decode('utf-8')
                if str(move[2]) == 'e':
                    #ledMove[int(move[0])][int(move[1])]()
                    pyb.LED(3).toggle();
                    movements[int(move[0])][int(move[1])]()
                    pyb.LED(3).toggle();
        except:
            pass

if __name__ == "__main__":
    for i in range(4): #movements, armAction, and ledMove are arrays, an array of 4, will be 5 since a 5th motor to be added
    #armAction setting up the pins on the board to specify what is the en, dir, and pulse_width_percent
    #movments detailing what way to move or Stop
    #ledMove lights on the board light up to signal what and how things are moving
        Pin(armAction[i][6], Pin.OUT_PP).high()
        Pin(armAction[i][5], Pin.OUT_PP).high()
        Timer(2, freq=1250).channel(i+1, Timer.PWM, pin=Pin(armAction[i][4])).pulse_width_percent(50)
    Pin(armAction[4][6], Pin.OUT_PP).high()
    Pin(armAction[4][5], Pin.OUT_PP).high()
    Timer(12, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[4][4])).pulse_width_percent(50)
    pyb.LED(2).toggle()
    time.sleep(1)
    pyb.LED(2).toggle()
    getcommand()



'''
#from pyb import Pin, Timer, LED, UART, ADC
#import time
#import pyb
for i in range(2): #movements, armAction, and ledMove are arrays, an array of 4, will be 5 since a 5th motor to be added
#armAction setting up the pins on the board to specify what is the en, dir, and pulse_width_percent
#movments detailing what way to move or Stop
#ledMove lights on the board light up to signal what and how things are moving
    Pin(armAction[i][6], Pin.OUT_PP).high()
    Pin(armAction[i][5], Pin.OUT_PP).high()
    Timer(2, freq=1250).channel(i+1, Timer.PWM, pin=Pin(armAction[i][4])).pulse_width_percent(50)
pyb.LED(2).toggle()
time.sleep(5)
pyb.LED(2).toggle()
#p = Pin(armAction[2][4]) # using CH2 and TIM8 Pin('Y2')
#q = Pin(armAction[2][5], Pin.OUT_PP) #another way to write Pin('Y11', Pin.OUT_PP)
#r = Pin(armAction[2][6], Pin.OUT_PP)
#r = Pin('X6', Pin.OUT_PP)
Pin(armAction[0][6], Pin.OUT_PP).low()
Pin(armAction[0][5], Pin.OUT_PP).low()
Pin(armAction[1][6], Pin.OUT_PP).low()
Pin(armAction[1][5], Pin.OUT_PP).low()
Pin(armAction[4][6], Pin.OUT_PP).low()
Pin(armAction[4][5], Pin.OUT_PP).low()
Timer(2, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[0][4])).pulse_width_percent(50)
Timer(2, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[1][4])).pulse_width_percent(50)
Timer(8, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[4][4])).pulse_width_percent(50)
pyb.LED(3).toggle()
time.sleep(4)
Timer(2, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[0][4])).pulse_width_percent(0)
Timer(2, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[1][4])).pulse_width_percent(0)
Timer(8, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[4][4])).pulse_width_percent(0)
pyb.LED(3).toggle()

time.sleep(2) #2 seconds break then continue

Pin(armAction[0][5], Pin.OUT_PP).high()
Pin(armAction[1][5], Pin.OUT_PP).high()
Pin(armAction[4][5], Pin.OUT_PP).high()
Timer(2, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[0][4])).pulse_width_percent(50)
Timer(2, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[1][4])).pulse_width_percent(50)
Timer(8, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[4][4])).pulse_width_percent(50)
pyb.LED(3).toggle()
time.sleep(4)
Timer(2, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[0][4])).pulse_width_percent(0)
Timer(2, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[1][4])).pulse_width_percent(0)
Timer(8, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[4][4])).pulse_width_percent(0)
pyb.LED(3).toggle()
'''

'''
# main.py -- put your code here!
#from pyb import Pin, Timer, LED, UART, ADC
#import time
#import pyb
p = Pin('X2') # X1 has TIM2, CH1
q = Pin('X9', Pin.OUT_PP)
p2 = Pin('Y2') # X1 has TIM2, CH1
q2 = Pin('X19', Pin.OUT_PP)

q.high()
q2.high()
tim = Timer(2, freq=1250)
ch = tim.channel(2, Timer.PWM, pin=p)
ch.pulse_width_percent(50)
tim2 = Timer(8, freq=1250)
ch2 = tim2.channel(2, Timer.PWM, pin=p2)
ch2.pulse_width_percent(50)
pyb.LED(2).toggle()
time.sleep(4)
ch.pulse_width_percent(0)
ch2.pulse_width_percent(0)
pyb.LED(2).toggle()

time.sleep(2)
#code above moves the motor for 5 seconds in the clockwise direction
#using channel 4 and timer 2
q.low()
q2.low()
ch.pulse_width_percent(50)
ch2.pulse_width_percent(50)
pyb.LED(2).toggle()
time.sleep(4)
ch.pulse_width_percent(0)
ch2.pulse_width_percent(0)
pyb.LED(2).toggle()
'''

'''
# main.py -- put your code here!
from pyb import Pin, Timer, LED, UART, ADC
import time
import pyb
p = Pin('X1') # X1 has TIM2, CH1
q = Pin('X2', Pin.OUT_PP)
q.low()
tim = Timer(2, freq=1250)
ch = tim.channel(1, Timer.PWM, pin=p)
ch.pulse_width_percent(50)
time.sleep(1)
ch.pulse_width_percent(0)
ser = UART(1, 115200)                         # init with given baudrate
#ser.init(9600, bits=8, parity=None, stop=1) # init with given parameters
# FeedBack Shit HERE
feed = ADC(Pin('Y12'))
pin1_a = Pin('X12', Pin.IN)
pin2_b = Pin('X11', Pin.IN)
pin3_ind = Pin('X22', Pin.IN)
while True:
    lol = pin1_a.value() # read value, 0-4095
    lol2 = pin2_b.value() # read value, 0-4095
    ser.write(str(lol) + str(lol2))
    if int(lol) < 10:
        lol = "000" + str(lol)
    elif int(lol) < 100:
        lol = "00" + str(lol)
    elif int(lol) < 1000:
        lol = "0" + str(lol)
    #ser.write(str(lol))
    time.sleep(.1)
ser = UART(1, 9600)                         # init with given baudrate
p = Pin('X1') # X1 has TIM2, CH1
q = Pin('X2', Pin.OUT_PP)
#r = Pin('X5', Pin.OUT_PP)
#s = Pin('X3')
#t = Pin('X4', Pin.OUT_PP)
q.high()
#r.low()
#s.low()
tim1 = Timer(2, freq=1250)
ch1 = tim1.channel(1, Timer.PWM, pin=p)
ch1.pulse_width_percent(50)
time.sleep(1)
while True:
    data = ser.read(1)
    if int(data) is 0:
        r.low()
        break
    elif int(data) is 1:
        r.high()
        break
tim1 = Timer(2, freq=1250)
ch1 = tim1.channel(1, Timer.PWM, pin=p)
#tim2 = Timer(2, freq=1250)
#ch2 = tim2.channel(3, Timer.PWM, pin=r)
ch1.pulse_width_percent(50)
#ch2.pulse_width_percent(50)
time.sleep(2)
ch1.pulse_width_percent(0)
#ch2.pulse_width_percent(0)
ser = UART(1, 9600)                         # init with given baudrate
#ser.init(9600, bits=8, parity=None, stop=1) # init with given parameters
while True:
    data = ser.read(1)
    if int(data) > 5:
        LED(4).toggle()
    else:
        LED(3).toggle()
armAction = { 0 : {'pwm' : 'X1', 'dir' : 'X2'},         # low = CW   , high = CCW   //// freq = 1250  (Top)
              1 : {'pwm' : 'X3', 'dir' : 'X4'},         # low = Down , high = up    //// freq = 1250  (Front)
              2 : {'pwm' : 'X5', 'dir' : 'X6'},         # low = CW   , high = CCW   //// freq = 1250  (Top)
              3 : {'pwm' : 'XX', 'dir' : 'XX'}          # low =  , high =     //// freq = 1250
            }
#for i in range(len(armAction)):
#    pyb.Pin(armAction[i]['pwm'], pyb.Pin.OUT_PP)
#    pyb.Pin(armAction[i]['dir'], pyb.Pin.OUT_PP)
p = pyb.Pin('X1', pyb.Pin.OUT_PP)
q = pyb.Pin('X2', pyb.Pin.OUT_PP)
#r = pyb.Pin('X3', pyb.Pin.OUT_PP)
#s = pyb.Pin('X4', pyb.Pin.OUT_PP)
q.low()
#q.high()
for i in range(150):
    p.high()
    time.sleep_us(1000)
    p.low()
    time.sleep_us(1000)
'''
