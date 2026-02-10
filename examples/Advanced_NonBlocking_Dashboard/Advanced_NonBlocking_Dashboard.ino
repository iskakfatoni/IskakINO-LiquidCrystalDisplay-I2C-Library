/*
  Advanced_NonBlocking_Dashboard.ino
  ------------------------------------------------------------
  Advanced example for IskakINO_LiquidCrystal_I2C library

  Demonstrates:
  - Non-blocking LCD updates using millis()
  - Partial screen refresh (no lcd.clear() spam)
  - Simple status dashboard layout
  - Suitable for ESP32 & Arduino multitasking projects

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
  Version    : 1.0.0
*/
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(16, 2);

unsigned long lastUpdate = 0;
unsigned long lastUptimeUpdate = 0;

uint32_t counter = 0;

void setup() {
  Serial.begin(115200);

  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("System: READY");

  lcd.setCursor(0, 1);
  lcd.print("Count: 0");
}

void loop() {
  unsigned long now = millis();

  // Update counter every 500 ms (non-blocking)
  if (now - lastUpdate >= 500) {
    lastUpdate = now;
    counter++;

    lcd.setCursor(7, 1);
    lcd.print(counter);
    lcd.print("   "); // clear leftover digits
  }

  // Update uptime every 1 second
  if (now - lastUptimeUpdate >= 1000) {
    lastUptimeUpdate = now;

    lcd.setCursor(0, 0);
    lcd.print("Uptime:");
    lcd.setCursor(8, 0);
    lcd.print(now / 1000);
    lcd.print("s   ");
  }
}
