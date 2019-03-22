#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include <OneWire.h>
#include <DallasTemperature.h>

// Setup the display
// Pin 3 - Reset
// Pin 4 - CE
// Pin 5 - DC
// Pin 6 - Din
// Pin 7 - Clk
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Declare temperature variables globally
float temperature;
int tempWhole;
int tempDecimal;
char tempUnit = 'C';

// Declare all back light variables globally
const int backLightButtonPin = 8;
const int backLightPin = 9;
int backLightButtonState = LOW;
int backLightCount = 0;

// Declare the button pin and state which switches unit of measure
const int unitButtonPin = 10;
int unitButtonState = LOW;
int unitOfMeasure = 0;

void setup() {

    // Initialize the display and set the contrast
    display.begin();
    display.clearDisplay();
    display.display();
    display.setContrast(25);

    // Sets the text size and colour
    display.setTextColor(BLACK);

    // Init the sensors (in this case only one)
    sensors.begin();

    // Setup the digital pin
    pinMode(backLightButtonPin, INPUT);
    pinMode(backLightPin, OUTPUT);
    pinMode(unitButtonPin, INPUT);
}

void loop() {
    sensors.requestTemperatures();

    // Wait a second between measurements
    delay(200);

    // Initial font size and text
    display.clearDisplay();
    display.setTextSize(0);
	display.setCursor(20, 0);
	display.print("HACKLAB");


    // Read the button state and swith the back light on for 10 secs
    backLightButtonState = digitalRead(backLightButtonPin);
    if (backLightButtonState == HIGH) {
      	backLightCount = 10;
    }
    if (backLightCount > 0) {
		digitalWrite(backLightPin, HIGH);
		backLightCount -= 1;
    }
    else {
      	digitalWrite(backLightPin, LOW);
    }

	// Read the unit of measure button state and calculate accordingly
    unitButtonState = digitalRead(unitButtonPin);
    if (unitButtonState == HIGH) {
		if (unitOfMeasure == 0) {
			unitOfMeasure = 1;
		}
		else {
			unitOfMeasure = 0;
		}
    }

    // Get the temperature, determine unit of measure and split the decimals out
    // for display purposes
    if (unitOfMeasure == 1) {
		temperature = sensors.getTempFByIndex(0);
		tempUnit = 'F';
    }
    else {
		temperature = sensors.getTempCByIndex(0);
		tempUnit = 'C';
    }

	// Cast the temperature as an integer
    tempWhole = temperature;

    // Display the split temperature to the screen
    display.println("");
    display.setTextSize(3);
	display.setCursor(12, 18);
    display.print(tempWhole);
    display.setTextSize(0);
    display.print("O");
	display.setTextSize(3);
	display.println(tempUnit);

    // Send to the display
    display.display();
}
