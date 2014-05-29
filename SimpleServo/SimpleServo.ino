#include <Servo.h>

Servo servo_pan;
Servo servo_tilt;

const int powerButtonPin = 2;

int servoPosition = 0;
int powerState = 0;

void setup() {
  pinMode(powerButtonPin, INPUT);
  
  servo_pan.attach(5);
  servo_tilt.attach(6);
}

void loop() {
  
  for(servoPosition = 0; servoPosition < 180; servoPosition += 1) {
    servo_pan.write(servoPosition);
    if (servoPosition < 120 && servoPosition > 50) {
      servo_tilt.write(servoPosition);
    }
    delay(15);
  } 
  for(servoPosition = 180; servoPosition>=1; servoPosition-=1) {
    servo_pan.write(servoPosition);
    if (servoPosition < 120 && servoPosition > 50) {
      servo_tilt.write(servoPosition);
    }
    delay(15);
  }
} 

