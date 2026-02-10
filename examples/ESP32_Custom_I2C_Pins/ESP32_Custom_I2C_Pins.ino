#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
  ESP32 Custom I2C Pins Example
  SDA = GPIO 4
  SCL = GPIO 5
*/

LiquidCrystal_I2C lcd(16, 2);

void setup() {
  Wire.begin(4, 5);  // Custom I2C pins
  lcd.begin();
  lcd.backlight();

  lcd.print("ESP32 I2C OK");
}

void loop() {
}
