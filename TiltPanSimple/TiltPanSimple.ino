
#include <Servo.h>

// instantiate servo pins
Servo servoPan;
Servo servoTilt;

// instantiate servo & joystrick positions for tracking purpose
int servoPanPosition = 0;
int servoTiltPosition = 0;

void setup() {
  
  // setup the servo pins
  servoPan.attach(9);
  servoTilt.attach(8);
  
  // move the servo to a start position
  servoPan.write(90);
  servoTilt.write(180);
  
  // serial i/o
  Serial.begin(9600);

}

void loop() {

  if ( Serial.available()) {
    
  }

  servoPanPosition = random(30, 180);
  servoTiltPosition = random(90, 180);

  servoPan.write(servoPanPosition);
  delay(1000);
  servoTilt.write(servoTiltPosition);
  delay(1000);

  Serial.print("Pan: ");
  Serial.println(servoPanPosition);

  Serial.print("Tilt: ");
  Serial.println(servoTiltPosition);

  Serial.println("---------------------");

  delay(3000);
}
