#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD to for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(16, 2);

void setup()
{
	// initialize the LCD
	lcd.autoBegin();
}

void loop()
{
	bool blinking = true;
	lcd.cursor();

	while (1) {
		if (blinking) {
			lcd.clear();
			lcd.print("No cursor blink");
			lcd.noBlink();
			blinking = false;
		} else {
			lcd.clear();
			lcd.print("Cursor blink");
			lcd.blink();
			blinking = true;
		}
		delay(4000);
	}
}
