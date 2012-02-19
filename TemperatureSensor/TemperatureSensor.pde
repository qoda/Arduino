/*
A reletively precise digital thermometer.
*/

// Set the analog pin
int sensorPin = A0;
int sensorReading = 0;
float voltageReading = 0.0;
float temperatureCelcius = 0.0;

void setup () {
  Serial.begin(9600);
}

void loop () {
  
  // Read the sensor value
  sensorReading = analogRead(sensorPin);
  
  // Calculate the temperature in celcius
  temperatureCelcius = (5.0 * sensorReading * 100.0) / 1024.0;
  
  // Finally print the temperature and wait for 1 sec
  Serial.println(temperatureCelcius);
  delay(1000);
}
