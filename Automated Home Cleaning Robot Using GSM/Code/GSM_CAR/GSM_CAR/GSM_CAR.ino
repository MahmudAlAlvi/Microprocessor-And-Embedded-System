#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Servo.h>

// Define pin numbers
int ENA = 5;
int IN1 = 3;
int IN2 = 4;

int ENB = 6;
int IN3 = 10;
int IN4 = 11;

// Ultrasonic sensor pin definitions
#define TRIG_PIN 12
#define ECHO_PIN 13

// Maximum distance and speed
#define MAX_DISTANCE 200
#define SPEED 55  

// Initialize NewPing object
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Servo pin definition
#define SERVO_PIN 9
Servo myservo;

// Initialize SoftwareSerial object for SIM900 communication
SoftwareSerial mySerial(7, 8); // SIM900 Tx & Rx is connected to Arduino #7 & #8

// Global variables
// Global variables
boolean goesForward = false;
// boolean allowMovement = false; // Flag to control movement based on SMS
char sms;
int distance;
unsigned long lastPingTime = 0;
unsigned long pingInterval = 100; // Ping interval in milliseconds

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myservo.attach(SERVO_PIN);
  myservo.write(88); // Adjust this value based on your servo's neutral position
  delay(2000); // Delay for stability

  // Initial distance readings
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();

  mySerial.println("AT+CMGS=\"+8801740784444\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();

  mySerial.print("Device Started."); //text content
  updateSerial();
  mySerial.write(26);
}

void loop() {
  if (millis() - lastPingTime >= pingInterval) {
    lastPingTime = millis();
    distance = readPing();
  }
  // // Check for incoming SMS only if movement is allowed
  // if (allowMovement) {
  //   checkSMS();
  // }

  // updateSerial(); 

  // if (sms == "ON") {
  //   allowMovement = true;
  // }

  // if (allowMovement){
  //   Obstacle();
  // }

  Obstacle();

  // Execute obstacle avoidance routine
  // Obstacle();
}