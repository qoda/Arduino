/*
A simple push button / LED application as per: 
*/

int potIn = A0;
int ledPin = 9;
int potVal = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
}
void loop() {
  potVal = analogRead(potIn);
  analogWrite(ledPin, potVal / 4);
}


