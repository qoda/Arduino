/*
An example of controlling a Rover 5 chasis over WiFi.
*/

#include "WiFly.h"
#include "Credentials.h"

Server server(80);

boolean read_input = false;

// Instantiate the direction and speed (pwm) pins.
const int directionPinRight = 2;
const int directionPinLeft = 4;
const int speedPin = 3;

int const SpeedFull = 255;
int const SpeedHalf = 128;
int const SpeedStopped = 0;

void setup() {
  WiFly.begin();

  if (!WiFly.join(ssid, passphrase)) {
    while (1) {
      // Hang on failure.
    }
  }

  Serial.begin(9600);
  Serial.print("IP: ");
  Serial.println(WiFly.ip());
  
  // Set the pins as output pins
  pinMode(directionPinRight, OUTPUT);
  pinMode(directionPinLeft, OUTPUT);
  pinMode(speedPin, OUTPUT);
  
  server.begin();
}

void loop() {
  
  // Instantiate the server
  Client client = server.available();
  if (client) {
    // While the client is connected read the input
    while (client.connected()) {
      if (client.available()) {
        int command = client.read();
        
        // Check the query string and set the LED state accordingly
        if (read_input) {
          // Send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
    
          // Go forward
          if (command == 'f') {
            digitalWrite(speedPin, SpeedFull);
            digitalWrite(directionPinLeft, HIGH);
            digitalWrite(directionPinRight, HIGH);
            client.println("Going forward.");
            break;
          }
          
          // Go backwards
          else if (command == 'b') {
            digitalWrite(speedPin, SpeedHalf);
            digitalWrite(directionPinLeft, LOW);
            digitalWrite(directionPinRight, LOW);
            client.println("Going backwards.");
            break;
          }
          
          // Go left
          else if (command == 'l') {
            digitalWrite(speedPin, SpeedHalf);
            digitalWrite(directionPinLeft, LOW);
            digitalWrite(directionPinRight, HIGH);
            client.println("Going left.");
            break;
          }
          
          // Go right
          else if (command == 'r') {
            digitalWrite(speedPin, SpeedHalf);
            digitalWrite(directionPinLeft, HIGH);
            digitalWrite(directionPinRight, LOW);
            client.println("Going right.");
            break;
          }
          
          // Stop
          else if (command == 's') {
            digitalWrite(speedPin, SpeedStopped);
            digitalWrite(directionPinLeft, LOW);
            digitalWrite(directionPinRight, LOW);
            client.println("Stopping.");
            break;
          }
        }
        
        // If a query string is sent continue read the rest of the input as
        // a command
        if (command == '?') {
          read_input = true;
        }
      }
    }
    client.stop();
  }
}
