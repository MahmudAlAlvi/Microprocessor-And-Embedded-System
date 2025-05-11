///////////////////////////////////////////////////////////////First Sketch////////////////////////////////////////////////////////////////////////////////
//define L298n module IO Pin
int ENA = 5;
int IN1 = 3;
int IN2 = 4;

int ENB = 6;
int IN3 = 2;
int IN4 = 7;

#define MotorASpeed 40
#define MotorBSpeed 40

int Sensor1 = 0;
int Sensor4 = 0;

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(Sensor1, INPUT);
  pinMode(Sensor4, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  Sensor1 = digitalRead(8);
  Sensor4 = digitalRead(11);

  if (Sensor1 == HIGH && Sensor4 == HIGH)
  {
    //Stop both Motors
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite (ENA, 0);
    analogWrite (ENB, 0);
    Serial.println("Both IR is on black line - stop");
  }
  else if (Sensor1 == LOW && Sensor4 == LOW)
  {
    //Move both the Motors
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite (ENA, MotorASpeed);
    analogWrite (ENB, MotorBSpeed);
   Serial.println("IR not on black line - go foward");
  }

  else if (Sensor1 == LOW && Sensor4 == HIGH)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite (ENA, 120);
    analogWrite (ENB, 120);
   Serial.println("Move left");
  }

  else if (Sensor1 == HIGH && Sensor4 == LOW)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite (ENA, 120);
    analogWrite (ENB, 120);
    Serial.println("Move right");
  }

  else
  {
    //Stop both the motors
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite (ENA, 0);
    analogWrite (ENB, 0);
    Serial.println("stop");
  }
}

