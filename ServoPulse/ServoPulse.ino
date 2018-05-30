#include <Servo.h>

Servo servo;

int servoPosition = 0;

void setup() {
    servo.attach(9);
}

void loop() {
    servo.writeMicroseconds(1500);
    delay(500);
    servo.writeMicroseconds(1000);
    delay(500);
    servo.writeMicroseconds(2000);
    delay(500);
}
