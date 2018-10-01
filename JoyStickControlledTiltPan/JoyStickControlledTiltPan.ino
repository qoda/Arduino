
#include <Servo.h>

// instantiate servo pins
Servo servoPan;
Servo servoTilt;

// instantiate servo & joystrick positions for tracking purpose
int servoPanPosition = 0;
int servoTiltPosition = 0;

int joystickXPosition = 0;
int joystickYPosition = 0;

// instantiate the joystick pins
int joystickXPin = 0;
int joystickYPin = 1;

void setup() {

  // setup the servo pins
  servoPan.attach(9);
  servoTilt.attach(8);

}

void loop() {

  // Get the joystrick position
  joystickXPosition = analogRead(joystickXPin);
  joystickYPosition = analogRead(joystickYPin);

  // Map the joystick position to the servo position and than write it
  servoPanPosition = map(joystickXPosition, 0, 1023, 0, 170);
  servoTiltPosition = map(joystickYPosition, 0, 1023, 90, 180);
  servoPan.write(servoPanPosition);
  servoTilt.write(servoTiltPosition);

  delay(250);
}
