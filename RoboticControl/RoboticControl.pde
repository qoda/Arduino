/*
A simple example of controlling a Rover 5 robot with serial commands.
*/

void setup() {
  Serial.begin(9500);
  
  // Setup the digital pins
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.read();
    
    // Go forward
    if (command == 'f') {
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      Serial.println("Going forward.");
    }
    
    // Go backwards
    else if (command == 'b') {
      digitalWrite(3, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      Serial.println("Going backwards.");
    }
    
    // Go left
    else if (command == 'l') {
      digitalWrite(3, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      Serial.println("Going left.");
    }
    
    // Go right
    else if (command == 'r') {
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      Serial.println("Going right.");
    }
    
    // Stop
    else if (command == 's') {
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      Serial.println("Stopping.");
    }
  }
}
