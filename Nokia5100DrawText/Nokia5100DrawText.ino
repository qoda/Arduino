#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

void setup() {
    display.begin();
    display.clearDisplay();
    display.setContrast(30);

    // Sets the text size and colour and prints a line to the diplay once.
    display.setTextSize(0);
    display.setTextColor(BLACK);
    printWords("Testing Arduino + Nokia 5110 Display...");
}

void loop() {
    // Loop not required, we print once.
}

void printWords (String words) {
    display.println(words);
    display.display();
}
