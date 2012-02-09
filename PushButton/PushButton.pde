/*
A simple push button / LED application as per: 
http://arduino.cc/en/Tutorial/DigitalReadSerial
*/

void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int sensorVal = digitalRead(2);
  if(sensorVal == 1) {
    delay(2);
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}
