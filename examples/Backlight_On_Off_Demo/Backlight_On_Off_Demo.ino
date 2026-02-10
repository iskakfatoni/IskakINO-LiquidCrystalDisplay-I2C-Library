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
