/*
A vehicle park distance control sketch.
*/

const int ultraSonicPin = 3;
const int piezoPin = 8;

void setup() {
  Serial.begin(9600);
}
 
void loop() {
  
  // Instantiate the required variables
  long duration, distance;
 
  // Trigger ping with a high pulse for 2 or more  milliseconds, cleaning the 
  // high pulse with a low pulse before and after.
  pinMode(ultraSonicPin, OUTPUT);
  digitalWrite(ultraSonicPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(ultraSonicPin, HIGH);
  delayMicroseconds(5);
  
  digitalWrite(ultraSonicPin, LOW);
 
  // Use the same pin to recieve the ping.
  pinMode(ultraSonicPin, INPUT);
  duration = pulseIn(ultraSonicPin, HIGH);
  
  // Convert the time into a distance.
  distance = microsecondsToCentimeters(duration);

  Serial.println(digitalRead(ultraSonicPin));
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  
  // Play a tone on a piezo more frequently the closer the obstacle gets.
  tone(piezoPin, 2000);
  
  delay(100);
}
 
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter, therefor
  // because the distance travels to the obstacle and back again the distance
  // is halfed.
  return microseconds / 29 / 2;
}
