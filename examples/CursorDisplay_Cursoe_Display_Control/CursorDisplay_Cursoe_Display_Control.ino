#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(16, 2);

void setup() {
  lcd.begin();
  lcd.backlight();

  lcd.print("Display Demo");
}

void loop() {
  lcd.noDisplay();
  delay(1000);

  lcd.display();
  delay(1000);
}
