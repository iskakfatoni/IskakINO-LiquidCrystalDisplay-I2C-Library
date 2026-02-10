# IskakINO_LiquidCrystal_I2C

LiquidCrystal I2C library for HD44780 LCD with **automatic I2C address detection**.  
Designed to be **backward compatible**, lightweight, and friendly for Arduino & ESP32 projects.

---

## ✨ Features
- Automatic I2C address scanning (PCF8574)
- Backward compatible with `LiquidCrystal_I2C`
- Optional splash screen
- Compile-time configuration
- Arduino & ESP32 compatible
- Lightweight and optimized for flash & RAM

---

## 📦 Installation
**Arduino IDE**
1. Download this repository as ZIP
2. Open Arduino IDE
3. Sketch → Include Library → Add .ZIP Library

---

## 🚀 Basic Usage
```cpp
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(16, 2);

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Hello IskakINO");
}

void loop() {
}
```

---

## More Examples
This library includes several ready-to-use examples to help you get started quickly:
- **Basic**
  - Initialize the LCD and display static text.
- **SetAddress**
  - Manually set the I2C address (useful if you already know the LCD address).
- **Backlight**
  - Turn LCD backlight ON and OFF.
- **CursorDisplay**
  - Control LCD visibility using `display()` and `noDisplay()`.
- **ESP32_I2C_CustomPins**
  - Use custom SDA and SCL pins on ESP32 by initializing `Wire` manually.

You can access these examples from Arduino IDE:

## 📚 More Examples

- **Advanced_NonBlocking_Dashboard**  
  Demonstrates non-blocking LCD updates using `millis()`,  
  partial screen refresh, and real-world dashboard layout.

