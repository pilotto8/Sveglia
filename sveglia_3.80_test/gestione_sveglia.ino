bool rilevato_allarme() {
  if (rtc.alarmFired(1) && svegliaAbilitata == 1) {
    return true;
  }
  return false;
}
void sveglia_triggherata() {
  accendi_schermo();
  // setluxeq();
  lcd.clear();
  mostra_data();
  for (i = 390; digitalRead(3) == LOW && i > 0; i--) {
    mostra_orologio();
    tone(4, melody[4], 80);
    // Delay(1);
    if (i % 3 == 0) {
      if (lum(true) == true) {
        rilevataInterazioneLuce = true;
        i = 0;
        // Darck();
        tone(4, melody[3], 20);
      }
    }
    statoInterazione = allarmeInCorso;
  }
}

void imposta_posticipo() {
  //post++;
  if (variabile[minutiSveglia] + 5 > 59){
    variabile[oraSveglia] = (variabile[oraSveglia] + 1) % 24;
  }
  variabile[minutiSveglia] = (variabile[minutiSveglia] + 5) % 60;
  //clock.armAlarm1(false);
  //clock.clearAlarm1();
  //clock.setAlarm1(0, variabile[oraSveglia], variabile[minutiSveglia], 0, DS3231_MATCH_H_M_S);
  //lcd.clear();
  // lam = 0;
  /*do {
    dt = clock.getDateTime();
    home(true);
    delay(100);
  }
  while (digitalRead(6) == LOW || digitalRead(3) == HIGH);*/
}
