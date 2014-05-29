// instantiate direction sensor pins
const int sensorPin = 0;

void setup() {
  // output to serial
  Serial.begin(9600);
}

void loop() {
  int sensorOutput = analogRead(sensorPin);
  
  // convert to voltage
  float voltage = sensorOutput * 5.0;
  voltage /= 1024.0;
  
  Serial.print("Voltage: ");
  Serial.print(voltage); 
  Serial.println("v");
  
  // calculate the temperature
  float temperature = (voltage) * 100;
  
  Serial.print("Temperature: ");
  Serial.print(temperature); 
  Serial.println("c");
  
  delay(1000);
}
