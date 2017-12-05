int OptRefLeft;
int OptRefRight;
int OptRefMiddle;

void taskLineFollowing() {
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);

  OptRefLeft = digitalRead(portaOptRefLeft);
  OptRefRight = digitalRead(portaOptRefRight);
  OptRefMiddle = digitalRead(portaOptRefMiddle);

  if(OptRefLeft == 0 && OptRefRight == 0 && OptRefMiddle == 0){
    FLAG = 4;
  }else if(OptRefLeft == 0 && OptRefRight == 1 && OptRefMiddle == 1){
    waddle_right();
  }else if(OptRefLeft == 1 && OptRefRight == 0 && OptRefMiddle == 1){
    waddle_left();
  }
}

void go_straight() {
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
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
