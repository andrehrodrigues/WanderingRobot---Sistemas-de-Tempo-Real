int OptRefLeft;
int OptRefMiddle;
int OptRefRight;

void taskLineFollowing() {
  //Serial.println("LINE FOLLOWING");
  //Serial.print("Início: ");
  //Serial.println(millis());
  if (FLAG > 0) return;

  OptRefLeft = digitalRead(portaOptRefLeft);
  OptRefMiddle = digitalRead(portaOptRefMiddle);
  OptRefRight = digitalRead(portaOptRefRight);

  if (OptRefLeft == 0 && OptRefMiddle == 1 && OptRefRight == 1) {
    waddle_left();
  } else if (OptRefLeft == 0 && OptRefMiddle == 0 && OptRefRight == 1) {
    waddle_left();
  } else if (OptRefLeft == 1 && OptRefMiddle == 1 && OptRefRight == 0) {
    waddle_right();
  } else if (OptRefLeft == 1 && OptRefMiddle == 0 && OptRefRight == 0) {
    waddle_right();
  } else {
    go_straight();
  }
  //Serial.print("Fim: ");
  //Serial.println(millis());
}

void go_straight() {
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
}

void waddle_left() {
  motorLeft.run(FORWARD);
  motorRight.run(RELEASE);
}

void waddle_right() {
  motorLeft.run(RELEASE);
  motorRight.run(FORWARD);
}

void turn_left() {
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
}

void turn_right() {
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
}
