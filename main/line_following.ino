//3333////////////////////////TAREFA TRES///////////// 3 3 3 3 //////////////////////////////////
void navegacao() {

  motorLeft->setSpeed(potenciaMotor);
  motorRight->setSpeed(potenciaMotor);

  while (1) {

    OptRefLeft = digitalRead(portaOptRefLeft);
    OptRefRight = digitalRead(portaOptRefRight);
    delay(100);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(OptRefLeft);
    lcd.setCursor(3, 0);
    lcd.print(OptRefRight);
    waddle_left();
    waituntil_on_the_line();
    waituntil_off_the_line();
    waddle_right();
    waituntil_on_the_line();
    waituntil_off_the_line();
  }
}

void waddle_left() {

  motorRight->run(FORWARD);
  motorLeft->run(RELEASE);
}

void waddle_right() {

  motorLeft->run(FORWARD);
  motorRight->run(RELEASE);
}
int grifo = 0;

//Ajustar valores quando o sensor for adicionado
void waituntil_on_the_line() {
  grifo = analogRead(portaLDRCores);
  while (OptRefLeft == 0)// && millis() - tempo_torneio < 60000 && grifo < 800) {
  {
    if (millis() - tempo_torneio > 60000) break;
    if (grifo > 800) break;
    grifo = analogRead(portaLDRCores);
    OptRefLeft = digitalRead(portaOptRefLeft);//Se for adicionar hysteresis eh soh setar um teto e um floor e colocar nessas funcs
  }
}

void waituntil_off_the_line() {
  while (OptRefLeft == 0)// && millis() - tempo_torneio < 60000 && grifo < 800){
  {

    if (millis() - tempo_torneio > 60000) break;
    if (grifo > 800) break;
    grifo = analogRead(portaLDRCores);
    OptRefLeft = digitalRead(portaOptRefLeft);
  }
  OptRefRight = digitalRead(portaOptRefRight);
}

