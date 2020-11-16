
// Set Solenoid Pin and ToggleButton Pin
const int solPin = 4;
const int togglePin = 8;

int mode = LOW;

void setup() {
  //Serial.begin(9600);
  pinMode(solPin, OUTPUT);
  pinMode(togglePin, INPUT);
}

void toggle() {
  //Serial.print("Toggle");
  if(mode == LOW){
    mode = HIGH;
  }
  else {
    mode = LOW;
  }
  digitalWrite(solPin, mode);
  delay(500);
}

void loop() {
  int buttonState = digitalRead(togglePin);
  if(buttonState == HIGH){
    toggle();
  }
}
