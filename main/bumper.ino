int bumperEsquerdo;
int bumperDireito;

void taskBumpers() {
  if(FLAG > 0) return;
  Serial.println("BUMPERS");
  Serial.print("Início: ");
  Serial.println(millis());

  bumperEsquerdo = digitalRead(digPinBumperEsquerdo);
  bumperDireito = digitalRead(digPinBumperDireito);

  if(bumperEsquerdo == 0 && bumperDireito == 1) {
    Serial.println("Bumper esquerdo");
    FLAG = 1;
  } else if(bumperEsquerdo == 1 && bumperDireito == 0) {
    Serial.println("Bumper direito");
    FLAG = 1;
  } else if(bumperEsquerdo == 0 && bumperDireito == 0) {
    Serial.println("Bumper esquerdo e direito");
    FLAG = 1;
  }
  Serial.print("Fim: ");
  Serial.println(millis());
}
