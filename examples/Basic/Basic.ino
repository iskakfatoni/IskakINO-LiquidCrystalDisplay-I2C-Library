/*
  =========================================================
  Basic Example
  IskakINO_LiquidCrystal_I2C v1.0.0
  =========================================================

  LCD Type  : HD44780 + I2C Backpack (PCF8574)
  LCD Size  : 16x2 (adjustable)

  ---------------------------------------------------------
  WIRING
  ---------------------------------------------------------
  LCD I2C      Arduino UNO / NANO      ESP32
  ---------------------------------------------------------
  GND     -->  GND                     GND
  VCC     -->  5V                      5V / 3V3*
  SDA     -->  A4                      GPIO 21
  SCL     -->  A5                      GPIO 22

  * Use 5V if your I2C module supports it.
    Most PCF8574 boards work on 3.3V logic (ESP32 safe).

  ---------------------------------------------------------
  FEATURES
  ---------------------------------------------------------
  - Auto I2C address scan (0x20 – 0x27)
  - No manual address needed
  - Compatible with Arduino & ESP32
  - Lightweight & low RAM usage
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_COLS, LCD_ROWS);

void setup() {
  // Optional serial debug
  // Serial.begin(115200);
  // #define LCD_ENABLE_SERIAL_DEBUG 1

  lcd.begin();       // Initialize LCD + auto scan
  lcd.backlight();   // Turn backlight ON

  lcd.setCursor(0, 0);
  lcd.print("IskakINO LCD");

  lcd.setCursor(0, 1);
  lcd.print("I2C Ready!");
}

void loop() {
  // Simple activity indicator
  static bool blink = true;

  lcd.setCursor(15, 1);
  lcd.print(blink ? "*" : " ");
  blink = !blink;

  delay(500);
}
