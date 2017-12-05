/**************************************************
   Simple example using the Scheduino library.
   Replicates the behaviour of the standard Arduino 'Blink' example, while outputting the LED status (ON or OFF) to the Serial port
*/
#include <Tasks.h>
#include <AFMotor.h>

// Define o motor1 ligado a conexao 1
AF_DCMotor motorLeft(2);
// Define o motor2 ligado a conexao 4
AF_DCMotor motorRight(4); 

// Sonares
long duration, cm, inches;
// Sonar - Obstaculo
int trigPin1 = 50;
int echoPin1 = 53;
// Sonar - Queda
int trigPin2 = 26;
int echoPin2 = 27;

// Bumper
int digPinBumper1 = 23;
int digPinBumper2 = 22;

// Break Beam
int portaBBLeft = 43;
int portaBBRight = 35;

// Optico Reflexivo
int portaOptRefRight = 33;
int portaOptRefLeft = 44;
int portaOptRefMiddle = 40;

int FLAG = 0;

int bumperDireito;
int bumperEsquerdo;

int potenciaMotor = 100;

/* Tasks are added to the schedule here in the form addTask(task_function_name, task_period, task_offset) */
void setup() {

  // Define a velocidade maxima para os motores 1 e 2
  motorLeft.setSpeed(potenciaMotor);
  motorRight.setSpeed(potenciaMotor);

  // Define bumper
  pinMode(digPinBumper1, INPUT);
  digitalWrite(digPinBumper1, HIGH);
  pinMode(digPinBumper2, INPUT);
  digitalWrite(digPinBumper2, HIGH);

  // Sonares
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Break Beam
  pinMode(portaBBLeft, INPUT);
  pinMode(portaBBRight, INPUT);
  
  // Optico Reflexivo - Line Following
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
  //Schedule.addTask("LINEFOLLOWING", taskLineFollowing, 1000, 8000);
  Serial.print(Schedule.lastAddedTask());
//  Schedule.addTask("PD", taskPD, 1000, 8000);
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
  //Schedule.runTasks();
  //stop();
  testaSonares();
}

/********** Task Functions **********/
void taskDrift(){
  if(FLAG > 0){
    stopMotors();
    turnAround();
  }
}

void stop(){
  while(1);
}

void stopMotors() {
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void turnAround() {
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);

  delay(4200);

  stopMotors();
}

/* This task sends the status of the LED pin to the serial port */
void statusOut() {
  Serial.println("");
}
