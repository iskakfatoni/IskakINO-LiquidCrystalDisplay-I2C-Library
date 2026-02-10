#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C::LiquidCrystal_I2C(uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize) {
    _addr = 0x00;
    _cols = lcd_cols;
    _rows = lcd_rows;
    _charsize = charsize;
    _backlightval = LCD_BACKLIGHT;
}

// ===== INTERNAL =====
void LiquidCrystal_I2C::_scanAddress() {
#if LCD_ENABLE_AUTO_SCAN
    Wire.begin();
    for (uint8_t address = LCD_SCAN_START; address <= LCD_SCAN_END; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            _addr = address;
#if LCD_ENABLE_SERIAL_DEBUG
            Serial.print("LCD I2C ditemukan di 0x");
            Serial.println(address, HEX);
#endif
            return;
        }
    }
#if LCD_ENABLE_SERIAL_DEBUG
    Serial.println("LCD I2C tidak ditemukan!");
#endif
#endif
}

void LiquidCrystal_I2C::_lcdInit(uint16_t splashDelay) {
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
    if (_rows > 1) _displayfunction |= LCD_2LINE;
    if ((_charsize != 0) && (_rows == 1)) _displayfunction |= LCD_5x10DOTS;

    delay(50);
    expanderWrite(_backlightval);
    delay(1000);

    write4bits(0x03 << 4); delayMicroseconds(4500);
    write4bits(0x03 << 4); delayMicroseconds(4500);
    write4bits(0x03 << 4); delayMicroseconds(150);
    write4bits(0x02 << 4);

    command(LCD_FUNCTIONSET | _displayfunction);

    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    display();
    clear();

    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    command(LCD_ENTRYMODESET | _displaymode);

#if LCD_ENABLE_SPLASH
    home();
    print(LCD_SPLASH_LINE1);
    setCursor(0, 1);
    print("LCD: 0x");
    print(_addr, HEX);
    delay(splashDelay);
    clear();
#endif
    home();
}

// ===== PUBLIC API =====
void LiquidCrystal_I2C::begin()      { _scanAddress(); _lcdInit(1500); }
void LiquidCrystal_I2C::init()       { _scanAddress(); _lcdInit(1500); }
void LiquidCrystal_I2C::autoBegin()  { _scanAddress(); _lcdInit(2500); }
void LiquidCrystal_I2C::autoAddress(){ _scanAddress(); }

void LiquidCrystal_I2C::clear() {
    command(LCD_CLEARDISPLAY);
    delayMicroseconds(2000);
}

void LiquidCrystal_I2C::home() {
    command(LCD_RETURNHOME);
    delayMicroseconds(2000);
}

void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row) {
    static const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row >= _rows) row = _rows - 1;
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LiquidCrystal_I2C::noDisplay() {
    _displaycontrol &= ~LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::display() {
    _displaycontrol |= LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::noCursor() {
    _displaycontrol &= ~LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::cursor() {
    _displaycontrol |= LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::noBlink() {
    _displaycontrol &= ~LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::blink() {
    _displaycontrol |= LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::scrollDisplayLeft() {
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LiquidCrystal_I2C::scrollDisplayRight() {
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LiquidCrystal_I2C::leftToRight() {
    _displaymode |= LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displaymode);
}

void LiquidCrystal_I2C::rightToLeft() {
    _displaymode &= ~LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displaymode);
}

void LiquidCrystal_I2C::autoscroll() {
    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | _displaymode);
}

void LiquidCrystal_I2C::noAutoscroll() {
    _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | _displaymode);
}

void LiquidCrystal_I2C::createChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x7;
    command(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++) write(charmap[i]);
}

void LiquidCrystal_I2C::noBacklight() {
    _backlightval = LCD_NOBACKLIGHT;
    expanderWrite(0);
}

void LiquidCrystal_I2C::backlight() {
    _backlightval = LCD_BACKLIGHT;
    expanderWrite(0);
}

void LiquidCrystal_I2C::setBacklight(uint8_t val) {
    val ? backlight() : noBacklight();
}

inline void LiquidCrystal_I2C::command(uint8_t value) {
    send(value, 0);
}

size_t LiquidCrystal_I2C::write(uint8_t value) {
    send(value, Rs);
    return 1;
}

void LiquidCrystal_I2C::send(uint8_t value, uint8_t mode) {
    uint8_t high = value & 0xF0;
    uint8_t low  = (value << 4) & 0xF0;
    write4bits(high | mode);
    write4bits(low  | mode);
}

void LiquidCrystal_I2C::write4bits(uint8_t value) {
    expanderWrite(value);
    pulseEnable(value);
}

void LiquidCrystal_I2C::expanderWrite(uint8_t data) {
    Wire.beginTransmission(_addr);
    Wire.write(data | _backlightval);
    Wire.endTransmission();
}

void LiquidCrystal_I2C::pulseEnable(uint8_t data) {
    expanderWrite(data | En);
    delayMicroseconds(1);
    expanderWrite(data & ~En);
    delayMicroseconds(50);
}
