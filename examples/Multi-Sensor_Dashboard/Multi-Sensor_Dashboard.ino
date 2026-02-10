/*
  Project: Multi-Sensor Dashboard
  -------------------------------

  Demonstrates a multi-line dashboard on a 20x4 LCD using I2C (PCF8574), displaying 4–5 sensor values simultaneously.

  Features:
  - Line 1: Temperature & Humidity
  - Line 2: Water Level & Battery
  - Line 3: Light & Gas sensor (simulated)
  - Line 4: Status / scrolling ticker optional
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

// Folder: examples/Multi_Sensor_Dashboard/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(20, 4);

unsigned long previousMillis = 0;
const long interval = 1000; // update every 1 second
int counter = 0;

// Simulated sensor values
int temp = 25;
int hum = 60;
int waterLevel = 75;
int battery = 90;
int lightLevel = 40;
int gasLevel = 15;

void setup() {
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Multi-Sensor Dashboard");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Update simulated sensor values
    temp = 20 + (counter % 10);
    hum = 50 + (counter % 20);
    waterLevel = (counter * 3) % 101;
    battery = 90 - (counter % 20);
    lightLevel = (counter * 5) % 101;
    gasLevel = (counter * 2) % 101;

    // Line 1: Temperature & Humidity
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temp);
    lcd.print((char)223); // degree symbol
    lcd.print("C  Hum:");
    lcd.print(hum);
    lcd.print("%   ");

    // Line 2: Water Level & Battery
    lcd.setCursor(0, 1);
    lcd.print("Water:");
    printProgressBar(waterLevel, 8);
    lcd.print("Bat:");
    printProgressBar(battery, 8);

    // Line 3: Light & Gas
    lcd.setCursor(0, 2);
    lcd.print("Light:");
    printProgressBar(lightLevel, 8);
    lcd.print("Gas:");
    printProgressBar(gasLevel, 8);

    // Line 4: Status
    lcd.setCursor(0, 3);
    lcd.print("Status: Running...  ");

    counter++;
  }
}

// Helper function: prints a horizontal progress bar
void printProgressBar(int value, int length) {
  int filled = map(value, 0, 100, 0, length);
  for (int i = 0; i < length; i++) {
    if (i < filled) {
      lcd.write(byte(255)); // full block
    } else {
      lcd.write(' ');       // empty space
    }
  }
  lcd.print(" "); // padding
}
