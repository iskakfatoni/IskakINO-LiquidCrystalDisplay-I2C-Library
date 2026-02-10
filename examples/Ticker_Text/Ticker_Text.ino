/*
  Ticker_Text.ino
  ------------------------------------------------------------
  Example for IskakINO_LiquidCrystal_I2C library

  Demonstrates:
  - Smooth ticker (running text) on LCD
  - Non-blocking update using millis()
  - Manual text shifting (no lcd.clear() flicker)
  - Suitable for ESP32 and Arduino projects

  LCD:
  - Type : HD44780 + I2C (PCF8574)
  - Size : 16x2

  Wiring:
  - SDA -> SDA
  - SCL -> SCL
  - VCC -> 5V / 3.3V
  - GND -> GND

  Created by : Iskak Fatoni
  Library    : IskakINO_LiquidCrystal_I2C
  Version    : 1.0.1
*/
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(16, 2);

const char message[] = "  Welcome to IskakINO LiquidCrystal I2C Library  ";
const uint8_t lcdWidth = 16;

unsigned long lastTick = 0;
uint8_t indexPos = 0;

void setup() {
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Ticker Demo");

  lcd.setCursor(0, 1);
  lcd.print("Starting...");
}

void loop() {
  unsigned long now = millis();

  // Update ticker every 250 ms
  if (now - lastTick >= 250) {
    lastTick = now;
    updateTicker();
  }
}

void updateTicker() {
  lcd.setCursor(0, 1);

  for (uint8_t i = 0; i < lcdWidth; i++) {
    uint8_t charIndex = (indexPos + i) % (sizeof(message) - 1);
    lcd.print(message[charIndex]);
  }

  indexPos++;
  if (indexPos >= sizeof(message) - 1) {
    indexPos = 0;
  }
}
