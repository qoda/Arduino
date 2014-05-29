/*
A simple example of controlling a Rover 5 robot with serial commands.
*/

#include <Servo.h>

Servo panServo;
Servo tiltServo;

int const DirectionRightPin = 2;
int const DirectionLeftPin = 4;
int const MotorSpeedPin = 3;

int const SpeedFull = 255;
int const SpeedHalf = 128;
int const SpeedStopped = 0;

int tiltServoPosition = 90;
int panServoPosition = 90;

int const sensorTopPin = A1;
int const sensorLeftPin = A2;
int const sensorBottomPin = A3;
int const sensorRightPin = A4;

int const sensorTopVal;
int const sensorLeftVal;
int const sensorBottomVal;
int const sensorRightVal;

const int irPin = 5;
const int ledPin = 13;

int const FRW = 1;
int const BKW = 2;
int const LFT = 3;
int const RHT = 4;
int const STP = 5;

void setup() {
  Serial.begin(9600);
  
  // Setup the digital pins
  pinMode(DirectionRightPin, OUTPUT);
  pinMode(DirectionLeftPin, OUTPUT);
  pinMode(MotorSpeedPin, OUTPUT);
  
  // Setup the pan and tilt servos
  tiltServo.attach(9);
  panServo.attach(10);
  
  // Setup all the required ir sensor pin modes
  pinMode(sensorTopPin, INPUT);
  pinMode(sensorLeftPin, INPUT);
  pinMode(sensorBottomPin, INPUT);
  pinMode(sensorRightPin, INPUT);
  pinMode(irPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  // Swith the IR leds on
  digitalWrite(irPin, HIGH);
}

void loop() {
  // Determine if the object has moved in a certain direction
  int detectionTop = DetectMovement(sensorTopVal, analogRead(sensorTopPin));
  int detectionBottom = DetectMovement(sensorBottomVal, analogRead(sensorBotoomPin));
  int detectionLeft = DetectMovement(sensorLeftVal, analogRead(sensorLeftPin));
  int detectionRight = DetectMovement(sensorRightVal, analogRead(sensorRightPin));
  
  if (detectionTop > detectionBottom) {
    tiltServo.write(tiltServoPosition - 5);
  }
  else if (detectionTop < detectionBottom) {
    tiltServo.write(tiltServoPosition + 5);
  }
  if (detectionLeft < detectionRight) {
    tiltServo.write(panServoPosition - 5);
  }
  else if (detectionLeft > detectionRight) {
    tiltServo.write(panServoPosition + 5);
  }
  
  // Read analog ir sensor values
  sensorTopVal = analogRead(sensorTopPin);
  sensorBottomVal = analogRead(sensorBottomPin);
  sensorLeftVal = analogRead(sensorLeftPin);
  sensorRightVal = analogRead(sensorRightPin);
  
  delay(10);
}

int DetectMovement (int previousVal, int newVal) {
  newVal = newVal / 5;
  previousVal = previousVal / 5;
  if (previousVal == newVal) {
    return 0;
  }
  else if (previousVal < newVal) {
    return 1;
  }
  else if (previousVal > newVal) {
    return -1;
  }
}

void MotorController (int command) {
  digitalWrite(MotorSpeedPin, SpeedFull);
  
  // Go forwards
  if (command == 1) {
    digitalWrite(DirectionRightPin, HIGH);
    digitalWrite(DirectionLeftPin, HIGH);
  }
  
  // Go backwards
  else if (command == 2) {
    digitalWrite(DirectionRightPin, LOW);
    digitalWrite(DirectionLeftPin, LOW);
  }
  
  // Go left
  else if (command == 3) {
    digitalWrite(DirectionRightPin, LOW);
    digitalWrite(DirectionLeftPin, HIGH);
  }
  
  // Go right
  else if (command == 4) {
    digitalWrite(DirectionRightPin, HIGH);
    digitalWrite(DirectionLeftPin, LOW);
  }
  
  // Stop
  else if (command == 5) {
     digitalWrite(MotorSpeedPin, SpeedStopped);
  }
}
