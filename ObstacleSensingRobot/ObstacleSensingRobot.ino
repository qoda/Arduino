/*
An ulta-sonic obstacle detecting robot.
*/

const int ultraSonicPin = 5;

const int motorSpeedRight = 3;
const int motorSpeedLeft = 11;
const int motorDirectionRight = 12;
const int motorDirectionLeft = 13;

void setup() {
  Serial.begin(9600);
  
  pinMode(motorSpeedRight, OUTPUT);
  pinMode(motorSpeedLeft, OUTPUT);
  pinMode(motorDirectionRight, OUTPUT);
  pinMode(motorDirectionLeft, OUTPUT);
}
 
void loop() {
  
  // Instantiate the required variables
  long duration, distance, acceleration;
 
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
  
  // Make a variable speed depending on the distance from obsticle
  if (distance >= 255) {
    acceleration = 255;
  }
  else if (distance <= 100) {
    acceleration = 100;
  }
  else {
    acceleration = distance;
  }
  
  if (distance < 15) {
    goLeft();
    Serial.println("Turn...");
  }
  else {
    digitalWrite(motorDirectionRight, HIGH);
    digitalWrite(motorDirectionLeft, HIGH);
    analogWrite(motorSpeedRight, acceleration);
    analogWrite(motorSpeedLeft, acceleration);
    
    Serial.println("Forward...");
  }
  
  delay(100);
}

void goForward (long speed) {
  digitalWrite(motorDirectionRight, HIGH);
  digitalWrite(motorDirectionLeft, HIGH);
  analogWrite(motorSpeedRight, 255);
  analogWrite(motorSpeedLeft, 255);
}

void goLeft () {
  digitalWrite(motorDirectionRight, HIGH);
  digitalWrite(motorDirectionLeft, LOW);
  analogWrite(motorSpeedRight, 100);
  analogWrite(motorSpeedLeft, 100);
}
 
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter, therefor
  // because the distance travels to the obstacle and back again the distance
  // is halfed.
  return microseconds / 29 / 2;
}
