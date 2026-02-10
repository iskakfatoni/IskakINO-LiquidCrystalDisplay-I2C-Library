/*
  Project: Advanced Multi-Sensor Dashboard with Alarm
  ---------------------------------------------------

  Demonstrates an advanced multi-line dashboard on a 20x4 LCD using I2C (PCF8574):
  - 4–5 sensor values displayed
  - Line 4: scrolling ticker / status messages
  - Backlight toggle on alarm condition
  - Cursor blink to highlight critical sensor
  - Non-blocking updates using millis()
  - Progress bars using full block characters

  Hardware:
  - HD44780 20x4 LCD
  - I2C backpack (PCF8574 / PCF8574A)
  - Arduino / ESP32 / ESP32-C3 / NodeMCU / Wemos D1

  Wiring:
    LCD SDA → Board SDA
    LCD SCL → Board SCL
    LCD VCC → Board 5V (Arduino) or 3.3V (ESP)
    LCD GND → Board GND

  Author: Iskak Fatoni
  License: MIT
*/

// Folder: examples/Advanced_Dashboard/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(20, 4);

unsigned long previousMillis = 0;
unsigned long tickerMillis = 0;
const long sensorInterval = 1000; // update sensors every 1 sec
const long tickerInterval = 300;  // ticker scroll speed

int counter = 0;

// Simulated sensor values
int temp = 25;
int hum = 60;
int waterLevel = 75;
int battery = 90;
int lightLevel = 40;

// Ticker message
String tickerMessage = "ALERT: Check Water! | System running smoothly... | ";
int tickerPos = 0;

// Alarm threshold
const int waterAlarmThreshold = 20;
bool alarmState = false;

void setup() {
  lcd.begin();
  lcd.backlight();
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Update sensors ---
  if (currentMillis - previousMillis >= sensorInterval) {
    previousMillis = currentMillis;

    // Simulate sensor values
    temp = 20 + (counter % 10);
    hum = 50 + (counter % 20);
    waterLevel = (counter * 3) % 101;
    battery = 90 - (counter % 20);
    lightLevel = (counter * 5) % 101;

    // --- Line 1: Temp & Humidity ---
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temp);
    lcd.print((char)223); // degree symbol
    lcd.print("C  Hum:");
    lcd.print(hum);
    lcd.print("%   ");

    // --- Line 2: Water Level & Battery ---
    lcd.setCursor(0, 1);
    lcd.print("Water:");
    printProgressBar(waterLevel, 8);
    lcd.print("Bat:");
    printProgressBar(battery, 8);

    // --- Line 3: Light sensor ---
    lcd.setCursor(0, 2);
    lcd.print("Light:");
    printProgressBar(lightLevel, 12);

    // --- Alarm handling ---
    if (waterLevel < waterAlarmThreshold) {
      alarmState = true;
      lcd.backlight();       // ensure backlight is on
      lcd.setCursor(0, 3);
      lcd.blink();           // blink cursor for alert
    } else {
      alarmState = false;
      lcd.noBlink();
    }

    // --- Status line (line 4) ---
    lcd.setCursor(0, 3);
    lcd.print("Status: Running...  ");

    counter++;
  }

  // --- Update ticker line independently ---
  if (currentMillis - tickerMillis >= tickerInterval) {
    tickerMillis = currentMillis;

    String displayText = tickerMessage.substring(tickerPos);
    if (displayText.length() < 20) {
      displayText += tickerMessage.substring(0, 20 - displayText.length());
    }

    lcd.setCursor(0, 3);
    lcd.print(displayText);

    tickerPos++;
    if (tickerPos >= tickerMessage.length()) {
      tickerPos = 0;
    }
  }
}

// Helper: horizontal progress bar
void printProgressBar(int value, int length) {
  int filled = map(value, 0, 100, 0, length);
  for (int i = 0; i < length; i++) {
    if (i < filled) lcd.write(byte(255));
    else lcd.write(' ');
  }
  lcd.print(" ");
}
