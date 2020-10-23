void sveglia_triggherata(){
  if (clock.isAlarm1() && svegliaAbilitata == 1) {
    accendiSchermo();
    //setluxeq();
    lcd.clear();
    mostra_data();
    for (i = 390; digitalRead(3) == LOW && i > 0; i--) {
      dt = clock.getDateTime();
      mostra_orologio();
      tone(4, melody[4], 80);
      //Delay(1);
      if (i % 3 == 0) {
        if (lum(true) == true) {
          rilevataInterazioneLuce = true;
          i = 0;
          //Darck();
          tone(4, melody[3], 20);
        }
      }
      allarmeInCorso = true;
    }
  }
}