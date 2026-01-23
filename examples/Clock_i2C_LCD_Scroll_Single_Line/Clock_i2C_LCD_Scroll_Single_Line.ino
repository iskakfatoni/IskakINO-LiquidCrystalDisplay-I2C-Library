//#include <ESP8266WiFi.h>
//#include <Wire.h>  // needed if you use esp8266

#include <LiquidCrystal_I2C.h>  //i2C LCD Library

//Define your LCD 16x2 or 20x4
LiquidCrystal_I2C lcd(20, 4);

uint32_t targetTime = 0;
uint8_t conv2d(const char* p) {
uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
   v = *p - '0';
  return 10 * v + *++p - '0';
}

//Mengambil waktu jam dari waktu Compile/Upload di system Windows
uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3), ss = conv2d(__TIME__ + 6); // mengambil data waktu dari jam Compile-Upload
uint8_t dd = conv2d(__DATE__ + 4), bb = conv2d(__DATE__), y1 = conv2d(__DATE__ + 7), y2 = conv2d(__DATE__ + 9);;  // mengambil data waktu dari jam Compile-Upload
String bl="   ";
uint8_t dtk=0, mnt = 0;

void setup()
{
 //Aktifkan serial jika ingin melihat notifikasi di Serial monitor
 //Serial.begin (9600);  

 //memulai lcd
 lcd.autoBegin();

}

void loop() {
  // put your main code here, to run repeatedly:  

  updateClock();
  
  int i=0;
  while (i<10){
  i++;
  lcd.clear();
  lcd.setCursor(4,0);
  if(hh<10){lcd.print("0");}
  lcd.print(hh); lcd.print(":");
  if(mm<10){lcd.print("0");}
  lcd.print(mm); lcd.print(":");
  if(ss<10){lcd.print("0");}
  lcd.print(ss);
  lcd.setCursor(i-1,1);
  lcd.print(dd);
  lcd.print(" ");
  lcd.print(bl);
  lcd.print(" ");
  lcd.print(y1);
  lcd.print(y2);
  delay(100);}
  
  updateClock();
  
  while (i>0){
  i--;
  lcd.clear();
  lcd.setCursor(4,0);
  if(hh<10){lcd.print("0");}
  lcd.print(hh); lcd.print(":");
  if(mm<10){lcd.print("0");}
  lcd.print(mm); lcd.print(":");
  if(ss<10){lcd.print("0");}
  lcd.print(ss);
  lcd.setCursor(i+1,1);
  lcd.print(dd);
  lcd.print(" ");
  lcd.print(bl);
  lcd.print(" ");
  lcd.print(y1);
  lcd.print(y2);
  delay(100);}
}

void updateClock() {
  switch (__DATE__[0]) {
case 'J': bb = __DATE__[1] == 'a' ? 1 : bb = __DATE__[2] == 'n' ? 6 : 7; break;
case 'F': bb = 2; break;
case 'A': bb = __DATE__[2] == 'r' ? 4 : 8; break;
case 'M': bb = __DATE__[2] == 'r' ? 3 : 5; break;
case 'S': bb = 9; break;
case 'O': bb = 10; break;
case 'N': bb = 11; break;
case 'D': bb = 12; break;}
switch (bb) {
case 1: bl = "Jan"; break;
case 2: bl = "Feb"; break;
case 3: bl = "Mar"; break;
case 4: bl = "Apr"; break;
case 5: bl = "Mei"; break;
case 6: bl = "Jun"; break;
case 7: bl = "Jul"; break;
case 8: bl = "Aug"; break;
case 9: bl = "Sep"; break;
case 10: bl = "Okt"; break;
case 11: bl = "Nov"; break;
case 12: bl = "Des"; break;

}
  // put your main code here, to run repeatedly:
  if (targetTime < millis()) {
    targetTime = millis() + 1000;
    dtk++;
    if (dtk == 60) {
      dtk = 0;
      mnt++;  } 
    ss++;              // Advance second
    if (ss == 60) {
      ss = 0;
      mm++;            // Advance minute
      if (mm > 59) {
        mm = 0;
        hh++;          // Advance hour
        if (hh > 23) {
          hh = 0;
        }
      }
    }
  }
  
}

