int OptRefLeft;
int OptRefRight;
int OptRefMiddle;

void taskLineFollowing() {
  Serial.println("Task Line Following");
  
  motorLeft.setSpeed(potenciaMotor);
  motorRight.setSpeed(potenciaMotor);

  OptRefLeft = digitalRead(portaOptRefLeft);
  OptRefRight = digitalRead(portaOptRefRight);

  if(OptRefLeft == 1 && OptRefRight == 1 && OptRefMiddle == 1){
    FLAG = 4;
  }else if(OptRefLeft == 0 && OptRefRight == 1 && OptRefMiddle == 1){
    waddle_left();
  }else if(OptRefLeft == 1 && OptRefRight == 0 && OptRefMiddle == 1){
    waddle_right();
  }

}

void waddle_left() {

  motorRight.run(FORWARD);
  motorLeft.run(RELEASE);
}

void waddle_right() {

  motorLeft.run(FORWARD);
  motorRight.run(RELEASE);
}

void findLine(){
  
}
