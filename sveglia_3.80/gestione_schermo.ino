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

}
void mostra_orologio(){
  lcd.setCursor(4, 0);
  if ((dt.hour) < 10) {
    lcd.print(0);
  }
  lcd.print(dt.hour);
  lcd.print(":");
  if ((dt.minute) < 10) {
    lcd.print(0);
  }
  lcd.print(dt.minute);
  lcd.print(":");
  if ((dt.second) < 10) {
    lcd.print(0);
  }
  lcd.print(dt.second);
}
void mostra_data(){
  lcd.setCursor(4, 1);
  lcd.print(printday[day]);
  lcd.print(" ");
  if ((dt.day) < 10) {
    lcd.print(0);
  }
  lcd.print(dt.day);
}
void mostra_temperatura(){
  tempReading = analogRead(A7);
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