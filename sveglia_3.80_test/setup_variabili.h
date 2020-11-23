#include <pitches.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>
RTC_DS3231 rtc;
#include <EEPROM.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#include <Adafruit_SleepyDog.h>
#define joystick 5
#define X A1
#define Y A0
#define pulsante 3
#define ball_switch 6
#define fotores A3

const int melody[] = {
  NOTE_C5,
  NOTE_D5,
  NOTE_E5,
  NOTE_F5,
  NOTE_G5,
  NOTE_A5,
  NOTE_B5,
  NOTE_C6
};
const byte campanella[] = {
  B00000,
  B00100,
  B01010,
  B01010,
  B10001,
  B11111,
  B00100,
  B00000
};
const byte ripeti[] = {
  B01110,
  B10001,
  B10001,
  B10101,
  B10011,
  B10001,
  B10000,
  B01110
};
const byte unavolta[] = {
  B00000,
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000
};
const byte switch_[] = {
  B00000,
  B00100,
  B01000,
  B11111,
  B00000,
  B11111,
  B00010,
  B00100
};
const byte calend[] = {
  B11011,
  B10001,
  B01110,
  B01010,
  B01110,
  B01000,
  B10001,
  B11011
};
const byte cerchio[] = {
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

int variabile[50];
enum variabili {
  numeroSveglia,
  oraSveglia,
  minutiSveglia,
  modalita,
  durataSchermoAcceso,
  durataStandBy,
  limiteRichiesteLuce
};


int i, r, c;
bool inputBottone, inputBallSwitch, inputJoystick;
unsigned long int millisRitardo, millisPulsante, millisBallSwitch, millisJoystick;
bool svegliaAbilitata = true;
int schermoAcceso = 50;
int standBy = 10;
bool rilevataInterazioneLuce = false;
int ritardoEsecuzione = 100;
//int lampeggio;


enum stati {
  attivo,
  riposo,
  aggiorna,
  allarmeInCorso
};
int statoInterazione = attivo;

int arrayIdealeLuce[100];
int arrayLuce[100];
int puntoArrayLuce = 0;
