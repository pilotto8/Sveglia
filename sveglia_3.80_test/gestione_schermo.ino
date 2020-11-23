void accendi_schermo() {
  schermoAcceso = durataSchermoAcceso;
  standBy = durataStandBy;
  ritardoEsecuzione = 100;
  /*if (adstdby > 0) {
    calstdby = 0;
  }*/
  digitalWrite(2, HIGH);
}
void spegni_schermo(){
 digitalWrite(2, LOW);
  /*py = 0;
  inv = false;
  Inv = 0;
  reloadinf = true;*/
}
void mostra_orologio(){
  lcd.setCursor(4, 0);
  lcd.print(now.toString("hh:mm:ss"));
}
void mostra_data(){
  lcd.setCursor(4, 1);
  //lcd.print(printday[day]);
  lcd.print(" ");
  lcd.print(now.toString("YYYY"));
}
void mostra_temperatura(){
  int tempReading = analogRead(A7);
  double tempC = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempC = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempC * tempC)) * tempC) - 273.15 + 1.5;
  /*float restemp = tempC - (int)tempC;
  tempC -= restemp;
  if (restemp >= 0.5) {
    tempC++;
  } */
  lcd.setCursor(12, 1);
  if (tempC < 10) {
    lcd.print(0);
  }
  lcd.print(tempC);
  //lcd.write(5);
}
