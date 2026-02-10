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