void aggiornamentoPassivoLuce(){
  arrayLuce[puntoArrayLuce] = analogRead(A3);
  puntoArrayLuce = (puntoArrayLuce + 1) % 100;
}
