/**************************************************
	

*/
#include <Tasks.h>		//Biblioteca de escalonamento por tempo.
#include <AFMotor.h>	//Biblioteca de controle dos motores.
#include "sonar.ino"

//Definição dos motores.
AF_DCMotor motor1(1); 	// Define o motor1 ligado a conexao 1.
AF_DCMotor motor2(2); 	// Define o motor2 ligado a conexao 2.

//Configuração de pino para os SONARES
//Sonar 1 - Cores: Verm, Laranja, Azul, Preto
int trigPin1 = 30;    //Trig - Laranja
int echoPin1 = 34;    //Echo - Azul
//Sonar 2 - Preto, Laranja, Roxo, Vermelho
int trigPin2 = 40;    //Trig - Laranja
int echoPin2 = 44;    //Echo - Roxo

//

long duration, cm, inches;

/* Tasks are added to the schedule here in the form addTask(task_function_name, task_period, task_offset) */
void setup() {
  String addedTasks;
  /* Configure the serial port to 9600 baud - used for reportAddedTask and the statusOut task */
  Serial.begin(9600);
  Serial.print("Tarefas definidas:\n\n");

  /* Create a schedule with 3 tasks */
  Schedule.begin(3);

  //Sonar 1
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  //Sonar 2
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  
  // Inclusão de tarefas no escalonador.
  /* Tarefa 1 - Sonar 1 */
  Schedule.addTask("SONAR 1", taskSonar1, 0, 5000);
  Serial.print(Schedule.lastAddedTask());
  
  /* Tarefa 2 - Sonar 2 */
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
  Schedule.runTasks();
  //taskSonar1();
}

/********** Task Functions **********/



/* This task sends the status of the LED pin to the serial port */
void statusOut() {
  Serial.println("");
}