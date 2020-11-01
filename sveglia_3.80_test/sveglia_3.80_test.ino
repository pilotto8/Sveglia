#include <pitches.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 rtc;
#include <EEPROM.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#include <Adafruit_SleepyDog.h>
#define SW_pin 5
#define X_pin A1
#define Y_pin A0
const int melody[] = {
  NOTE_C5,
  NOTE_D5,
  NOTE_E5,
  NOTE_F5,
  NOTE_G5,
  NOTE_A5,
  NOTE_B5,
  NOTE_C6
};
const byte campanella[] = {
  B00000,
  B00100,
  B01010,
  B01010,
  B10001,
  B11111,
  B00100,
  B00000
};
const byte ripeti[] = {
  B01110,
  B10001,
  B10001,
  B10101,
  B10011,
  B10001,
  B10000,
  B01110
};
const byte unavolta[] = {
  B00000,
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000
};
const byte switch_[] = {
  B00000,
  B00100,
  B01000,
  B11111,
  B00000,
  B11111,
  B00010,
  B00100
};
const byte calend[] = {
  B11011,
  B10001,
  B01110,
  B01010,
  B01110,
  B01000,
  B10001,
  B11011
};
const byte cerchio[] = {
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};


void setup() {
  pinMode(6, INPUT_PULLUP);
  pinMode(3, INPUT);
  pinMode(SW_pin, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  inputString.reserve(20);
  lcd.begin(16, 2);
  lcd.createChar(1, campanella);
  lcd.createChar(2, unavolta);
  lcd.createChar(3, ripeti);
  lcd.createChar(4, calend);
  lcd.createChar(5, cerchio);
  if(rtc.lostPower()) {

  }
}
void loop(){
  DateTime now = rtc.now();
  if (millis() - millisDiPrima >= ritardoEsecuzione || soft_interrupt() == true){
    millisDiPrima = millis();

  }
}
