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
  Schedule.begin(6);

 /* Add the tasks to the schedule */
  Schedule.addTask("SONAR_QUEDA", taskSonarQueda, 0, 5000);
  Serial.print(Schedule.lastAddedTask());
  Schedule.addTask("SONAR_OBSTACULO", taskSonarObstaculo, 1000, 8000);
  Serial.print(Schedule.lastAddedTask());
  Schedule.addTask("BUMPER", taskBumpers, 1000, 8000);
  Serial.print(Schedule.lastAddedTask());
  Schedule.addTask("LINEFOLLOWING", taskLineFollowing, 1000, 8000);
  Serial.print(Schedule.lastAddedTask());
  Schedule.addTask("PD", taskPD, 1000, 8000);
  Serial.print(Schedule.lastAddedTask());
  Schedule.addTask("Gerenciador Aperiodicos", taskDrift, 1000, 8000);
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
  Schedule.runTasks();
}

/********** Task Functions **********/
void taskDrift(){
  if(FLAG > 0){
    turnAround();
  }
}

void turnAround(){

}

/* This task sends the status of the LED pin to the serial port */
void statusOut() {
  Serial.println("");
}
