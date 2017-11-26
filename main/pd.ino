int setspeedR;
int setspeedL;

void taskPD() {
  Serial.println("Task PD");
  odometer();
}


void odometer() {
  motorRight->setSpeed(potenciaMotor);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(potenciaMotor);
  motorLeft->run(FORWARD);

  erroRightlast = 0;
  erroLeftlast = 0;
  setspeedR = potenciaMotor;
  setspeedL = potenciaMotor;
  contador_rodaR = 0;
  contador_rodaL = 0;
  lastTime = millis();
  odometria();
}

void odometria() {

    contador_rodaR = 0;
    contador_rodaL = 0;
    leitura_bbR_antiga = digitalRead(27);
    leitura_bbL_antiga = digitalRead(31);
    lastTime = millis();
    while ((millis() - lastTime) < dt) {
      if (leitura_bbR_antiga != digitalRead(27)) {
        leitura_bbR_antiga = digitalRead(27);
        contador_rodaR ++;
      }
      if (leitura_bbL_antiga != digitalRead(31)) {
        leitura_bbL_antiga = digitalRead(31);
        contador_rodaL ++;
      }
    }
    
    erroLeft = fps - contador_rodaL;//((1 / dt) * 1000);
    erroRight = fps - contador_rodaR; //- ((1 / dt) * 1000);
    
    deLeft = (erroLeft - erroLeftlast );// / dt;
    deRight = (erroRight - erroRightlast); /// dt;
    
    erroLeftlast = erroLeft;
    erroRightlast = erroRight;
    
    outputLeft = kp * erroLeft + kd * deLeft;
    outputRight = kp * erroRight + kd * deRight;
    
    motorRight->run(RELEASE);
    motorLeft->run(RELEASE);
    
    setspeedR += outputRight ;
    setspeedL += outputLeft;

    motorRight->setSpeed(setspeedR);
    motorLeft->setSpeed(setspeedL);
    motorRight->run(FORWARD);
    motorLeft->run(FORWARD);
  
}
