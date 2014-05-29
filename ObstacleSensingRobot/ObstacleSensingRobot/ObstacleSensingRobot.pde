/*
A simple example of controlling a Rover 5 robot with serial commands.
*/

int const DirectionRightPin = 2;
int const DirectionLeftPin = 4;
int const MotorSpeedPin = 3;

int const SpeedFull = 255;
int const SpeedHalf = 128;
int const SpeedStopped = 0;

int const ultraSonicPin = 5;
boolean obstacleDetected = false;

int const FWD = 1;
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
}

void loop() {
  
  // Instantiate the required variables
  long duration, distance;
 
  // Trigger ping with a high pulse for 2 or more  milliseconds, cleaning the 
  // high pulse with a low pulse before and after.
  pinMode(ultraSonicPin, OUTPUT);
  digitalWrite(ultraSonicPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(ultraSonicPin, HIGH);
  delayMicroseconds(5);
  
  digitalWrite(ultraSonicPin, LOW);
 
  // Use the same pin to recieve the ping.
  pinMode(ultraSonicPin, INPUT);
  duration = pulseIn(ultraSonicPin, HIGH);
  
  // Convert the time into a distance.
  distance = microsecondsToCentimeters(duration);
  
  Serial.println(distance);
  
  if (distance <= 50) {
    MotorController(STP);
    delay(500);d 
    MotorController(LFT);
    delay(1000);
    MotorController(STP);
    delay(500);
  }
  else {
    MotorController(FWD);
  }
  delay(100);
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

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
