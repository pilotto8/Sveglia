unsigned long int millisDiPrima = 0;

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
bool rilevataInterazioneLuce = false;
int ritardoEsecuzione = 100;
//int lampeggio;


enum stati{
  attivo,
  riposo,
  aggiorna,
  allarmeInCorso
}
int statoInterazione = attvio;