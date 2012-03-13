/*
Alter the pitch of a peizo by reading from a potentiometers.
*/

const int potPin = A0;
const int piezoPin = 7;

int potVal = 0;
int volumeVal = 0;
int durationVal = 0;

void setup() {
  pinMode(piezoPin, OUTPUT);
}
void loop() {
  potVal = analogRead(potPin);
  
  // maps the tone to the correct output values
  volumeVal = map(potVal, 0, 1023, 1, 2000);
  durationVal = map(potVal, 0, 1023, 1, 1000);
  
  // play the tone
  tone(piezoPin, volumeVal, durationVal);
}
