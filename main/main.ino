/**************************************************
   Simple example using the Scheduino library.
   Replicates the behaviour of the standard Arduino 'Blink' example, while outputting the LED status (ON or OFF) to the Serial port
*/
#include <Tasks.h>
#include <AFMotor.h>

// Define o motor1 ligado a conexao 1
AF_DCMotor motor1(2); 
// Define o motor2 ligado a conexao 4
AF_DCMotor motor2(4); 

//Sonares
long duration, cm, inches;
//Sonar para detectar obstaculo
int trigPin1 = 50;    //Trig - Laranja
int echoPin1 = 53;    //Echo - Azul

//Sonar para detectar queda
int trigPin2 = 26;    //Trig - green Jumper
int echoPin2 = 27;    //Echo - yellow Jumper

//Bumpers
int digPinBumper1 = 22; //Direito 
int digPinBumper2 = 23; //Esquerdo

//BreakBean
int portaBBLeft = 43; //Roxo azul e verde
int portaBBRight = 35; //Vermelho laranja e marrom

//OpticoReflex
int portaOptRefRight = 36; // Verde amarelo laranja
int portaOptRefLeft = 44; // Preto cinza e branco

int FLAG = 0;

int bumperDireito;
int bumperEsquerdo;

/* Tasks are added to the schedule here in the form addTask(task_function_name, task_period, task_offset) */
void setup() {

  // Define a velocidade maxima para os motores 1 e 2
  motor1.setSpeed(250); 
  motor2.setSpeed(250); 

  //Define bumper
  pinMode(digPinBumper1, INPUT);
  digitalWrite(digPinBumper1, HIGH);
  pinMode(digPinBumper2, INPUT);
  digitalWrite(digPinBumper2, HIGH);

  //Sonares
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  //BreakBean
  pinMode(portaBBLeft, INPUT);
  pinMode(portaBBRight, INPUT);
  
  //Optico Reflexivo - Line Following
  pinMode(portaOptRefLeft, INPUT);
  pinMode(portaOptRefRight, INPUT);
  
  String addedTasks;
  /* Configure the serial port to 9600 baud - used for reportAddedTask and the statusOut task */
  Serial.begin(9600);
  Serial.print("Tasks for Arduino - Scheduler example\n\n");

  /* Create a schedule with 3 tasks */
  Schedule.begin(3);

  /* Add the LED tasks to the schedule */
  Schedule.addTask("SONAR 1", taskSonar1, 0, 5000);
  Serial.print(Schedule.lastAddedTask());
  Schedule.addTask("SONAR2", taskSonar2, 1000, 8000);
  Serial.print(Schedule.lastAddedTask());

  /* The status is output every 100 'ticks', offset by 1 'tick' */
  Schedule.addTask("PRINT...", statusOut, 10, 3000);
  Serial.print(Schedule.lastAddedTask());

  /* Starting the scheduler with a tick length of 1 millisecond */
  Schedule.startTicks(1);

  /* Some error checks */
  if (Schedule.checkTooManyTasks() == true) {
    Serial.println("Too many tasks");
  }

  if (Schedule.checkTicksTooLong() == true) {
    Serial.println("Ticks too long");
  }

  
  
}

/* It's best not to do anything in loop() except runTasks() - doing anything else here will affect timing */
void loop() {
  
}

/********** Task Functions **********/

void taskSonarObstaculo() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration = pulseIn(echoPin1, HIGH);

  // convert the time into a distance
  cm = (duration / 2) / 29.1;

  if(cm < 5){
    FLAG = 1;
  }
}

void taskSonarQueda() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin2, INPUT);
  duration = pulseIn(echoPin2, HIGH);

  // convert the time into a distance
  cm = (duration / 2) / 29.1;

  if(cm > 4){
    FLAG = 1;
  } 
}

void taskBumpers(){
  //BUMPER READ
  bumperDireito = digitalRead(digPinBumper1);
  bumperEsquerdo = digitalRead(digPinBumper2);

  if(bumperDireito == 0 || bumperEsquerdo == 0){
    FLAG = 1;
  } 

}

void taskLineFollowing(){

}

void taskPD(){
  
}

void taskDrift(){

}

/* This task sends the status of the LED pin to the serial port */
void statusOut() {
  Serial.println("");
}