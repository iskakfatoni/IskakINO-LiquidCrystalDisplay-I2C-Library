/*
  SetAddress.ino - Manual I2C address example

  Demonstrates how to manually set the I2C address
  instead of using automatic address scanning.

  Useful when the LCD I2C address is already known
  (commonly 0x27 or 0x3F).

  Library  : IskakINO_LiquidCrystal_I2C
  Version  : 1.0.0
  Author   : Iskak Fatoni
  License  : MIT
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(16, 2);

void setup() {
  lcd.setAddress(0x27);  // Disable auto scan
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Manual Address");

  lcd.setCursor(0, 1);
  lcd.print("I2C: 0x27");
}

void loop() {
}
