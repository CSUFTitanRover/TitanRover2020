//====================================================================================//
/*
File:         GripperControl.ino
Authors:      Robert Pace IV 
Emails:       rpaceiv@gmail 
Description:  This is used to test the J51(grip rotation) and J52(grip closing/opening) 
              of the arm. 
              
*/
//====================================================================================//

int a_speed=135;//135 micro secs is the fastest tested val for nema 23 (smaller number is faster, while bigger number is slower)
  
//Buttons
int j51_but_right = 9;     
int j51_but_left = 10;
int j52_but_up = 11;     
int j52_but_down = 12; 

int i_speed = A0;//POT used for variable speed control

//grip rotation
int j51_EN;//If HIGH the motor can be controlled 
int j51_DIR;//Sets what direction you are going
int j51_PUL;//This sets up your pulse that will be used to switch between phases

//grip closing/opening
int j52_EN;
int j52_DIR;
int j52_PUL;

void setup() {
  pinMode(j51_but_right, INPUT);
  pinMode(j51_but_left, INPUT); 
  pinMode(j52_but_up, INPUT); 
  pinMode(j52_but_down, INPUT);
  
  pinMode(j51_EN, OUTPUT);
  pinMode(j51_DIR, OUTPUT);
  pinMode(j51_PUL, OUTPUT);
 
  pinMode(j52_EN, OUTPUT);
  pinMode(j52_DIR, OUTPUT);
  pinMode(j52_PUL, OUTPUT); 
  
  //initialize everything to start in the off state
  digitalWrite(j51_EN, LOW);
  digitalWrite(j51_DIR, LOW);
  digitalWrite(j51_PUL, LOW);
  digitalWrite(j52_EN, LOW);
  digitalWrite(j52_DIR, LOW);
  digitalWrite(j52_PUL, LOW);
  
  Serial.begin(9600);
}

//==================/Move function/=====================//
/*
  This function moves the stepper by first enabling 
  the motor and then pulsates between the phases, while 
  also giving the motor time between each phase switch 
  so it does not lock up. Then once it is done shifting
  phases it disables the motor so it does not burn up.
*/
void move(int pul_port, int dir_port, int en_port, int but_val, int speed_val, int dir_val){
  digitalWrite(en_port, HIGH);
  digitalWrite(dir_port, dir_val);
  digitalWrite(pul_port, HIGH);
  delayMicroseconds(speed_val);
  digitalWrite(pul_port, LOW); 
  delayMicroseconds(speed_val);
  digitalWrite(en_port, LOW);
}

void loop() {
  //warning: print statments will slow down the motor considerably
  a_speed = analogRead(i_speed); //use this if block if you want varible speed control 
  if(a_speed>=1000){
    a_speed = 135; 
  }else if(a_speed>=800){
    a_speed = 200;
  }else if(a_speed>=600){
    a_speed = 300;
  }else if(a_speed>=400){
    a_speed = 400;
  }else{
    a_speed = 580;
  }

  if(digitalRead(j51_but_right)==1){
//    Serial.println("right"); 
//    Serial.println(a_speed);
    move(j51_PUL,j51_DIR,j51_EN,j51_but_right,a_speed,HIGH);
  }else if(digitalRead(j51_but_left)==1){
//    Serial.println("left"); 
//    Serial.println(a_speed);
    move(j51_PUL,j51_DIR,j51_EN,j51_but_left,a_speed,LOW);
  }
  
  if(digitalRead(j52_but_up)==1){
//    Serial.println("up"); 
//    Serial.println(a_speed);
    move(j52_PUL,j52_DIR,j52_EN,j52_but_up,a_speed,HIGH);
  }else if(digitalRead(j52_but_down)==1){
//    Serial.println("down"); 
//    Serial.println(a_speed);
    move(j52_PUL,j52_DIR,j52_EN,j52_but_down,a_speed,LOW);
  }
}


//Old Style before converted to function
// a_speed = analogRead(i_speed);    
//  
//  if(digitalRead(j51_but_right)==1){
//    digitalWrite(j51_DIR, HIGH);
//    while(digitalRead(j51_but_right)==1){
//     digitalWrite(j51_PUL, HIGH);
//     delayMicroseconds(a_speed);
//     digitalWrite(j51_PUL, LOW); 
//     delayMicroseconds(a_speed);
//    }
//  }
//  if(digitalRead(j51_but_left)==1){
//    digitalWrite(j51_DIR, LOW);
//    while(digitalRead(j51_but_left)==1){
//     digitalWrite(j51_PUL, HIGH);
//     delayMicroseconds(a_speed);
//     digitalWrite(j51_PUL, LOW); 
//     delayMicroseconds(a_speed);
//    }
//  }
//  if(digitalRead(j52_but_up)==1){
//    digitalWrite(j52_DIR, HIGH);
//    while(digitalRead(j52_but_up)==1){
//     digitalWrite(j52_PUL, HIGH);
//     delayMicroseconds(a_speed);
//     digitalWrite(j52_PUL, LOW); 
//     delayMicroseconds(a_speed);
//    }
//  }
//  if(digitalRead(j52_but_down)==1){
//    digitalWrite(j52_DIR, LOW);
//    while(digitalRead(j52_but_down)==1){
//     digitalWrite(j52_PUL, HIGH);
//     delayMicroseconds(a_speed);
//     digitalWrite(j52_PUL, LOW); 
//     delayMicroseconds(a_speed);
//    }
//  }
