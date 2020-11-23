#include "setup_variabili.h"
void setup() {
  pinMode(ball_switch, INPUT_PULLUP);
  pinMode(pulsante, INPUT);
  pinMode(joystick, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  //inputString.reserve(20);
  lcd.begin(16, 2);
  lcd.createChar(1, campanella);
  lcd.createChar(2, unavolta);
  lcd.createChar(3, ripeti);
  lcd.createChar(4, calend);
  lcd.createChar(5, cerchio);
  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("Errore: RTC non\n        presente");
    abort();
  }
  if (rtc.lostPower()) {
    sveglia_triggherata();
  }
  rtc.disable32K();
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);
  rtc.writeSqwPinMode(DS3231_OFF);
  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  ////////////rtc.setAlarm1();
}
void loop() {
  DateTime now = rtc.now();
  if (soft_interrupt() == true) {

  }
}
