/*
  ESP32_I2C_CustomPins.ino - ESP32 custom I2C pins example

  Demonstrates how to use custom SDA and SCL pins
  on ESP32 by initializing Wire manually.

  Default example:
    SDA = GPIO 4
    SCL = GPIO 5

  Library  : IskakINO_LiquidCrystal_I2C
  Version  : 1.0.0
  Author   : Iskak Fatoni
  License  : MIT
*/

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
