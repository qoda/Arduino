#include <EEPROM.h>
#include <DFRobot_SHT3x.h>
#include <string.h>
#include "U8glib.h"

#define TOUCH_PIN 4  // Pin connected to touch sensor
#define DISPLAY_UPDATE_INTERVAL 5000L  // milliseconds between sensor reads and display updates
#define DISPLAY_SLEEP_TIMEOUT 60000L  // milliseconds of inactivity before display sleeps
#define LONG_PRESS_DURATION 100 // Number of loop iterations for long press (approx 5 seconds with 50ms delay)

// Display units state
bool isTemperature = true;
int previousTouchState = LOW;  // Track previous state for edge detection
unsigned long lastDisplayUpdate = 0;
unsigned long displayWakeTime = 0;
unsigned long currentMillis = 0;
unsigned long touchCounter = 0;
bool displayOn = true;

// Store minimum and maximum readings in EEPROM
struct TemperatureMetrics
{
  int min;
  int max;
};
struct HumidityMetrics
{
  int min;
  int max;
};
TemperatureMetrics temperatureMetrics = {100, -100};
HumidityMetrics humidityMetrics = {100, -100};

U8GLIB_SH1106_128X64 display(U8G_I2C_OPT_NONE);
DFRobot_SHT3x sensor;

void setup()
{
  pinMode(TOUCH_PIN, INPUT);
  display.setColorIndex(255);

  // Start display in sleep mode
  if (!displayOn) display.sleepOn();

  // Get temperature and humidity metrics from eeprom
  EEPROM.get(0, temperatureMetrics.min);
  EEPROM.get(sizeof(int), temperatureMetrics.max);
  EEPROM.get(2 * sizeof(int), humidityMetrics.min);
  EEPROM.get(3 * sizeof(int), humidityMetrics.max);
}

void loop()
{
  currentMillis = millis();

  // Read touch sensor
  int touchReading = digitalRead(TOUCH_PIN);

  // Detect falling edge (HIGH -> LOW) and toggle immediately
  if (touchReading == LOW && previousTouchState == HIGH)
  {

    // Toggle display state
    if (displayOn)
    {
      isTemperature = !isTemperature;
    }
    else
    {
      display.sleepOff();
      displayOn = true;
      displayWakeTime = currentMillis;
    }

    // Force immediate display update after toggle
    lastDisplayUpdate = 0;

    // reset the touch counter
    touchCounter = 0;
  }
  previousTouchState = touchReading;

  while (touchReading == HIGH)
  {
    // Start a counter in order to detect long press
    touchReading = digitalRead(TOUCH_PIN);
    touchCounter++;
    if (touchCounter >= LONG_PRESS_DURATION)
    {
      resetMetrics();
      touchCounter = 0;
      lastDisplayUpdate = 0;
      break;
    }

    delay(50);  // Debounce delay
  }

  // Update display only at specified interval
  if (currentMillis - lastDisplayUpdate >= DISPLAY_UPDATE_INTERVAL)
  {

    // Update diplay timer
    lastDisplayUpdate = currentMillis;

    float reading = isTemperature ? sensor.getTemperatureC() : sensor.getHumidityRH();

    // Make buffer larger to safely hold number + symbol + null
    char readingBuffer[12];

    // Use a C-string for the symbol so strncat receives a char*
    const char *readingSymbol;
    if (isTemperature)
    {
      readingSymbol = "C";
    }
    else
    {
      readingSymbol = " %";
    }

    // Update min/max and store in EEPROM
    storeMetrics(reading, isTemperature);

    // Convert float to char buffer with no decimal places
    dtostrf(reading, 0, 0, readingBuffer);

    if (displayOn)
    {
      displayReading(readingBuffer, readingSymbol);

      // Disable display after 60 seconds of inactivity;
      if (currentMillis - displayWakeTime >= DISPLAY_SLEEP_TIMEOUT)
      {
        display.sleepOn();
        displayOn = false;
      }
    }
  }

  // Small delay to prevent excessive CPU usage; touch is still very responsive
  delay(10);
}

void displayReading(const char *reading, const char *unit)
{
  display.firstPage();
  do
  {
    // Draw the current reading centered on the display
    display.setFont(u8g_font_helvB24);
    drawCentreString(reading, 0, 0);

    display.setFont(u8g_font_helvB08);
    drawCentreString(unit, 22, -6);

    // Draw min and max readings at the bottom
    display.setFont(u8g_font_helvR08);
    char metricBuffer[32];
    if (isTemperature)
    {
      snprintf(metricBuffer, sizeof(metricBuffer), "Min: %d%s  |  Max: %d%s", temperatureMetrics.min, unit, temperatureMetrics.max, unit);
    }
    else
    {
      snprintf(metricBuffer, sizeof(metricBuffer), "Min: %d%s  |  Max: %d%s", humidityMetrics.min, unit, humidityMetrics.max, unit);
    }
    drawCentreString(metricBuffer, 0, 28);

  }
  while (display.nextPage());
}

void drawCentreString(const char *text, int x_offset, int y_offset)
{
  // Calculate width and height of the text
  u8g_uint_t textWidth = display.getStrWidth(text);
  u8g_uint_t fontAscent = display.getFontAscent();
  u8g_uint_t fontDescent = display.getFontDescent();
  u8g_uint_t textHeight = fontAscent + abs(fontDescent);

  // Calculate position to center the text
  u8g_uint_t x = (display.getWidth() - textWidth) / 2 + x_offset;
  u8g_uint_t y = (display.getHeight() + textHeight) / 2 + y_offset;

  display.drawStr(x, y, text);
}

void storeMetrics(float reading, bool isTemperature)
{
  if (isTemperature)
  {
    int tempReading = static_cast<int>(reading);
    if (tempReading < temperatureMetrics.min) {
      temperatureMetrics.min = tempReading;
      EEPROM.put(0, temperatureMetrics.min);
    }
    if (tempReading > temperatureMetrics.max) {
      temperatureMetrics.max = tempReading;
      EEPROM.put(sizeof(int), temperatureMetrics.max);
    }
  }
  else
  {
    int humidityReading = static_cast<int>(reading);
    if (humidityReading < humidityMetrics.min) {
      humidityMetrics.min = humidityReading;
      EEPROM.put(2 * sizeof(int), humidityMetrics.min);
    }
    if (humidityReading > humidityMetrics.max) {
      humidityMetrics.max = humidityReading;
      EEPROM.put(3 * sizeof(int), humidityMetrics.max);
    }
  }
}

void resetMetrics()
{
  temperatureMetrics.min = 100;
  temperatureMetrics.max = -100;
  humidityMetrics.min = 100;
  humidityMetrics.max = -100;

  EEPROM.put(0, temperatureMetrics.min);
  EEPROM.put(sizeof(int), temperatureMetrics.max);
  EEPROM.put(2 * sizeof(int), humidityMetrics.min);
  EEPROM.put(3 * sizeof(int), humidityMetrics.max);
}
