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
armAction = { 0 : {4 : 'X1',  5 : 'X11',  6 : 'X12'},               # CH1 TIM2    Joint 1 ===> low = CLKW,    high = CCW,     freq = 1250  (Top)     Motor: NEMA 23
              1 : {4 : 'X2',  5 : 'X9',  6 : 'X10'},                # CH2 TIM2    Joint 2 ===> low = DOWN,    high = UP,      freq = 1250  (Front)   Motor: NEMA 23
              2 : {4 : 'X3',  5 : 'X7',  6 : 'X8'},                 # CH3 TIM2    Joint 3 ===> low = CLKW,    high = CCW      freq = 1250  (Top)     Motor: NEMA 23
              3 : {4 : 'X4',  5 : 'X6', 6 : 'X5'},                  # CH4 TIM2    Joint 5 ===> low = CLKW,    high = CCW      freq = 1250  (Front)   Motor: NEMA 11
              4 : {4 : 'Y7',  5 : 'X19', 6 : 'X20'}                 # CH1 TIM12   Joint 6 ===> low = EXTD,    high = RTRCT    freq = 1250  (Front)   Motor: Hall Effect Linear Hybrid
              #note: X1 to X12 currently taken up
            }
                       # Counter Clockwise / Left                  # Clockwise / Right                          # Stop - EN on to prevent movement         # Start - EN off to allow movement
movements = { 0 : {4 : "Pin(armAction[0][5], Pin.OUT_PP).high()", 5 : "Pin(armAction[0][5], Pin.OUT_PP).low()", 6 : "Timer(2, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[0][4])).pulse_width_percent(0)", 7 : "Timer(2, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[0][4])).pulse_width_percent(50)"},
                       # UP                                         # Down                                      # Stop                                       # Start
              1 : {4 : "Pin(armAction[1][5], Pin.OUT_PP).high()", 5 : "Pin(armAction[1][5], Pin.OUT_PP).low()", 6 : "Timer(2, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[1][4])).pulse_width_percent(0)", 7 : "Timer(2, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[1][4])).pulse_width_percent(50)"},
                       # Counter Clockwise / Left                  # Clockwise / Right                          # Stop                                       # Start
              2 : {4 : "Pin(armAction[2][5], Pin.OUT_PP).high()", 5 : "Pin(armAction[2][5], Pin.OUT_PP).low()", 6 : "Timer(2, freq=1250).channel(3, Timer.PWM, pin=Pin(armAction[2][4])).pulse_width_percent(0)", 7 : "Timer(2, freq=1250).channel(3, Timer.PWM, pin=Pin(armAction[2][4])).pulse_width_percent(50)"},
                       # Counter Clockwise / Left                  # Clockwise / Right                          # Stop                                       # Start
              3 : {4 : "Pin(armAction[3][5], Pin.OUT_PP).high()", 5 : "Pin(armAction[3][5], Pin.OUT_PP).low()", 6 : "Timer(2, freq=1250).channel(4, Timer.PWM, pin=Pin(armAction[3][4])).pulse_width_percent(0)", 7 : "Timer(2, freq=1250).channel(4, Timer.PWM, pin=Pin(armAction[3][4])).pulse_width_percent(50)"},
                       # Counter Clockwise / Left                  # Clockwise / Right                          # Stop                                       # Start
              4 : {4 : "Pin(armAction[4][5], Pin.OUT_PP).high()", 5 : "Pin(armAction[4][5], Pin.OUT_PP).low()", 6 : "Timer(12, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[4][4])).pulse_width_percent(0)", 7 : "Timer(12, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[4][4])).pulse_width_percent(50)"}
            }
                   # CCW / Left           # Clockwise / Right    # Stop                 # Start
ledMove = { 0 : {4 : pyb.LED(1).on, 5 : pyb.LED(1).on, 6 : pyb.LED(1).off, 7 : pyb.LED(1).on},
                   # UP                   # Down                 # Stop                 # Start
            1 : {4 : pyb.LED(2).on, 5 : pyb.LED(2).on, 6 : pyb.LED(2).off, 7 : pyb.LED(2).on},
                   # CCW / Left           # Clockwise / Right    # Stop                 # Start
            2 : {4 : pyb.LED(3).on, 5 : pyb.LED(3).on, 6 : pyb.LED(3).off, 7 : pyb.LED(3).on},
                   # Close / Open         # Close / Open         # Stop                 # Start
            3 : {4 : pyb.LED(4).on, 5 : pyb.LED(4).on, 6 : pyb.LED(4).off, 7 : pyb.LED(4).on},
                   # CCW / Left           # Clockwise / Right    # Stop                 # Start
            4 : {4 : pyb.LED(4).on, 5 : pyb.LED(4).on, 6 : pyb.LED(4).off, 7 : pyb.LED(4).on}
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
                    eval(movements[int(move[0])][int(move[1])])
                    pyb.LED(3).toggle();
                    print(move)
        except:
            pass

if __name__ == "__main__":
    Timer(2, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[0][4])).pulse_width_percent(0)
    Timer(2, freq=1250).channel(2, Timer.PWM, pin=Pin(armAction[1][4])).pulse_width_percent(0)
    Timer(2, freq=1250).channel(3, Timer.PWM, pin=Pin(armAction[2][4])).pulse_width_percent(0)
    Timer(2, freq=1250).channel(4, Timer.PWM, pin=Pin(armAction[3][4])).pulse_width_percent(0)
    Timer(12, freq=1250).channel(1, Timer.PWM, pin=Pin(armAction[4][4])).pulse_width_percent(0)

    for i in range(5): #movements, armAction, and ledMove are arrays, an array of 4, will be 5 since a 5th motor to be added
    #armAction setting up the pins on the board to specify what is the en, dir, and pulse_width_percent
    #movments detailing what way to move or Stop
    #ledMove lights on the board light up to signal what and how things are moving
		Pin(armAction[i][6], Pin.OUT_PP).low()
		Pin(armAction[i][5], Pin.OUT_PP).high()

    pyb.LED(2).toggle()
    time.sleep(1)
    pyb.LED(2).toggle()
    getcommand()

