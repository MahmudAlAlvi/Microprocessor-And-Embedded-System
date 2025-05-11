void Obstacle() {
  int distanceR = 0;
  int distanceL = 0;
  Serial.print("Distance: ");
  Serial.println(distance); // Print distance for debugging

  if (distance <= 15) {
    moveStop();
    delay(100);
    Serial.println("Obstacle detected! Stopping!");
    moveBackward();
    delay(500);
    Serial.println("Moving backward!");
    moveStop();
    delay(100);
    Serial.println("Stopped!");
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);
    if (distanceR > distanceL) {
      turnRight();
      Serial.println("Turning right!");
      delay(500);
      moveStop();
      Serial.println("Stopped after turning right.");
      delay(200);
    }
    else if (distanceL > distanceR) {
      turnLeft();
      Serial.println("Turning left!");
      delay(500);
      moveStop();
      Serial.println("Stopped after turning left.");
      delay(200);
    }
  } 
  else {
    moveForward();
    Serial.println("Moving forward.");
  }
}


int lookRight() {
  myservo.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(88); // Adjust this value based on your servo's neutral position
  return distance;
}

int lookLeft() {
  myservo.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(88); // Adjust this value based on your servo's neutral position
  return distance;
}

int readPing() {
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, SPEED);
    analogWrite(ENB, SPEED);
  }
}

void moveBackward() {
  goesForward = false;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}