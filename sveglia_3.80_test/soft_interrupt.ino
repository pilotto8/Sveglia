bool soft_interrupt(){
  if (rilevato_allarme() == true){
    return true;
  }
  if (digitalRead(pulsante) != inputPulsante){
    inputPulsante = digitalRead(pulsante);
    millisPulsante = millis();
    return true;
  }
  if (digitalRead(ball_switch) != inputBallSwitch){
    inputBallSwitch = digitalRead(ball_switch);
    millisBallSwitch = millis();
    return true;
  }
  return false;
}
void ritardo(int ritardoEsecuzione){
  millisRitardo = millis();
  while(millis() - millisRitardo < ritardoesecuzione && soft_interrupt() == false){}
}
