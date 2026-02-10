#ifndef LIQUIDCRYSTAL_I2C_H
#define LIQUIDCRYSTAL_I2C_H

#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>

// ================= CONFIG =================
#ifndef LCD_ENABLE_AUTO_SCAN
#define LCD_ENABLE_AUTO_SCAN     1
#endif

#ifndef LCD_ENABLE_SERIAL_DEBUG
#define LCD_ENABLE_SERIAL_DEBUG  1
#endif

#ifndef LCD_ENABLE_SPLASH
#define LCD_ENABLE_SPLASH        1
#endif

#ifndef LCD_SCAN_START
#define LCD_SCAN_START           0x20
#endif

#ifndef LCD_SCAN_END
#define LCD_SCAN_END             0x3F
#endif

#ifndef LCD_SPLASH_LINE1
#define LCD_SPLASH_LINE1         "@iskakfatoni"
#endif
// =========================================

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME   0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT  0x10
#define LCD_FUNCTIONSET  0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT  0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON  0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON   0x02
#define LCD_CURSOROFF  0x00
#define LCD_BLINKON    0x01
#define LCD_BLINKOFF   0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE  0x00
#define LCD_MOVERIGHT   0x04
#define LCD_MOVELEFT    0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE    0x08
#define LCD_1LINE    0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS  0x00

// backlight
#define LCD_BACKLIGHT   0x08
#define LCD_NOBACKLIGHT 0x00

// control bits
#define En 0b00000100
#define Rw 0b00000010
#define Rs 0b00000001

class LiquidCrystal_I2C : public Print {
public:
    LiquidCrystal_I2C(uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS);

    void begin();
    void init();
    void autoBegin();
    void autoAddress();

    void clear();
    void home();
    void setCursor(uint8_t, uint8_t);

    void noDisplay();
    void display();
    void noCursor();
    void cursor();
    void noBlink();
    void blink();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void leftToRight();
    void rightToLeft();
    void autoscroll();
    void noAutoscroll();

    void createChar(uint8_t, uint8_t[]);
    void noBacklight();
    void backlight();
    void setBacklight(uint8_t);

    virtual size_t write(uint8_t);

private:
    void command(uint8_t);
    void send(uint8_t, uint8_t);
    void write4bits(uint8_t);
    void expanderWrite(uint8_t);
    void pulseEnable(uint8_t);

    void _scanAddress();
    void _lcdInit(uint16_t splashDelay);

    uint8_t _addr;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _charsize;
    uint8_t _backlightval;
    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;
};

#endif
