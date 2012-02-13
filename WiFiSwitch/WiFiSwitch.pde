/*
 * A simple web service which to switch an LED on and off over HTTP.
 */

#include "WiFly.h"
#include "Credentials.h"

Server server(80);

boolean read_input = false;
int state = LOW;

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
  
  pinMode(9, OUTPUT);
  
  server.begin();
}

void loop() {
  
  // Instantiate the server
  Client client = server.available();
  if (client) {
    
    // While the client is connected read the input
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        // Check the query string and set the LED state accordingly
        if (read_input) {
          
          // Switch the LED off
          if (c == '0') {
            state = LOW;
          }
          
          // Switch the LED on
          else if (c == '1') {
            state = HIGH;
          }
          
          // Quit the application
          else {
            read_input = false;
            break;
          }
        }
        
        // If a query string is sent continue read the rest of the input as
        // a command
        if (c == '?') {
          read_input = true;
        }
      }
    }
    delay(100);
    client.stop();
  }
  
  // Set the LED state
  digitalWrite(9, state);
}
