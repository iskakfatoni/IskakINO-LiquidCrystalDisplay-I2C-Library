# IskakINO_LiquidCrystal_I2C

[![Arduino Library](https://img.shields.io/badge/Arduino-Library-blue.svg)](https://www.arduino.cc/reference/en/libraries/)
[![Platform](https://img.shields.io/badge/platform-Arduino%20%7C%20ESP32-green)](#)
[![License](https://img.shields.io/badge/license-MIT-lightgrey)](LICENSE)
[![Version](https://img.shields.io/badge/version-1.0.0-orange)](#)

LiquidCrystal I2C library for **HD44780 LCD** using **PCF8574 I2C expander**  
with **automatic I2C address detection**.

Designed to be:

- ✅ Backward compatible with `LiquidCrystal_I2C`
- ⚡ Lightweight & optimized for flash/RAM
- 🔌 Arduino & ESP32 friendly
- 🧼 Clean API & maintainer-grade structure

---

## 📑 Table of Contents

- [Features](#-features)
- [Supported Hardware](#-supported-hardware)
- [Installation](#-installation)
- [Wiring](#-wiring)
- [Basic Usage](#-basic-usage)
- [Showcase Examples](#-showcase-examples)
- [API Compatibility](#-api-compatibility)
- [Versioning](#-versioning)
- [License](#-license)

---

## ✨ Features

- Automatic I2C address scanning (0x20–0x27)
- Full **HD44780 command support**
- Standard `LiquidCrystal` compatible API
- Custom character (CGRAM) support
- Scroll, autoscroll, cursor & blink control
- Non-blocking friendly (millis-based design)
- Optimized for ESP32 & Arduino boards

---

## 🧩 Supported Hardware

This library supports HD44780 LCDs with I2C backpack (PCF8574 / PCF8574A) and popular microcontrollers:

| Board / MCU | Notes |
|-------------|-------|
| Arduino UNO / Nano | 5V logic, SDA/A4, SCL/A5 |
| Arduino Mega | 5V logic, SDA/20, SCL/21 |
| ESP32 | 3.3V logic, SDA = GPIO21, SCL = GPIO22 |
| ESP32-C3 | 3.3V logic, SDA = GPIO20, SCL = GPIO21 |
| ESP8266 (NodeMCU / Wemos D1) | 3.3V logic, SDA = D2 (GPIO4), SCL = D1 (GPIO5) |

---

## 📦 Installation

### Arduino IDE (Library Manager)

1. Open **Arduino IDE**
2. Sketch → Include Library → **Manage Libraries**
3. Search for **IskakINO_LiquidCrystal_I2C**
4. Click **Install**

### Manual Installation (ZIP)

1. Download this repository as ZIP
2. Arduino IDE → Sketch → Include Library → **Add .ZIP Library**

---

## 🔌 Wiring

Connect your HD44780 LCD with I2C backpack to your board:

| LCD I2C Pin | Arduino | ESP32 | ESP32-C3 | ESP8266 |
|------------|----------|--------|-----------|----------|
| SDA | A4 | GPIO21 | GPIO20 | D2 (GPIO4) |
| SCL | A5 | GPIO22 | GPIO21 | D1 (GPIO5) |
| VCC | 5V | 3.3V | 3.3V | 3.3V |
| GND | GND | GND | GND | GND |

> ⚠ Ensure voltage compatibility between your LCD backpack and board.

---

## 🚀 Basic Usage

```cpp
#include <LiquidCrystal_I2C.h>

// Auto-detect I2C address
LiquidCrystal_I2C lcd(16, 2);

void setup() {
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hello IskakINO");
}

void loop() {
}
```

---

## 🎬 Showcase Examples

This library includes **15 example sketches** demonstrating various features:

1. **Basic** – Basic LCD initialization and text display  
2. **Backlight_On_Off_Demo** – Backlight ON/OFF control  
3. **CursorDisplay_Cursoe_Display_Control** – Cursor, blink & display control  
4. **Scroll_and_Autoscroll** – Text scrolling and autoscroll  
5. **Ticker_Text** – Non-blocking ticker / marquee text  
6. **Scroll_with_ProgressBar** – Scroll combined with progress bar  
7. **Advanced_CustomChar_ProgressBar** – Custom character progress bar  
8. **Multi_Line_Dashboard** – Multi-line layout example  
9. **Multi-Sensor_Dashboard** – Multi-sensor data display  
10. **Multi-Line_Dashboard_with_Scrolling_Ticker** – Dashboard + ticker  
11. **Advanced_Dashboard_Example** – Structured LCD dashboard  
12. **Advanced_NonBlocking_Dashboard** – Non-blocking update system  
13. **Advanced_Multi-Sensor_Dashboard_with_Alarm** – Dashboard with alarm logic  
14. **ESP32_Custom_I2C_Pins** – Custom I2C pins for ESP32  
15. **SetAddress_Manual_I2C_Address** – Manual I2C address configuration  

### 📂 Example Folder Structure

```
examples/
├── Advanced_CustomChar_ProgressBar/
│   └── Advanced_CustomChar_ProgressBar.ino
├── Advanced_Dashboard_Example/
│   └── Advanced_Dashboard_Example.ino
├── Advanced_Multi-Sensor_Dashboard_with_Alarm/
│   └── Advanced_Multi-Sensor_Dashboard_with_Alarm.ino
├── Advanced_NonBlocking_Dashboard/
│   └── Advanced_NonBlocking_Dashboard.ino
├── Backlight_On_Off_Demo/
│   └── Backlight_On_Off_Demo.ino
├── Basic/
│   └── Basic.ino
├── CursorDisplay_Cursoe_Display_Control/
│   └── CursorDisplay_Cursoe_Display_Control.ino
├── ESP32_Custom_I2C_Pins/
│   └── ESP32_Custom_I2C_Pins.ino
├── Multi-Line_Dashboard_with_Scrolling_Ticker/
│   └── Multi-Line_Dashboard_with_Scrolling_Ticker.ino
├── Multi-Sensor_Dashboard/
│   └── Multi-Sensor_Dashboard.ino
├── Multi_Line_Dashboard/
│   └── Multi_Line_Dashboard.ino
├── Scroll_and_Autoscroll/
│   └── Scroll_and_Autoscroll.ino
├── Scroll_with_ProgressBar/
│   └── Scroll_with_ProgressBar.ino
├── SetAddress_Manual_I2C_Address/
│   └── SetAddress_Manual_I2C_Address.ino
└── Ticker_Text/
    └── Ticker_Text.ino
```

Each example demonstrates different LCD capabilities including scrolling, autoscroll, custom characters, progress bars, dashboards, sensor integration, alarm logic, and non-blocking display updates.

---

## 🔁 API Compatibility

This library is designed to be **100% backward compatible** with common `LiquidCrystal_I2C` usage patterns.

### Standard Mode

```cpp
LiquidCrystal_I2C lcd(address, columns, rows);
```

### Auto-Detect Mode

```cpp
LiquidCrystal_I2C lcd(columns, rows);
```

Legacy API calls remain fully functional.

---

## 🏷 Versioning

This library follows **Semantic Versioning**:

```
MAJOR.MINOR.PATCH
```

### 📌 Current Version

&nbsp;&nbsp;&nbsp;&nbsp;**v1.0.0**

&nbsp;&nbsp;&nbsp;&nbsp;- Initial stable release  
&nbsp;&nbsp;&nbsp;&nbsp;- Backward compatible API  
&nbsp;&nbsp;&nbsp;&nbsp;- Automatic I2C address detection  
&nbsp;&nbsp;&nbsp;&nbsp;- Custom character support  
&nbsp;&nbsp;&nbsp;&nbsp;- Scroll, cursor & blink control  
&nbsp;&nbsp;&nbsp;&nbsp;- Advanced dashboard & progress bar examples  
&nbsp;&nbsp;&nbsp;&nbsp;- No breaking changes will be introduced within the 1.x series.

---

## 📜 License

This library is released under the **MIT License**.

You are free to:

- Use  
- Modify  
- Distribute  
- Include in commercial projects  

As long as the original copyright notice is retained.
