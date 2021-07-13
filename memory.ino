byte defaultPar[]{0};
void setDefault(){
  int i;
  for(i = 0; i < EEPROM_used; i++){
    EEPROM.update(i, defaultPar[i]);
  }
}

void eepromPar(int address){
  int par = EEPROM.read(address);
  switch(address){
    
  }
}