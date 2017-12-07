unsigned long tempoAntigo;
int gaFlag = 0;

void taskGerenciadorAperiodicos() {
  Serial.println("GERENCIADOR DE APERIÓDICOS");
  if (FLAG > 0) {
    Serial.println("Parando os motores");
    stopMotors();
    delay(10);
    Serial.println("Dando ré");
    goBackwards();
    while(gaFlag != 0); 
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
  delay(10000);
  Serial.print("Teste ");
  gaFlag = 0;
}

void turnAround() {
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
  delay(4200);
}
