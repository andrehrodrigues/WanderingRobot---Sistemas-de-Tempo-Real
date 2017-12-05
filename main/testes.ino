void testaSonares(){
  taskSonarObstaculo();
  //taskSonarQueda();
}

void testaOptReflex(){
  Serial.print(digitalRead(portaOptRefLeft));
  Serial.print("  ");
  Serial.print(digitalRead(portaOptRefMiddle));
  Serial.print("  ");
  Serial.println(digitalRead(portaOptRefRight));
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
