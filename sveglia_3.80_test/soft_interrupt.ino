bool soft_interrupt{
  if (rilevato_allarme() == true;){
    return true;
  }
  return false;
}