int gaFlag = 0;
long int lastTimeGA;
float dur = 1000;

void taskGerenciadorAperiodicos() {
  Serial.println("GERENCIADOR DE APERIÓDICOS");
  if (FLAG > 0) {
    Serial.println("Parando os motores");
    stopMotors();
    delay(10);
    Serial.println("Dando ré");
    lastTimeGA = millis();
    goBackwards();
    Serial.println("Girando 180 graus");
    turnAround();
    FLAG = 0;
  }
}

void stopMotors() {
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void goBackwards() {
  Serial.println("Go back ");
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
  while ((millis() - lastTimeGA) < dur){}
  Serial.print("Teste ");
}

void turnAround() {
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
  delay(8000);
  Serial.print("DELAAAY ");
}
