void testaSonares(){
  //taskSonarObstaculo();
  taskSonarQueda();
}

void testaOptReflex(){
  //Serial.println(digitalRead(portaOptRefLeft));
  //Serial.println(digitalRead(portaOptRefRight));
  Serial.println(digitalRead(portaOptRefMiddle));
}

void testaBumpers(){
  Serial.print(digitalRead(digPinBumper1));
  Serial.print("  ");
  Serial.println(digitalRead(digPinBumper2));
}

void testaBB(){
  Serial.print(digitalRead(portaBBLeft));
  Serial.print("  ");
  Serial.println(digitalRead(portaBBRight));
}

void testaMotores(){
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);

  delay(1000);

  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  stop();
}
