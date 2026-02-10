#include "LiquidCrystal_I2C.h"
#include <Arduino.h>
#include <Wire.h>

/* =========================================================
   Constructor
   ========================================================= */
LiquidCrystal_I2C::LiquidCrystal_I2C(uint8_t cols, uint8_t rows)
    : _cols(cols),
      _rows(rows),
      _addr(0x00),
      _backlight(true),
      _displayfunction(LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS),
      _displaycontrol(0),
      _displaymode(0)
{
}

/* =========================================================
   Public API
   ========================================================= */
void LiquidCrystal_I2C::setAddress(uint8_t addr) {
    _addr = addr;
#if LCD_ENABLE_SERIAL_DEBUG
    Serial.print(F("[LCD] Manual I2C address set: 0x"));
    Serial.println(_addr, HEX);
#endif
}

uint8_t LiquidCrystal_I2C::getAddress() {
    return _addr;
}

void LiquidCrystal_I2C::begin() {
    Wire.begin();

    _scanAddress();

    if (_rows > 1) {
        _displayfunction |= LCD_2LINE;
    }

    delay(50);

    _write4bits(0x03 << 4);
    delayMicroseconds(4500);
    _write4bits(0x03 << 4);
    delayMicroseconds(4500);
    _write4bits(0x03 << 4);
    delayMicroseconds(150);
    _write4bits(0x02 << 4);

    _command(LCD_FUNCTIONSET | _displayfunction);

    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    display();

    clear();

    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    _command(LCD_ENTRYMODESET | _displaymode);

    home();
}

void LiquidCrystal_I2C::clear() {
    _command(LCD_CLEARDISPLAY);
    delayMicroseconds(2000);
}

void LiquidCrystal_I2C::home() {
    _command(LCD_RETURNHOME);
    delayMicroseconds(2000);
}

void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row) {
    static const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row >= _rows) row = _rows - 1;
    _command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LiquidCrystal_I2C::noDisplay() {
    _displaycontrol &= ~LCD_DISPLAYON;
    _command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::display() {
    _displaycontrol |= LCD_DISPLAYON;
    _command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::noBacklight() {
    _backlight = false;
    _expanderWrite(0);
}

void LiquidCrystal_I2C::backlight() {
    _backlight = true;
    _expanderWrite(0);
}

size_t LiquidCrystal_I2C::write(uint8_t value) {
    _send(value, Rs);
    return 1;
}

/* =========================================================
   Low-level command handling
   ========================================================= */
void LiquidCrystal_I2C::_command(uint8_t value) {
    _send(value, 0);
}

void LiquidCrystal_I2C::_send(uint8_t value, uint8_t mode) {
    uint8_t highnib = value & 0xF0;
    uint8_t lownib  = (value << 4) & 0xF0;

    _write4bits(highnib | mode);
    _write4bits(lownib | mode);
}

void LiquidCrystal_I2C::_write4bits(uint8_t value) {
    _expanderWrite(value);
    _pulseEnable(value);
}

void LiquidCrystal_I2C::_pulseEnable(uint8_t data) {
    _expanderWrite(data | En);
    delayMicroseconds(1);

    _expanderWrite(data & ~En);
    delayMicroseconds(50);
}

void LiquidCrystal_I2C::_expanderWrite(uint8_t data) {
    Wire.beginTransmission(_addr);
    Wire.write(data | (_backlight ? LCD_BACKLIGHT : LCD_NOBACKLIGHT));
    Wire.endTransmission();
}

/* =========================================================
   I2C Address Auto Scan
   ========================================================= */
void LiquidCrystal_I2C::_scanAddress() {
    if (_addr != 0x00) return; // manual override

    for (uint8_t addr = 0x20; addr <= 0x27; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            _addr = addr;
#if LCD_ENABLE_SERIAL_DEBUG
            Serial.print(F("[LCD] I2C found at 0x"));
            Serial.println(_addr, HEX);
#endif
            return;
        }
    }

#if LCD_ENABLE_SERIAL_DEBUG
    Serial.println(F("[LCD] I2C device NOT found"));
#endif
}
