void onAlarm() {
    rtc.clearAlarm(1);
    Serial.println("Alarm occured!");
}