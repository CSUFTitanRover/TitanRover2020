// to be used for the Nema 11 stepper motor that controls J2 and J3
int a_speed=0;

int i_speed = A5;    
int but_right = 13;//CW initially 33     
int but_left = 12;//CCW initially 32
//int j52_but_up = 30;     
//int j52_but_down = 31; 

//DIR CCW
//PUL/STEP CW
int EN=8; //38
int DIR=9; //39
int PUL=10; //40

/*
int j52_EN=41;
int j52_DIR=42;
int j52_PUL=43;
*/

void setup() {
  pinMode(but_right, INPUT);
  pinMode(but_left, INPUT); 
  
  pinMode(EN, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);
 
  digitalWrite(EN, LOW);
  digitalWrite(DIR, LOW);
  digitalWrite(PUL, LOW);
  
  Serial.begin(9600);
}


void move(int pul_port, int dir_port, int en_port, int but_val, int speed_val, int dir_val){
  digitalWrite(en_port, HIGH);
  digitalWrite(dir_port, dir_val);
  digitalWrite(pul_port, HIGH);
  delayMicroseconds(20);
  digitalWrite(pul_port, LOW); 
  delayMicroseconds(40);
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
    a_speed = 45;
  }

  if(digitalRead(but_right)==1){
    //Serial.println("right");
    //Serial.println(a_speed);
    move(PUL,DIR,EN,but_right,a_speed,HIGH);
  }
  if(digitalRead(but_left)==1){
    //Serial.println("left");
    //Serial.println(a_speed);
    move(PUL,DIR,EN,but_left,a_speed,LOW);
  }
}
