void taskSonarObstaculo() {
  Serial.println("SONAR OBSTÁCULO");
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
  Serial.print("duration = ");
  Serial.println(duration);

  // convert the time into a distance
  cm = (duration / 2) / 29.1;

  Serial.print("SONAR OBSTACULO: ");
  Serial.println(cm);

  if(cm < 5){
    FLAG = 1;
  }
}

void taskSonarQueda() {
  Serial.println("SONAR QUEDA");
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

  Serial.print("SONAR QUEDA: ");
  Serial.println(cm);

  if(cm > 5){
    FLAG = 1;
  } 
}
