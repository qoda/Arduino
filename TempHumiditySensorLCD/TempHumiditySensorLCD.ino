#include <SPI.h>

#include <DHT.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


// The temperature/humidity sensor pin
// Connect a 10k resistor from pin 2 to 5V
#define DHTPIN 2

// Use type 11 of the sensor component.
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Setup the display
// Pin 3 - reset
// Pin 4 - CE
// Pin 5 - DC
// Pin 6 - Din
// Pin 7 - Clk
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

void setup() {
    Serial.begin(9600);
    dht.begin();

    // Initialize the display and set the contrast
    display.begin();
    display.clearDisplay();
    display.setContrast(30);

    // Sets the text size and colour
    display.setTextSize(0);
    display.setTextColor(BLACK);
}

void loop() {

    // Start with a clear display
    display.clearDisplay();

    // Wait a few seconds between measurements
    delay(2000);

    // Reading temperature or humidity takes about 250 milliseconds!
    float humidity = dht.readHumidity();

    // Read temperature as Celsius (the default)
    float temperature = dht.readTemperature();

    // Check if any reads failed and exit early (to try again)
    if (isnan(humidity) || isnan(temperature)) {
        display.println("Failed to read from DHT sensor!");
        display.display();
        return;
    }

    Serial.println(humidity);

    // Display the humidity
    display.println("Humidity: ");
    display.print(humidity);
    display.println("%");

    // Space in between the metrics
    display.println("");

    // Display the temperature
    display.println("Temperature: ");
    display.print(temperature);
    display.println(" *C ");

    // Send to the display
    display.display();
}
