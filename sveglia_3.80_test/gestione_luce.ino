void rilevamentoLuce() {
  puntoArrayLucePrecedente = puntoArrayLuce;
  puntoArrayLuce = (puntoArrayLuce + 1) % 100;
  arrayLuce[puntoArrayLuce] = analogRead(A3);
  if (arrayLuce[puntoArrayLuce] - arrayLuce[puntoArrayLuce]){
    
  }
  if (arrayLuce[puntoArrayLuce] < livelloLuceConsolidato - 30% * livelloLuceConsolidato - 1 || arrayLuce[puntoArrayLuce] > livelloLuceConsolidato + 30% * livelloLuceConsolidato + 1) {

  }
}
