/*
A reletively precise digital thermometer.
*/

// Set the analog pin
int sensorPin = A0;
int sensorReading = 0;
int ledPin = 11;
int ledBrightness = 0;

void setup () {
  Serial.begin(9600);
}

void loop () {
  
  // Read the sensor value
  sensorReading = analogRead(sensorPin);
  sensorReading -= 1024;
  
  // Calculate what brightess to activate the led at
  ledBrightness = map(sensorReading, 1023, 0, 0, 255);
  ledBrightness -= 255;
  
  // Set the LED bightness
  Serial.println(ledBrightness);
  
  // Switch the led off if it becomes bright enough
  if (ledBrightness < 100) {
    ledBrightness = 0;
  }
  analogWrite(ledPin, ledBrightness);
}
