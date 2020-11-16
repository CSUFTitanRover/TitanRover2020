# main.py -- put your code here!
from pyb import Timer, UART, ADC, Pin, ExtInt
import pyb
import time

# Virtual UART Port
ser = pyb.USB_VCP(0)

# Tracks the toggle state of the current device
dc_state1 = [0]
dc_state2 = [0]
dc_state3 = [0]
dc_state4 = [0]
sol_state = [0]

Pins = {
    # Manafold
    0: {
        0: {
            0: "(Timer(2, freq=850)).channel(3, Timer.PWM, pin=Pin('X3'))",  # PWM Pin
            1: Pin('X9', Pin.OUT_PP),  # Dir Pin
            2: Pin('X10', Pin.OUT_PP)  # ENA Pin
        }
    },
    # Spectroscopy
    1: {
        0: {
            0: "(Timer(2, freq=850)).channel(4, Timer.PWM, pin=Pin('X4'))",
            1: Pin('X11', Pin.OUT_PP),
            2: Pin('Y12', Pin.OUT_PP)
        }
    },
    # Pumps
    2: {
        0: {
            0: Pin('Y1', Pin.OUT_PP),  # in1
            1: Pin('Y2', Pin.OUT_PP)  # in2
        },
        1: {
            0: Pin('Y3', Pin.OUT_PP),  # in1
            1: Pin('Y4', Pin.OUT_PP)  # in2
        },
        2: {
            0: Pin('Y5', Pin.OUT_PP),  # in1
            1: Pin('Y6', Pin.OUT_PP)  # in2
        },
        3: {
            0: Pin('Y7', Pin.OUT_PP),  # in1
            1: Pin('Y8', Pin.OUT_PP)  # in2
        }
    },
    # Solenoid
    3: {
        0: {
            0: Pin('Y9', Pin.OUT_PP)  # sig pin
        }
    }
}


# Pulse a stepper motor
def stepperMove(stepper, dir_port, en_port, dir_val):
    dir_port.value(dir_val)
    stepper.pulse_width_percent(50)
    pyb.LED(4).on()
    time.sleep(.1)
    stepper.pulse_width_percent(0)
    pyb.LED(4).off()


def togglePump(in1, in2, state):
    time.sleep(.4)
    if state[0] == 0:
        in1.high()
        in2.low()
        state[0] = 1
    else:
        in1.low()
        in2.low()
        state[0] = 0


def toggleSolenoid(sig, state):
    time.sleep(.4)
    if state[0] == 0:
        sig.high()
        state[0] = 1
    else:
        sig.low()
        state[0] = 0


fluidAction = {
    0: {
        0: {                # PWM Port          #DIR Port       #ENA Port     #DIR
            0: 'stepperMove(eval(Pins[0][0][0]), Pins[0][0][1], Pins[0][0][2], 1)',  # Manaf CW
            1: 'stepperMove(eval(Pins[0][0][0]), Pins[0][0][1], Pins[0][0][2], 0)'  # Manaf CCW
        }
    },

    1: {
        0: {
            0: 'stepperMove(eval(Pins[1][0][0]), Pins[1][0][1], Pins[1][0][2], 1)',  # Spect CW
            1: 'stepperMove(eval(Pins[1][0][0]), Pins[1][0][1], Pins[1][0][2], 0)'  # Spect CCW
        }
    },

    2: {                    # in1        #in2       #State
        0: {
            0: 'togglePump(Pins[2][0][0],Pins[2][0][1],dc_state1)',  # Toggle pump1
            1: 'togglePump(Pins[2][1][0],Pins[2][1][1],dc_state2)',  # Toggle pump2
            2: 'togglePump(Pins[2][2][0],Pins[2][2][1],dc_state3)',  # Toggle pump3
            3: 'togglePump(Pins[2][3][0],Pins[2][3][1],dc_state4)',  # Toggle pump4
        }
    },

    3: {
        0: {  # Sig pin   #State
            0: 'toggleSolenoid(Pins[3][0][0],sol_state)'  # Toggle Solenoid
        }
    }

}


# def getCommand():
#     while True:
#         try:
#             data = ser.read(1)
#             time.sleep(.1)
#             if str(data.decode('utf-8')) == 's':
#                 move = ser.read(4)
#                 move = move.decode('utf-8')
#                 if str(move[3]) == 'e':
#                     time.sleep(1)
#                     eval(fluidAction[int(move[0])][int(move[1])][int(move[2])])
#         except:
#             pass


if __name__ == "__main__":
    # Testing buttons
    but_mana_cw = Pin('X5', Pin.IN, Pin.PULL_NONE)
    but_mana_ccw = Pin('X6', Pin.IN, Pin.PULL_NONE)
    but_spec_cw = Pin('X7', Pin.IN, Pin.PULL_NONE)
    but_spec_ccw = Pin('X8', Pin.IN, Pin.PULL_NONE)
    but_pump_1 = Pin('X19', Pin.IN, Pin.PULL_NONE)
    but_pump_2 = Pin('X20', Pin.IN, Pin.PULL_NONE)
    but_pump_3 = Pin('X21', Pin.IN, Pin.PULL_NONE)
    but_pump_4 = Pin('X22', Pin.IN, Pin.PULL_NONE)
    but_sol = Pin('Y11', Pin.IN, Pin.PULL_NONE)

    # Setup all the ports and devices to default states
    eval(Pins[0][0][0])
    eval(Pins[1][0][0])
    Pins[0][0][2].low()
    Pins[1][0][2].low()

    # Loop button checks
    while True:
        if but_mana_cw.value():
            eval(fluidAction[0][0][0])
        elif but_mana_ccw.value():
            eval(fluidAction[0][0][1])
        if but_spec_cw.value():
            eval(fluidAction[1][0][0])
        elif but_spec_ccw.value():
            eval(fluidAction[1][0][1])
        if but_pump_1.value():
            eval(fluidAction[2][0][0])
        if but_pump_2.value():
            eval(fluidAction[2][0][1])
        if but_pump_3.value():
            eval(fluidAction[2][0][2])
        if but_pump_4.value():
            eval(fluidAction[2][0][3])
        if but_sol.value():
            eval(fluidAction[3][0][0])

    # getCommand()
