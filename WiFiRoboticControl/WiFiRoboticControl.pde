/*
An example of controlling a Rover 5 chasis over WiFi.
*/

#include "WiFly.h"
#include "Credentials.h"

Server server(80);

boolean read_input = false;

// Instantiate the direction and speed (pwm) pins.
int directionPinLeft = 2;
int directionPinRight = 4;
int speedPinLeft = 3;
int speedPinRight = 5;

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
  pinMode(speedPinLeft, OUTPUT);
  pinMode(directionPinLeft, OUTPUT);
  pinMode(speedPinRight, OUTPUT);
  pinMode(directionPinRight, OUTPUT);
  
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
            digitalWrite(speedPinLeft, HIGH);
            digitalWrite(directionPinLeft, HIGH);
            digitalWrite(speedPinRight, HIGH);
            digitalWrite(directionPinRight, HIGH);
            client.println("Going forward.");
            break;
          }
          
          // Go backwards
          else if (command == 'b') {
            digitalWrite(speedPinLeft, HIGH);
            digitalWrite(directionPinLeft, LOW);
            digitalWrite(speedPinRight, HIGH);
            digitalWrite(directionPinRight, LOW);
            client.println("Going backwards.");
            break;
          }
          
          // Go left
          else if (command == 'l') {
            digitalWrite(speedPinLeft, HIGH);
            digitalWrite(directionPinLeft, LOW);
            digitalWrite(speedPinRight, HIGH);
            digitalWrite(directionPinRight, HIGH);
            client.println("Going left.");
            break;
          }
          
          // Go right
          else if (command == 'r') {
            digitalWrite(speedPinLeft, HIGH);
            digitalWrite(directionPinLeft, HIGH);
            digitalWrite(speedPinRight, HIGH);
            digitalWrite(directionPinRight, LOW);
            client.println("Going right.");
            break;
          }
          
          // Stop
          else if (command == 's') {
            digitalWrite(speedPinLeft, LOW);
            digitalWrite(directionPinLeft, LOW);
            digitalWrite(speedPinRight, LOW);
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
