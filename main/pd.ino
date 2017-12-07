float kp = 10;
float kd = 3;
float ki = 5;
float contaFurosLeft;
float erroLeft;
float anterior_L;
float contaFurosRight;
float erroRight;
float anterior_R;
float outputLeft;
float outputRight;
float deLeft;
float deRight;
float dt = 1000;
long int newTime;
long int lastTime;
int contador_rodaR = 0;
int contador_rodaL = 0;
int count_min;
int count_max;
int leitura_bbR_antiga;
int leitura_bbL_antiga;
int erroLeftlast;
int erroRightlast;
float setspeedR;
float setspeedL;
int fps = 5;
unsigned long pdBegin;

void taskPD() {
  Serial.println("PD");
  if(FLAG > 0) return;
  
  //int directionLeftMotor, int directionRightMotor, int executionTime
  motorRight.setSpeed(potenciaMotor);
  //motorRight.run(directionRightMotor);
  motorRight.run(FORWARD);
  motorLeft.setSpeed(potenciaMotor);
  //motorLeft.run(directionLeftMotor);
  motorLeft.run(FORWARD);

  erroRightlast = 0;
  erroLeftlast = 0;
  setspeedR = potenciaMotor;
  setspeedL = potenciaMotor;
  contador_rodaR = 0;
  contador_rodaL = 0;
  lastTime = millis();
  odometria(FORWARD, FORWARD, 1000);
}

void odometria(int directionLeftMotor, int directionRightMotor, int executionTime) {
  pdBegin = millis();
  Serial.println("Executando PD");
  while (millis() - pdBegin < executionTime) {
    contador_rodaR = 0;
    contador_rodaL = 0;
    leitura_bbR_antiga = digitalRead(portaBBLeft);
    leitura_bbL_antiga = digitalRead(portaBBRight);
    lastTime = millis();
    while ((millis() - lastTime) < dt) {
      if (leitura_bbR_antiga != digitalRead(portaBBRight)) {
        leitura_bbR_antiga = digitalRead(portaBBRight);
        contador_rodaR ++;
      }
      if (leitura_bbL_antiga != digitalRead(portaBBLeft)) {
        leitura_bbL_antiga = digitalRead(portaBBLeft);
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

    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);

    setspeedR += outputRight ;
    setspeedL += outputLeft;

    motorRight.setSpeed(setspeedR);
    motorLeft.setSpeed(setspeedL);
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
  }
}
