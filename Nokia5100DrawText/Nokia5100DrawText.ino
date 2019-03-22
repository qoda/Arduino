#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Setup the display
// Pin 3 - reset
// Pin 4 - CE
// Pin 5 - DC
// Pin 6 - Din
// Pin 7 - Clk
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

void setup() {
    Serial.begin(9600);

    // Initialize the display and set the contrast
    display.begin();
    display.clearDisplay();
    display.setContrast(25);

    // Sets the text size and colour
    display.setTextColor(BLACK);
}

void loop() {

    // Start with a clear display
    display.clearDisplay();

    // Wait a few seconds between measurements
    delay(2000);

    display.setTextSize(0);
    display.println("");

    display.setTextSize(2);
    display.println("134.00");
    
    display.setTextSize(0);
    display.println("Celcius");

    // Send to the display
    display.display();
}
