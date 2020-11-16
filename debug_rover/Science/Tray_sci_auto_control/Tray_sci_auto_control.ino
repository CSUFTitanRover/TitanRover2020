***********to be finished***********
//========================================================================//
/*
File:         Tray_sci_auto_control.ino
Authors:      Robert Pace IV 
Emails:       rpaceiv@gmail 
Description:  This is used to test the science trays with manual control
              with no feedback.
*/
//========================================================================//

int a_speed=580;//135 micro secs is the fastest tested val for nema 23 (smaller number is faster, while bigger number is slower)

//Keeps track of the trays rotation 
int bot_tick_counter=0;
int top_tick_counter=0;

//Buttons
int top_but_right = 6;//CW 
int top_but_left = 5;//CCW
int bot_but_right = A0;//CW     
int bot_but_left = A1;//CCW

int i_speed = A1;//POT used for variable speed control

// Encoder Z(index)
int bot_enc_Z = 3;
int top_enc_Z = 2;

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

//  pinMode(bot_enc_Z, INPUT); 
//  pinMode(top_enc_Z, INPUT);
  
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

  attachInterrupt(digitalPinToInterrupt(bot_enc_Z), bot_count, FALLING);
//  attachInterrupt(digitalPinToInterrupt(top_enc_Z), top_count, FALLING);
  
  Serial.begin(9600);
}

void bot_count(){
//  Serial.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  bot_tick_counter+=1;
}

void top_count(){
//  Serial.println("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");
  top_tick_counter+=1;
}

void move(int pul_port, int dir_port, int en_port, int but_val, int speed_val, int dir_val, int tick_sum){
  digitalWrite(en_port, HIGH);
  digitalWrite(dir_port, dir_val);
//  while(tick_sum<1000){
    Serial.println(tick_sum);
    digitalWrite(pul_port, HIGH);
    delayMicroseconds(135);
    digitalWrite(pul_port, LOW); 
    delayMicroseconds(135);
//  }
  tick_sum=0;
  digitalWrite(en_port, LOW);
}

void loop() {
//  a_speed = analogRead(i_speed);    
  if(analogRead(i_speed)>=1000){
    a_speed = 1;
  }else if(analogRead(i_speed)>=800){
    a_speed = 20;
  }else if(analogRead(i_speed)>=600){
    a_speed = 35;
  }else if(analogRead(i_speed)>=400){
    a_speed = 40;
  }else{
    a_speed = 1000;
  }

  if(digitalRead(bot_but_right)==1){
//    Serial.println("right");
//    Serial.println(digitalRead(bot_enc_Z));
    move(bot_PUL,bot_DIR,bot_EN,bot_but_right,a_speed,HIGH,bot_tick_counter);
  }
  if(digitalRead(bot_but_left)==1){
//    Serial.println("left");
//    Serial.println(a_speed);
    move(bot_PUL,bot_DIR,bot_EN,bot_but_left,a_speed,LOW,bot_tick_counter);
  }
  if(digitalRead(top_but_right)==1){
//    Serial.println("up");
//    Serial.println(a_speed);
    move(top_PUL,top_DIR,top_EN,top_but_right,a_speed,LOW,top_tick_counter);
  }
  if(digitalRead(top_but_left)==1){
//    Serial.println("down");
//    Serial.println(a_speed);
    move(top_PUL,top_DIR,top_EN,top_but_left,a_speed,HIGH,top_tick_counter);
  }
}
