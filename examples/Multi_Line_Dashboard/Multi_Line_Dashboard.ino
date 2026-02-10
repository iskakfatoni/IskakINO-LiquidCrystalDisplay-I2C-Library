/*
  Multi-Line Dashboard Example
  ----------------------------

  Demonstrates a multi-line dashboard on a 20x4 LCD using I2C (PCF8574).

  Features:
  - Line 1: Temperature & Humidity
  - Line 2: Water Level (progress bar)
  - Line 3: Battery Level (progress bar)
  - Line 4: Status / Message
  - Non-blocking updates using millis()
  - Progress bars using full block characters

  Hardware:
  - HD44780 20x4 LCD
  - I2C backpack (PCF8574 or PCF8574A)
  - Arduino / ESP32 / ESP32-C3 / NodeMCU / Wemos D1

  Wiring:
    LCD SDA → Board SDA
    LCD SCL → Board SCL
    LCD VCC → Board 5V (Arduino) or 3.3V (ESP)
    LCD GND → Board GND

  Author: Iskak Fatoni
  License: MIT
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD 20x4
LiquidCrystal_I2C lcd(20, 4);

unsigned long previousMillis = 0;
const long interval = 1000; // update every 1 second
int counter = 0;

// Example sensor values (simulated)
int temp = 25;
int hum = 60;
int waterLevel = 75; // %
int battery = 90;    // %

void setup() {
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Multi-Line Dashboard");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Update example sensor values
    temp = 20 + (counter % 10);
    hum = 50 + (counter % 20);
    waterLevel = (counter * 3) % 101;
    battery = 90 - (counter % 20);

    // Line 1: Temperature & Humidity
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print((char)223); // degree symbol
    lcd.print("C  Hum: ");
    lcd.print(hum);
    lcd.print("%   ");

    // Line 2: Water Level
    lcd.setCursor(0, 1);
    lcd.print("Water Level: ");
    printProgressBar(waterLevel, 10);

    // Line 3: Battery
    lcd.setCursor(0, 2);
    lcd.print("Battery: ");
    printProgressBar(battery, 10);

    // Line 4: Status / Message
    lcd.setCursor(0, 3);
    lcd.print("Status: Running   ");

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
