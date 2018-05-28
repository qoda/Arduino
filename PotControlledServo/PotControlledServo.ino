// Pot controlled servo
#include <Servo.h>

Servo myServo;

int potPin = 0;
int storedValue;

void setup() {
  myServo.attach(9);

}

void loop() {
  storedValue = analogRead(potPin);
  storedValue = map(storedValue, 0, 1023, 0, 180);
  myServo.write(storedValue);
  delay(15);
}
