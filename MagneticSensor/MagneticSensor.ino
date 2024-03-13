const int ledPin = 4;
const int hallEffectPin = 5;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int hallEffectValue = map(analogRead(hallEffectPin), 0, 1023, 0, 255);

  if (hallEffectValue < 255) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(1000);
}