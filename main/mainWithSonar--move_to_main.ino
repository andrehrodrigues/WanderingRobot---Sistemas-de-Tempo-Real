/**************************************************
   Scheduino_Blink_example

   Simple example using the Scheduino library.
   Replicates the behaviour of the standard Arduino 'Blink' example, while outputting the LED status (ON or OFF) to the Serial port

*/
#include <Tasks.h>

int trigPin1 = 30;    //Trig - green Jumper
int echoPin1 = 34;    //Echo - yellow Jumper

int trigPin2 = 40;    //Trig - green Jumper
int echoPin2 = 44;    //Echo - yellow Jumper

long duration, cm, inches;

/* Tasks are added to the schedule here in the form addTask(task_function_name, task_period, task_offset) */
void setup() {
  String addedTasks;
  /* Configure the serial port to 9600 baud - used for reportAddedTask and the statusOut task */
  Serial.begin(9600);
  Serial.print("Tasks for Arduino - Scheduler example\n\n");

  /* Create a schedule with 3 tasks */
  Schedule.begin(3);

  /* The LED is turned on every 2000 'ticks' and off every 2000 'ticks', offset by 1000 'ticks'*/
  /* Configure the LED pin as an output */
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  //Sonar 1
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  //Sonar 2
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);


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
  Schedule.runTasks();
  //taskSonar1();
}

/********** Task Functions **********/

void taskSonar1() {
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

  Serial.println("SONAR 1");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(500);
}

void taskSonar2() {
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
  inches = (duration / 2) / 74;

  Serial.println("SONAR 2");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(500);
}

/* This task sends the status of the LED pin to the serial port */
void statusOut() {
  Serial.println("");
}