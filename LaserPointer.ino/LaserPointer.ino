int laserPin = 4;
int buttonPin = 2;
int buttonState = 0;

void setup() {
  pinMode(laserPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == 1) {
    digitalWrite(laserPin, HIGH);
    delay(50);
  } else {
    digitalWrite(laserPin, LOW);
    delay(50);
  }
}
