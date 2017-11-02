void testaSonares(){
  //taskSonar1(); 
  //taskSonar2();
}

void testaOptReflex(){
  Serial.print(digitalRead(portaOptRefLeft)); //FUNCIONANDO
  Serial.print("  ");
  Serial.println(digitalRead(portaOptRefRight)); //FUNCIONANDO
}

void testaBumpers(){
  //BUMPER READ
  Serial.print(digitalRead(digPinBumper1));
  Serial.print("  ");
  Serial.println(digitalRead(digPinBumper2));
}

void testaBB(){
  //BB READ
  Serial.println(digitalRead(portaBBLeft)); 
  Serial.print("  ");
  Serial.println(digitalRead(portaBBRight));
}

void testaMotores(){
  // Aciona o motor 1 no sentido horario
  motor1.run(FORWARD); 
  // Aciona o motor 2 no sentido anti-horario
  motor2.run(BACKWARD); 
 
  // Aguarda 5 segundos
  delay(5000);
  Serial.println("PARA MOTORES");

  // Desliga os 2 motores
  motor1.run(RELEASE); 
  motor2.run(RELEASE); 
  delay(5000);
}
