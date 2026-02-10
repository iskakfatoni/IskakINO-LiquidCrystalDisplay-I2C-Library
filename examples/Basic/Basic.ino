/*
  Basic.ino - Basic LCD I2C example

  Demonstrates basic usage of IskakINO_LiquidCrystal_I2C library.
  This example initializes the LCD, turns on the backlight,
  and displays static text.

  Compatible with Arduino, ESP8266, ESP32.

  Library  : IskakINO_LiquidCrystal_I2C
  Version  : 1.0.0
  Author   : Iskak Fatoni
  License  : MIT
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
