#include "settings.h"
void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    //while(1); // Don't proceed, loop forever
  } 
  if(!rtc.begin()) {
    Serial.println("Couldn't find RTC!");
    Serial.flush();
    abort();
  }
  
  if(rtc.lostPower()) {
    // this will adjust to the date and time at compilation
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.disable32K();

  pinMode(clock_interrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(clock_interrupt), onAlarm, FALLING);

  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  rtc.writeSqwPinMode(DS3231_OFF);

  rtc.disableAlarm(2);

  dht.begin();

  interface = homeInter;
}

void loop() {
  now = rtc.now();
  interfaceSelector();

}
