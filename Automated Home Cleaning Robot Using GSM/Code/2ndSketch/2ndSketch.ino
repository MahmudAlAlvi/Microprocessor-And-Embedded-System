///////////////////////////////////////////////////////////////Second Sketch////////////////////////////////////////////////////////////////////////////////
#include <AFMotor.h>
#define Trig 12
#define Echo 13
#define ENA 5
#define ENB 6
#define IN1 3
#define IN2 4
#define IN3 2
#define IN4 7
float cm; //Distance variable
float temp; //

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);


}

void loop() {
 
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  temp = float(pulseIn(Echo, HIGH));
  cm = (temp * 17 ) / 1000;
  if (cm < 30 && cm > 10)
  {
    back();
    delay(500);
    rotateFullyBack();
    delay(200);
  }
  if (cm >= 30)
  {
    forward();
    delay(100);
  }


  if (cm < 10)
  {
    STOP();
  }
  Serial.print("Echo =");
  Serial.print(temp);
  Serial.print(" | | Distance = ");
  Serial.print(cm);
  Serial.println("cm");
  delay(100);
}

void forward() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
Serial.println("Forward");
}

void back() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}


void Left() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Left");
}

void Right() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}
void rotateFullyBack() {
  unsigned long startTime = millis(); // Record the start time

  while (millis() - startTime < 2500) { // Rotate fully back for 5000 milliseconds (5 seconds)
    analogWrite(ENA, 220);
    analogWrite(ENB, 220);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("Rotate Fully Back");
  }
  // Stop the motors after the specified duration
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void STOP() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("STOP");
}
