int variabile[50];
enum variabili{
  numeroSveglia,
  oraSveglia,
  minutiSveglia,
  modalità,
  durataSchermoAcceso,
  durataStandBy,
  limiteRichiesteLuce
}
int i, r, c;
bool svegliaAbilitata = true;
int schermoAcceso = 50;
int standBy = 10;
bool allarmeInCorso = false;
bool rilevataInterazioneLuce = false;
int ritardoEsecuzione = 100;
bool interrupt = false;