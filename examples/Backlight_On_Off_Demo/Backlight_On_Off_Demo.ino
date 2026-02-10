/*
  Backlight.ino - Backlight control example

  Demonstrates how to turn the LCD backlight ON and OFF
  using backlight() and noBacklight() functions.

  Library  : IskakINO_LiquidCrystal_I2C
  Version  : 1.0.0
  Author   : Iskak Fatoni
  License  : MIT
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(16, 2);

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.print("Backlight ON");
}

void loop() {
  delay(2000);
  lcd.noBacklight();

  delay(2000);
  lcd.backlight();
}
