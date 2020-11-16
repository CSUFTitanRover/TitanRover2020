//========================================================================//
/*
File: Stop_Cock_Control.ino
Authors:      
Emails:        
Description: This is used to control the stop cock with a servo which is
             a valve that controls direction of liquid.
*/
//========================================================================//

#include <Servo.h>

Servo myservo;  // twelve servo objects can be created on most boards

const int buttonPin1 = 4; 
const int buttonPin2 = 5;

int button1State = 0;
int button2State = 0;
int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to -the servo object
  Serial.begin(9600);
}

void loop() {
  button1State = digitalRead(buttonPin1);
  button2State = digitalRead(buttonPin2);

  if(button1State == HIGH) {
      if(pos != 169) { // If the servo is already in that position, then pressing the same button again won't reset the arm and spin it again.
      for (pos = 64; pos <= 168; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
       myservo.write(pos);              // tell servo to go to position in variable 'pos'
       delay(15);                       // waits 15ms for the servo to reach the position
     }
     Serial.print(pos);
    }
  }
  if(button2State == HIGH) {
    if(pos != 63) { // If the servo is already in that position, then pressing the same button again won't reset the arm and spin it again.
    for (pos = 168; pos >= 64; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    Serial.print(pos);
   }
  }
}
