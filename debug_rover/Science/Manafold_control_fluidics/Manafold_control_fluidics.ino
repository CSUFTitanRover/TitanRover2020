//========================================================================//
/*
File:         Manafold_control_fluidics.ino
Authors:      Robert Pace IV 
Emails:       rpaceiv@gmail 
Description:  This is used to test the fluidics manafold that has 
              a purpose of dispensing different types of liquid solutions.
*/
//========================================================================//

int a_speed=135;//135 micro secs is the fastest tested val for nema 23 (smaller number is faster, while bigger number is slower)
    
int Manaf_but_right = 8;//Move Right     
int Manaf_but_left = 7;//Move Left


int i_speed = A1;//POT used for variable speed control

int Manaf_EN=4;//If HIGH the motor can be controlled 
int Manaf_DIR=10;//Sets what direction you are going
int Manaf_PUL=13;//This sets up your pulse that will be used to switch between phases


void setup() {
  pinMode(Manaf_but_right, INPUT);
  pinMode(Manaf_but_left, INPUT); 

  pinMode(Manaf_EN, OUTPUT);
  pinMode(Manaf_DIR, OUTPUT);
  pinMode(Manaf_PUL, OUTPUT);
  
  //initialize everything to start in the off state
  digitalWrite(Manaf_EN, LOW);
  digitalWrite(Manaf_DIR, LOW);
  digitalWrite(Manaf_PUL, LOW);

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
/*a_speed = analogRead(i_speed); //use this block if you want varible speed control 
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

  if(digitalRead(Manaf_but_right)==1){
//    Serial.println("right");
//    Serial.println(a_speed);
    move(Manaf_PUL,Manaf_DIR,Manaf_EN,Manaf_but_right,a_speed,HIGH);
  }else if(digitalRead(Manaf_but_left)==1){
//    Serial.println("left");
//    Serial.println(a_speed);
    move(Manaf_PUL,Manaf_DIR,Manaf_EN,Manaf_but_left,a_speed,LOW);
  }
}
