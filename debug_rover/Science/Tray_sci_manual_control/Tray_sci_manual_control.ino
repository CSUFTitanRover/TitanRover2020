//========================================================================//
/*
File:         Tray_sci_manual_control.ino
Authors:      Robert Pace IV 
Emails:       rpaceiv@gmail 
Description:  This is used to test the science trays with manual control
              with no feedback.
*/
//========================================================================//

int a_speed=580;//135 micro secs is the fastest tested val for nema 23 (smaller number is faster, while bigger number is slower)

//Buttons
int top_but_right = 6;//CW     
int top_but_left = 5;//CCW 
int bot_but_right = A0;//CW     
int bot_but_left = A1;//CCW

int i_speed = A1;//POT used for variable speed control

//Top Tray
int top_EN=7;//If HIGH the motor can be controlled 
int top_DIR=4;//Sets what direction you are going
int top_PUL=10;//This sets up your pulse that will be used to switch between phases

//Bottom Tray
int bot_EN=8;
int bot_DIR=13;
int bot_PUL=12;

void setup() {
  pinMode(bot_but_right, INPUT);
  pinMode(bot_but_left, INPUT); 
  pinMode(top_but_right, INPUT); 
  pinMode(top_but_left, INPUT);
  
  pinMode(bot_EN, OUTPUT);
  pinMode(bot_DIR, OUTPUT);
  pinMode(bot_PUL, OUTPUT);
 
  pinMode(top_EN, OUTPUT);
  pinMode(top_DIR, OUTPUT);
  pinMode(top_PUL, OUTPUT); 
  
  //initialize everything to start in the off state
  digitalWrite(bot_EN, LOW);
  digitalWrite(bot_DIR, LOW);
  digitalWrite(bot_PUL, LOW);
  digitalWrite(top_EN, LOW);
  digitalWrite(top_DIR, LOW);
  digitalWrite(top_PUL, LOW);
  
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
/*a_speed = analogRead(i_speed); //use this if block if you want varible speed control 
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
*/

  if(digitalRead(top_but_right)==1){
//    Serial.println("right"); 
//    Serial.println(a_speed);
    move(top_PUL,top_DIR,top_EN,top_but_right,a_speed,LOW);
  }else if(digitalRead(top_but_left)==1){
//    Serial.println("left");
//    Serial.println(a_speed);
    move(top_PUL,top_DIR,top_EN,top_but_left,a_speed,HIGH);
  }

  if(digitalRead(bot_but_right)==1){
//    Serial.println("right");
//    Serial.println(a_speed);
    move(bot_PUL,bot_DIR,bot_EN,bot_but_right,a_speed,HIGH);
  }else if(digitalRead(bot_but_left)==1){
//    Serial.println("left");
//    Serial.println(a_speed);
    move(bot_PUL,bot_DIR,bot_EN,bot_but_left,a_speed,LOW);
  }
}
