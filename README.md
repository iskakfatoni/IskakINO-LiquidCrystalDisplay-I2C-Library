# IskakINO_LiquidCrystal_I2C

[![Arduino Library](https://img.shields.io/badge/Arduino-Library-blue.svg)](https://www.arduino.cc/reference/en/libraries/)
[![Platform](https://img.shields.io/badge/platform-Arduino%20%7C%20ESP32-green)](#)
[![License](https://img.shields.io/badge/license-MIT-lightgrey)](LICENSE)
[![Version](https://img.shields.io/badge/version-1.0.1-orange)](#)

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
- Non-blocking friendly (millis-based)
- Optimized for ESP32 & Arduino boards

---

## 🧩 Supported Hardware
- HD44780 compatible LCD (16x2, 20x4)
- I2C backpack using **PCF8574 / PCF8574A**
- Arduino UNO / Nano / Mega
- ESP32 / ESP8266

---

## 📦 Installation

### Arduino IDE
1. Open **Arduino IDE**
2. Sketch → Include Library → **Manage Libraries**
3. Search for **IskakINO_LiquidCrystal_I2C**
4. Click **Install**

### Manual (ZIP)
1. Download this repository as ZIP
2. Arduino IDE → Sketch → Include Library → Add `.ZIP Library`

---

## 🔌 Wiring

Connect your HD44780 LCD with I2C backpack (PCF8574 / PCF8574A) to your board as follows:

| LCD I2C Pin | Arduino / ESP32 | ESP32-C3 | NodeMCU (ESP8266) | Wemos D1 |
|------------|----------------|-----------|------------------|----------|
| SDA        | SDA             | GPIO20    | D2 (GPIO4)       | D2 (GPIO4) |
| SCL        | SCL             | GPIO21    | D1 (GPIO5)       | D1 (GPIO5) |
| VCC        | 5V (or 3.3V)   | 3.3V      | 3.3V             | 3.3V      |
| GND        | GND             | GND       | GND              | GND       |

> **Notes:**  
> - Arduino default: SDA/A4, SCL/A5 (Mega varies)  
> - ESP32 default: SDA = GPIO21, SCL = GPIO22 (can be changed using `Wire.begin(SDA, SCL);`)  
> - ESP32-C3 default: SDA = GPIO20, SCL = GPIO21 (can be changed in `Wire.begin()`)  
> - NodeMCU default: SDA = D2 (GPIO4), SCL = D1 (GPIO5)  
> - Wemos D1 default: SDA = D2 (GPIO4), SCL = D1 (GPIO5)  
> - Make sure VCC voltage matches your LCD and I2C backpack (3.3V for ESP32 / ESP32-C3 / NodeMCU / Wemos D1, 5V for Arduino)  

---

## 🚀 Basic Usage

```cpp
#include <LiquidCrystal_I2C.h>

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

## 🎬 Showcase Examples

This library provides examples **from basic to advanced**,  
designed to demonstrate **proper, efficient, and non-blocking usage of LCDs**.

### 📌 Basic
- **Basic**  
  Displays simple text on the LCD and ensures wiring and I2C address detection.

### ⚙️ Intermediate
- **Scroll_and_Autoscroll**  
  Demonstrates:
  - `scrollDisplayLeft()`  
  - `scrollDisplayRight()`  
  - `autoscroll()`  
  - `leftToRight()` / `rightToLeft()`

- **Ticker_Text**  
  Smooth running text (ticker) using `millis()`  
  without `delay()` and without `lcd.clear()`.

### 🚀 Advanced
- **Advanced_CustomChar_ProgressBar**  
  Uses **custom characters (CGRAM)** to create a smooth progress bar without flickering.

- **Scroll_with_ProgressBar**  
  Combines:
  - scrolling text  
  - progress bar  
  - non-blocking updates  
  Ideal for ESP32 IoT dashboards.

### 📂 Example Folder Structure
examples/
```├── Basic/
```├── Scroll_and_Autoscroll/
```├── Ticker_Text/
```├── Advanced_CustomChar_ProgressBar/
```└── Scroll_with_ProgressBar/

```
## 🔁 API Compatibility

This library is designed to be **100% backward compatible** with popular APIs:

LiquidCrystal_I2C lcd(address, columns, rows);

Or using auto-detect mode:

LiquidCrystal_I2C lcd(columns, rows);

## 🧩 Supported Hardware

This library supports HD44780 LCDs with I2C backpack (PCF8574 / PCF8574A) and popular microcontrollers:

| Board / MCU | Notes |
|------------|-------|
| Arduino UNO / Nano / Mega | Standard 5V logic, default I2C pins: SDA/A4, SCL/A5 (Mega varies) |
| ESP32 / ESP32 DevKit | 3.3V logic, default I2C pins: SDA = GPIO21, SCL = GPIO22 |
| ESP32-C3 | 3.3V logic, default I2C pins: SDA = GPIO20, SCL = GPIO21 |
| NodeMCU (ESP8266) | 3.3V logic, default I2C pins: SDA = D2 (GPIO4), SCL = D1 (GPIO5) |

---

## 📦 Installation

### Arduino IDE Library Manager
1. Open **Arduino IDE**  
2. Sketch → Include Library → **Manage Libraries**  
3. Search for **IskakINO_LiquidCrystal_I2C**  
4. Click **Install**

### Manual Installation (ZIP)
1. Download this repository as ZIP  
2. Arduino IDE → Sketch → Include Library → **Add .ZIP Library**

---

## 🔌 Wiring

Connect your HD44780 LCD with I2C backpack to your board as follows:

| LCD I2C Pin | Arduino / ESP32 | ESP32-C3 | NodeMCU (ESP8266) |
|------------|----------------|-----------|------------------|
| SDA        | SDA             | GPIO20    | D2 (GPIO4)       |
| SCL        | SCL             | GPIO21    | D1 (GPIO5)       |
| VCC        | 5V (or 3.3V)   | 3.3V      | 3.3V             |
| GND        | GND             | GND       | GND              |

> **Notes:**  
> - Arduino default: SDA/A4, SCL/A5 (Mega varies)  
> - ESP32 default: SDA = GPIO21, SCL = GPIO22 (can be changed using `Wire.begin(SDA, SCL);`)  
> - ESP32-C3 default: SDA = GPIO20, SCL = GPIO21 (can be changed using `Wire.begin()`)  
> - NodeMCU default: SDA = D2 (GPIO4), SCL = D1 (GPIO5)  
> - Make sure VCC voltage matches your LCD and I2C backpack (3.3V for ESP32 / ESP32-C3 / NodeMCU, 5V for Arduino)  

⚠️ **Note:**  
Legacy API calls remain fully functional.


## 🏷 Versioning
This library uses **Semantic Versioning**:
MAJOR.MINOR.PATCH
### 📌 Current Version
- **v1.0.0**
  - Initial stable release  
  - Backward compatible API  
  - Auto I2C address detection  
  - Custom character support  
  - Scroll, cursor, blink, progress bar examples

Breaking changes will **not be introduced** in the 1.x series.


## 📜 License

This library is released under the **MIT License**.

You are free to:  
- use  
- modify  
- distribute  
- include in commercial projects  

As long as the original copyright notice is retained.
