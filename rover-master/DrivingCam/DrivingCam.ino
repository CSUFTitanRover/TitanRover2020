#include <Wire.h>
#include <Stepper.h>
#define SLAVE_ADDRESS 0x05

// change this to the number of steps on your motor
#define STEPS 2038
#define sp 10

int16_t pan = 0;
int16_t tilt = 0;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper1(STEPS, 2, 3, 4, 5);
Stepper stepper2(STEPS, 7, 8, 9, 10);

String panTemp;
String tiltTemp;

void setup()
{

  // set the speed of the motor to 30 RPMs
  stepper1.setSpeed(sp);
  stepper2.setSpeed(sp);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
}
void loop()
{
}

void receiveData(int byteCount) 
{
    if (Wire.available() == 2)
    {
      pan = Wire.read();
      tilt = Wire.read();
    if(pan == 2)
    {
      pan = -1;
    }
    if(tilt == 2)
    {
      tilt = -1;
    }
      stepper1.step(pan);
      stepper2.step(tilt);
    }
}
