void taskBumpers(){
  //BUMPER READ
  bumperDireito = digitalRead(digPinBumper1);
  bumperEsquerdo = digitalRead(digPinBumper2);

  if(bumperDireito == 0 || bumperEsquerdo == 0){
    FLAG = 1;
  } 

}
