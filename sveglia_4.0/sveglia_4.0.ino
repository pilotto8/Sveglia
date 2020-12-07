#include <pitches.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <EEPROM.h>
DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#include <Adafruit_SleepyDog.h>
#define SW_pin 5
#define X_pin A1
#define Y_pin A0
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
boolean suona = false;
int o1 = 6;
int m1 = 5;
int s1 = 0;
int o2 = 0;
int m2 = 0;
int x = 5;
int y = 5;
boolean quic = true;
int v;
int s = 1;
int inter = 0;
int al = 0;
int Maxlux = 0;
int maxlux1 = 0;
int light = 0;
boolean reloadinf = true;
boolean inv = false;
int invo = 8;
int Inv = 0;
int semp = 1;
int it = 0;
int d = 0;
int t = 100;
int i = 0;

boolean adjustlight = false;///////////////
int adstdby = 1;
int calstdby = 0;
int calstdby1 = 0;

int a = 0;
boolean fine;
boolean fine1 = false;
int setlux = 0;
int luxvel = 5;
int luxtoll = 5;
#define maxlung 16
int luxarray[maxlung];
unsigned int luxmin = 1024;
int fotores = 50;
int fotores1 = fotores;
boolean risveglio = true;
int dark = 5;
int darkmode = 1;
int volfoto = 1;
int c = 1;
int onoff = 0;
int debug = 1;
int fer = 0;
int sv = 1;
int sv1 = 1;
int sve = 0;
boolean manual = false;
boolean oggmanual = false;
int post = 0;
int SV[] {7, 30, 8, 30, 9, 20, 10, 10};
int py = 0;
long int dmin;

int lam = 0;
boolean ra = false;
int l = 1;
int jx = 0;
int jy = 0;
int MaxX = 0;
int MinX = 0;
int MaxY = 0;
int MinY = 0;
int setin;
int setin1;
int setin2;
int refresh = 1;
int r = 0;
int q = 0;

int Setin[] {5, 0, 4, 0, 4, 0, 3, 0, 4, 0, 7, 0, 6, 0, 4, 0, 2, 0, 2, 0, 0, 0};
const int in[] = {
  0, 0, 8, 0, 0, 1, 8, 1, 15, 1,
  5, 0, 8, 0, 3, 1, 14, 1,
  0, 1, 5, 1, 10, 1, 15, 1,
  0, 1, 5, 1, 12, 1,
  1, 1, 6, 1, 11, 1, 15, 1,
  1, 0, 3, 0, 5, 0, 7, 0, 9, 0, 11, 0, 13, 0,
  4, 0, 7, 0, 10, 0, 5, 1, 8, 1, 12, 1,
  0, 1, 7, 1, 14, 1, 15, 1,
  2, 1, 8, 1,
  0, 1, 9, 1
};

int rallenta = 0;
int mode[] {0, 0, 0, 0, 0, 0, 0};
int sleep = 3000;
int durlight = 300;
int durwakeup = 700;
int Switch;
int tswitch = 0;
int tempReading;
int Ripeti = 1;
int day;
const char* printday[] = {"Lun", "Mar", "Mer", "Gio", "Ven", "Sab", "Dom"};
int cal;
boolean ora = false;
int amb = 0;
int amb1 = 0;
int antlam = 0;
int stop = 6;
int Ora, Min, Sec, Gio, Mes, Ann;
boolean cambia;
int sleepmode = 30;

int Temp = 0;
int ta;
int autoback = 1;
int autobackup[9][8];
int chiedi = 1;
int profilo = 0;

int autoday[5][7];
int svmagg[4];
int indic;
int settind = 0;
int autodayact = 0;
int svsuonata = 0;
String inputString = "";
bool stringComplete = false;

#define navvisi 4
int noti[navvisi];
int avvisato[navvisi];
short int ifnot = 0;
boolean push = false;
void setnot(int s) {
  if (noti[s] == 0) {
    noti[s] = 1;
    ifnot++;
    push = true;
  }
}
int notmap[navvisi] {8, 3, 10,};
const char* notitext[navvisi][2] = {
  {"Ripristino", "disponibile"},
  {"Calibra", "sensore"},
  {"Routine", "disponibile"},
  {"Errore", "codice"}
};
void mostranot(boolean soloAvviso) {
  for (a = 0, fine = false; noti[a] == 0 && fine == false; a++) {
    if (noti[a] == 1 && (avvisato[a] == 0 && soloAvviso == false)) {
      fine = true;
    }
  }
  if (soloAvviso == true) {
    avvisato[a] = 1;
  }
  else {
    avvisato[a] = 0;
    noti[a] = 0;
    ifnot--;
  }
  lcd.setCursor(3, 0);
  lcd.print(notitext[a][0]);
  lcd.setCursor(3, 1);
  lcd.print(notitext[a][1]);
}

unsigned long int scpu = 0;
void setup() {
  pinMode(6, INPUT_PULLUP);
  pinMode(3, INPUT);
  pinMode(SW_pin, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  inputString.reserve(20);
  clock.begin();
  clock.armAlarm1(false);
  clock.armAlarm2(false);
  clock.clearAlarm1();
  clock.clearAlarm2();
  lcd.begin(16, 2);
  lcd.createChar(1, campanella);
  lcd.createChar(2, unavolta);
  lcd.createChar(3, ripeti);
  lcd.createChar(4, calend);
  lcd.createChar(5, cerchio);

  // Mappatura elementi impostazioni
  for (setin = 0; Setin[setin] != 0; setin = setin + 2) {
    if (setin == 0) {
      setin1 = -1;
    }
    else {
      setin1 = Setin[setin - 1];
    }
    setin2 = Setin[setin];
    setin2 = setin2 * 2;
    Setin[setin] = setin1 + 1;
    Setin[setin + 1] = setin2 + setin1;
  }
  setin = 1;
  setin1 = 1;
  for (a = 0; a < 3; a++) {
    noti[a] = 0;
  }
  if (digitalRead(6) == LOW) {
    debug = 1;
  }
  Light();
  setluxeq();
  clock.setAlarm1(0, o1, m1, s1, DS3231_MATCH_H_M_S);
  dt = clock.getDateTime();
  gset(dt.year);
  svdomani();
  if (EEPROM.read(0) == 1 || EEPROM.read(69) == 0) {
    if (EEPROM.read(69) == 1) {
      setnot(0);
    }
    for (q = 0; q < 7; q++) {
      mode[q] = -1;
    }
    for (r = 0; r < 5; r++) {
      for (q = 0; q < 7; q++) {
        autoday[r][q] = -1;
      }
    }
  }
  else {
    ripristino();
  }
  EEPROM.update(69, 1);
  if (mode[cal] == -1) {
    manual = true;
  }
}

void loop() {
  // Aggiornamento display
  //Serial.println(millis() - scpu);
  scpu = millis();
  dt = clock.getDateTime();
  if (i > 0) {
    home(false);
  }

  // Allarme
  if (clock.isAlarm1() && c == 1 || Temp == 1 || debug == 0 || suona == true) {
    suona = false;
    if (autodayact == 1 && post == 0) {
      svsuonata = sv;
    }
    Light();
    setluxeq();
    lcd.clear();
    if (debug == 0 || Temp == 1) {
      lcd.setCursor(0, 1);
      lcd.print("STACCA LA SPINA");
    }
    else {
      data();
    }
    for (fer = 390; digitalRead(3) == LOW && fer > 0; fer--) {
      dt = clock.getDateTime();
      orologio();
      tone(4, melody[4], 80);
      Delay(1);
      if (fer % 3 == 0) {
        if (lum(true) == true && antlam <= stop) {
          it = 1;
          fer = 0;
          Dark();
          tone(4, melody[3], 20);
        }
      }
      reloadinf = true;
      al = 1;
      debug = 1;
    }

    // Imposta posticipo
    post++;
    if (post == 1) {
      m2 = m1 + 5;
      o2 = o1;
    }
    else {
      m2 += 5;
    }
    if (m2 > 59) {
      m2 -= 60;
      o2++;
    }
    clock.armAlarm1(false);
    clock.clearAlarm1();
    clock.setAlarm1(0, o2, m2, 0, DS3231_MATCH_H_M_S);
    lcd.clear();
    lam = 0;
    do {
      dt = clock.getDateTime();
      home(true);
      delay(100);
    }
    while (digitalRead(6) == LOW || digitalRead(3) == HIGH);
  }

  // Gestione posticipo
  if (al == 1) {
    i = durwakeup;
    amb++;
    if (amb >= 11 || light == 1) {
      amb = 0;
    }

    // Lampeggio ogni minuto
    if (dt.second == 0 && dt.minute != m2 && dt.minute != m1 || lam > 0) {
      digitalWrite(2, LOW);
      if (light == 0) {
        light = 40;//5+35
      }
      t = 500;
      delay(t);
      digitalWrite(2, HIGH);
      lam++;
      if (lam == 4) {
        lam = 0;
        t = 100;
      }
    }

    // Rimozione posticipo
    if (digitalRead(6) == LOW || d == 40 || post == 20) {
togliposticipo:
      Clear(true, true);
      tone(4, melody[1], 200);
      if (Ripeti == 0) {
        c = 0;
      }
      amb = 0;
      svdomani();
    }
    if (it == 1 && luxmin <= dark) {
      d++;
    }
    else {
      d = 0;
    }
  }

  // Ball switch
  if (digitalRead(6) == LOW) {
    if (adstdby > 0 && fine1 == false) {
      fine1 = true;
      durwakeup += (int)((calstdby * sleep / 300) / adstdby);
      calstdby1 = 0;
      //Serial.println(durwakeup);
      EEPROM.update(11, durwakeup / 20);
      if (durwakeup <= 0) {
        setnot(3);
        durwakeup = 20;
      }
    }
    Light();
    antlam = 0;
  }

  // Programmazione settimanale
  if (dt.hour == 0 && dt.minute == 0) {
    if (ra == false) {
      ra = true;
      if (autodayact == 1){
      autoday[settind][day] = svsuonata;
      EEPROM.update(settind * 7 + day + 33, svsuonata + 1);
      EEPROM.update(29, svsuonata + 1);
      svsuonata = 0;
      indic = 0;
      for (r = (settind + 1) % 6, q = 0; q < 5; r = (r + 1) % 6, q++) {
        if (autoday[r][day] != -1) {
          svmagg[autoday[r][day]]++;
          if (svmagg[autoday[r][day]] >= indic) {
            indic = svmagg[autoday[r][day]];
            mode[day] = autoday[r][day];
          }
        }
      }
      EEPROM.update(day + 20, mode[day] + 1);
      for (a = 0; a < 4; a++) {
        svmagg[a] = 0;
      }

      // Rilevamento routine disponibile
      if (Ripeti != 2) {
        fine = true;
        for (r = 0, q = 0; r < 7; r++) {
          if (autoday[settind][r] == autoday[(settind + 3) % 4][r]) {
            q++;
            if (autoday[settind][r] != autoday[settind][(r + 1) % 7] && autoday[settind][r] != -1 && autoday[settind][(r + 1) % 7] != -1) {
              fine = false;
            }
          }
          if (autoday[settind][r] > 4 || autoday[settind][r] < -1) {
            setnot(3);
          }
        }
        if (q >= 4 && fine == false) {
          setnot(2);
        }
      }
    }


      dt = clock.getDateTime();
      gset(dt.year);
      svdomani();
      if (Ripeti == 2) {
        ora = true;
      }
      if (volfoto == 0) {
        setnot(1);
      }
      else {
        volfoto = 0;
      }
    }
  }
  else if (ra == true) {
    ra = false;
  }


  if (al == 0) {
    if (ora == true) {
      ora = false;
      if (manual == false) {
        if (oggmanual == true) {
          oggmanual = false;
        }
        else {
          svoggi();
        }
        if (sv > 0) {
          c = 1;
          o1 = SV[sv * 2 - 2];
          m1 = SV[sv * 2 - 1];
          Clear(true, false);
        }
        else if (sv == 0) {
          c = 0;
          clock.armAlarm1(false);
          clock.clearAlarm1();
        }
        else {
          manual = true;
        }
      }
      else {
        if (mode[cal] != -1) {
          manual = false;
        }
      }
    }
  }

  // Impostazioni
  if (digitalRead(SW_pin) == LOW) {
    debug = 1;
    antlam = 0;
    reloadinf = true;
    Light();
    lcd.clear();
    s = 2;
    refresh = 1;
    setlux = 0;
    inter = 0;
    do {
      delay(65);
      setlux++;
      if (setlux == 6) {
        if (ifnot > 0) {
          mostranot(false);
          s = notmap[a];
          if (digitalRead(SW_pin) == HIGH) {
            delay(1000);
          }
        }
        else {
          lcd.print(F("Impostazioni"));
          s = 1;
        }
      }
    }
    while (digitalRead(SW_pin) == LOW);

    // Timer
    for (v = 50; v >= 0; v--) {
      x = 10 - analogRead(X_pin) / 100;
      y = analogRead(Y_pin) / 100;

      // Controllo joystick
      if (r == 0) {
        if (y > 6) {
          jy = jy + 1;
          r = -1;
          v = 50;
          setin += 2;
          if (jy > MaxY) {
            jy = MinY;
            setin = Setin[s * 2 - 2];
          }
          quic = false;
          goto Skip;
        }
        if (y < 4) {
          jy = jy - 1;
          r = -1;
          v = 50;
          setin -= 2;
          if (jy < MinY) {
            jy = MaxY;
            setin = Setin[s * 2 - 1] - 1;
          }
          quic = false;
          goto Skip;
        }

        if (y == 5) {
          t = 160;
          if (x > 6 || x < 4) {
            autobackup[s - 1][jy + inter * (MaxY)] = 1;
          }
          if (x > 6) {
            jx = jx + 1;
            v = 50;
            if (jx > MaxX) {
              jx = MinX;
            }
            ra = true;
            quic = false;
            goto Skip;
          }
          if (x < 4) {
            jx = jx - 1;
            v = 50;
            if (jx < MinX) {
              jx = MaxX;
            }
            ra = true;
            quic = false;
            goto Skip;
          }
        }
      }


      // Lampeggio sel.
      if (refresh == 0) {
        lcd.setCursor(in[setin], in[setin + 1]);
        switch (l) {
          case 0: {
              // null
            }
          case 1: {
              Delay(3); // 260 - t
              while (lam > 0) {
                lcd.print(" ");
                lam--;
              }
            }
        }
        Skip:
        if (r == -1) {
          r = 1;
          l = 1;
          t = 70;
        }
        else if (r == 1) {
          r = 0;
        }
      }

      // Controllo display
      if (refresh >= 1) {
        setin += 2;
        jy = jy + 1;
        if (refresh == 1) {
          //Serial.println("-----------------");
          lcd.clear();
          setin = Setin[s * 2 - 2];
          setin1 = Setin[s * 2 - 1];
          MaxY = ((Setin[s * 2 - 1]) - (Setin[s * 2 - 2]) - 1) / 2;
          MinY = 0;
          jx = 0;
          jy = 0;
          refresh = 2;
          r = 1;
          t = 0;
        }
        if (setin < setin1) {
          lcd.setCursor(in[setin], in[setin + 1]);
        }
        else {
          refresh = 0;
          setin = Setin[s * 2 - 2];
          jy = 0;
          t = 100;
        }
      }
      Delay(3);
      lcd.setCursor(in[setin], in[setin + 1]);


      // Interfaccia 1
      if (s == 1) {
        if (refresh == 2) {
          MaxX = 0;
          MinX = 0;
        }
        if (inter == 0) {
          if (jy == 0) {
            lcd.print(F("Allarme"));
            lam = 7;
          }
          if (jy == 1) {
            lcd.print(F("Luce"));
            lam = 4;
          }
          if (jy == 2) {
            lcd.print(F("On/Off"));
            lam = 6;
          }
          if (jy == 3) {
            lcd.print(F("Batteria"));
            lam = 8;
          }
          if (jy == 4) {
            t = 0;
            if (r == 1) {
            }
            else {
              inter = 1;
              refresh = 1;
              v = 50;
            }
          }
        }
        else {
          if (jy == 0) {
            lcd.print(F("Giorni"));
            lam = 6;
          }
          if (jy == 1) {
            lcd.print(F("Data/Ora"));
            lam = 8;
          }
          if (jy == 2) {
            lcd.print(F("Backup"));
            lam = 6;
          }
          if (jy == 3) {
            lcd.print(F("A.I."));
            lam = 4;
          }
          if (jy == 4) {
            t = 0;
            if (r == 1) {
            }
            else {
              inter = 0;
              refresh = 1;
              v = 50;
            }
          }
        }
        if (digitalRead(SW_pin) == LOW) {
          s = jy + 2 + inter * 4;
          r = 1;
          refresh = 1;
          v = 50;
          inter = 0;
          while (digitalRead(SW_pin) == LOW);
        }
      }


      // Interfaccia 2
      if (s == 2) {
        if (sv <= 0) {
          sv = 1;
        }
        if (jy == 0) {
          if (r == 1) {
            jx = o1;
            MaxX = 23;
            MinX = 0;
          }
          o1 = jx;
          SV[sv * 2 - 2] = o1;
          if (o1 < 10) {
            lcd.print(0);
          }
          lcd.print(o1);
          lcd.print(":");
          lam = 2;
        }
        if (jy == 1) {
          if (r == 1) {
            jx = m1;
            MaxX = 59;
            MinX = 0;
          }
          m1 = jx;
          SV[sv * 2 - 1] = m1;
          if (m1 < 10) {
            lcd.print(0);
          }
          lcd.print(m1);
          lam = 2;
        }
        if (jy == 2) {
          if (r == 1) {
            jx = sv;
            MaxX = 4;
            MinX = 1;
          }
          sv1 = sv;
          sv = jx;
          lcd.print("Sveglia ");
          lcd.print(sv);
          lam = 9;
          if (sv != sv1) {
            o1 = SV[sv * 2 - 2];
            m1 = SV[sv * 2 - 1];
            lcd.setCursor(5, 0);
            if (o1 < 10) {
              lcd.print(0);
            }
            lcd.print(o1);
            lcd.setCursor(8, 0);
            if (m1 < 10) {
              lcd.print(0);
            }
            lcd.print(m1);
          }
        }
        if (jy == 3) {
          if (r == 1) {
            jx = Ripeti;
            MaxX = 2;
            MinX = 0;
            manual = false;
            sve = 50;
          }
          Ripeti = jx;
          rallenta = 1;
          lcd.write(Ripeti + 2);
          lam = 1;
        }
      }


      // Interfaccia 3
      if (s == 3) {
        if (inter == 0) {
          /*if (digitalRead(SW_pin) == LOW && fotores1 != fotores) {
            ambient = ambient - fotores1 + fotores;
            fotores1 = fotores;
            }*/
          if (jy == 0) {
            if (r == 1) {
              jx = fotores;
              MaxX = 250;
              MinX = 2;
            }
            fotores = jx;
            if (fotores < 100) {
              lcd.print("_");
              if (fotores < 10) {
                lcd.print("_");
              }
            }
            lcd.print(fotores);
            lam = 3;
          }
          if (jy == 1) {
            if (r == 1) {
              if (darkmode == 1) {
                jx = -1;
              } else {
                jx = dark;
              }
              MaxX = 250;
              MinX = -1;
            }
            dark = jx;
            if (dark == -1) {
              darkmode = 1;
              lcd.print("auto");
            }
            else {
              darkmode = 0;
              if (dark < 100) {
                lcd.print("_");
                if (dark < 10) {
                  lcd.print("_");
                }
              }
              lcd.print(dark);
              lcd.print(" ");
            }
            lam = 4;
          }
          if (jy == 2) {
            jx = 0;
            lcd.print("Esegui");
            lam = 6;
            if (digitalRead(SW_pin) == LOW) {
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print(F("Calibrazione"));
              lcd.setCursor(2, 1);
              lcd.print(F("tra... "));
              for (a = 3; a > 0; a--) {
                lcd.setCursor(9, 1);
                lcd.print(a);
                delay(1000);
              }
              lcd.clear();
              digitalWrite(2, LOW);
              v = 8;
              setluxeq();
              luxvel = maxlung - 1;
              while (v > 7 && digitalRead(3) == LOW) {
                lum(true);
                for (a = 0; a < 100; a++) {
                  lum(false);
                  delay(1);
                }
                if (luxarray[0] > Maxlux) {
                  Maxlux = luxarray[0];
                }
                if ((luxarray[0] - luxmin) >= 2 + Maxlux * 5 / 10 && v == 8) {
                  dark = luxmin + 1;
                  for (v = 0; v < maxlung - 3 && luxvel == 10; v++) {
                    if (luxarray[v] == luxmin) {
                      luxvel = v + 2;
                    }
                  }
                  fotores = (luxarray[0] - luxmin);
                  fotores1 = fotores;
                  luxtoll = fotores + fotores / 2 + 1;
                  tone(4, melody[2], 100);
                  v = 0;
                }
              }
              Maxlux = 0;
              Dark();
              digitalWrite(2, HIGH);
            }
          }
          if (jy == 3) {
            t = 0;
            if (r == 1) {
            }
            else {
              inter = 1;
              v = 50;
              refresh = 1;
            }
          }
          if (refresh == 2) {
            lcd.setCursor(0, 0);
            lcd.print(F("Luce Buio Cal. "));
          }
        }
        else {
          if (jy == 0) {
            if (r == 1) {
              MinX = 0;
              MaxX = maxlung - 1;
              jx = luxvel;
            }
            luxvel = jx;
            lcd.print(" ");
            if (jx < 10) {
              lcd.print("_");
            }
            lcd.print(luxvel);
            lam = 3;
          }
          if (jy == 1) {
            if (r == 1) {
              MinX = 0;
              MaxX = 20;
              jx = luxtoll;
            }
            luxtoll = jx;
            lcd.print("  ");
            if (jx < 10) {
              lcd.print("_");
            }
            lcd.print(luxtoll);
            lam = 4;
          }
          if (jy == 3 || jy == 2) {
            t = 0;
            if (r == 1) {
            }
            else {
              inter = 0;
              v = 50;
              refresh = 1;
            }
          }
          if (refresh == 2) {
            lcd.setCursor(0, 0);
            lcd.print(F("Lung. Toll."));
          }
        }
      }


      // Interfaccia 4
      if (s == 4) {
        if (jy == 0) {
          if (r == 1) {
            MaxX = 11;
            MinX = 2;
            jx = stop;
          }
          stop = jx;
          lcd.print(" ");
          if (stop - 1 < 10) {
            lcd.print("_");
          }
          lcd.print(stop - 1);
          lam = 3;
        }
        if (jy == 1) {
          if (r == 1) {
            MaxX = 50;
            MinX = 0;
            jx = invo;
          }
          lcd.print(" ");
          if (jx < 10) {
            lcd.print("_");
          }
          lcd.print(jx);
          if (jx != invo) {
            invo = jx;
            if (semp == 1) {
              lcd.setCursor(12, 1);
              if (invo == 0) {
                lcd.print("off");
              }
              else {
                lcd.print("on ");
              }
            }
          }
          lam = 3;
        }
        if (jy == 2) {
          if (r == 1) {
            MaxX = 1;
            MinX = 0;
            if (invo == 0) {
              semp = 0;
            }
            jx = semp;
          }
          semp = jx;
          if (semp == 1) {
            lcd.print("on ");
            lam = 3;
          }
          else {
            lcd.print("off");
            lam = 3;
          }
          rallenta = 1;
        }
        if (digitalRead(SW_pin) == LOW && invo == 0) {
          semp = 0;
        }
        if (refresh == 2) {
          lcd.setCursor(0, 0);
          lcd.print(F("Stop Inv. Sempre"));
        }
      }

      // Interfaccia 5
      if (s == 5) {
        if (inter == 0) {
          if (jy == 0) {
            if (r == 1) {
              MaxX = 70;
              MinX = 1;
              jx = durlight / 20;
            }
            durlight = jx * 20;
            light = durlight;
            if (jx < 10) {
              lcd.print("_");
            }
            lcd.print(jx);
            lam = 2;
          }
          if (jy == 1) {
            if (r == 1) {
              MaxX = 55;
              MinX = 1;
              jx = durwakeup / 20;
            }
            durwakeup = jx * 20;
            i = durwakeup;
            if (jx < 10) {
              lcd.print("_");
            }
            lcd.print(jx);
            lam = 2;
          }
          if (jy == 2) {
            if (r == 1) {
              MaxX = 25;
              MinX = 1;
              jx = sleep / 200;
            }
            sleep = jx * 200;
            if (jx < 10) {
              lcd.print("_");
            }
            lcd.print(jx);
            lam = 2;
          }
          if (jy == 3) {
            t = 0;
            if (r == 1) {
            }
            else {
              inter = 1;
              v = 50;
              refresh = 1;
            }
          }
          if (refresh == 2) {
            lcd.setCursor(0, 0);
            lcd.print(F("LCD St.by Sleep"));
          }
        }
        else {
          if (jy == 0) {
            if (r == 1) {
              MaxX = 20;
              MinX = 0;
              jx = sleepmode / 5;
            }
            if (jx != 0) {
              sleepmode = jx * 5;
            }
            else {
              sleepmode = 1;
            }
            if (sleepmode < 100) {
              lcd.print("_");
              if (sleepmode < 10) {
                lcd.print("_");
              }
            }
            lcd.print(sleepmode);
            lam = 3;
          }
          if (jy == 3 || jy == 1) {
            t = 0;
            if (r == 1) {
            }
            else {
              inter = 0;
              v = 50;
              refresh = 1;
            }
          }
          if (refresh == 2) {
            lcd.setCursor(0, 0);
            lcd.print(F("Reatt."));
          }
        }
      }


      // Interfaccia 6
      if (s == 6) {
        if (r == 1) {
          MaxX = 4;
          MinX = -1;
          jx = mode[jy];
        }
        mode[jy] = jx;
        if (jx > 0) {
          lcd.print(jx);
        } else if (jx == 0) {
          lcd.print("X");
        } else if (jx == -1) {
          lcd.print("M");
        }
        lam = 1;
        rallenta = 1;
        if (refresh == 2) {
          lcd.setCursor(1, 1);
          lcd.print(F("L M M G V S D"));
        }
      }


      // Interfaccia 7
      if (s == 7) {
        dt = clock.getDateTime();
        if (refresh == 2) {
          Ora = dt.hour;
          Min = dt.minute;
          Sec = dt.second;
          Gio = dt.day;
          Mes = dt.month;
          Ann = dt.year;
          dmin = 0;
          cambia = true;
        }
        if (jy == 0) {
          if (r == 1) {
            MaxX = 23;
            MinX = 0;
            jx = Ora;
          }
          Ora = jx;
          if (jx < 10) {
            lcd.print(0);
          }
          lcd.print(jx);
        }
        if (jy == 1) {
          if (r == 1) {
            MaxX = 59;
            MinX = 0;
            jx = Min;
          }
          Min = jx;
          if (jx < 10) {
            lcd.print(0);
          }
          lcd.print(jx);
        }
        if (jy == 2) {
          if (r == 1) {
            MaxX = 59;
            MinX = 0;
            jx = dmin;
          }
          dmin = jx;
          Sec = (dt.second + dmin) % 60;
          if (Sec < 10) {
            lcd.print(0);
          }
          lcd.print(Sec);
        }
        if (jy == 3) {
          if (r == 1) {
            MaxX = MaxDay(Mes);
            MinX = 1;
            if (Gio > MaxX) {
              Gio = MaxX;
            }
            jx = Gio;
          }
          Gio = jx;
          if (jx < 10) {
            lcd.print(0);
          }
          lcd.print(jx);
        }
        if (jy == 4) {
          if (r == 1) {
            MaxX = 12;
            MinX = 1;
            jx = Mes;
          }
          Mes = jx;
          if (jx < 10) {
            lcd.print(0);
          }
          lcd.print(jx);
        }
        lam = 2;
        if (jy == 5) {
          if (r == 1) {
            MaxX = 3000;
            MinX = 2018;
            jx = Ann;
          }
          Ann = jx;
          lcd.print(jx);
          lam = 4;
          rallenta = 1;
        }
        if (digitalRead(SW_pin) == LOW) {
          if (Gio > MaxDay(Mes)) {
            Gio = MaxDay(Mes);
          }
          clock.setDateTime(Ann, Mes, Gio, Ora, Min, Sec);
          dt = clock.getDateTime();
          gset(Ann);
        }
        if (refresh == 2) {
          lcd.setCursor(6, 0);
          lcd.print(":");
          lcd.setCursor(9, 0);
          lcd.print(":");
          lcd.setCursor(7, 1);
          lcd.print("/");
        }
        else {
          if (jy != 2) {
            Sec = (dt.second + dmin) % 60;
          }
          if (Sec != 0) {
            cambia = true;
          }
          if (Sec == 0 && cambia == true) {
            cambia = false;
            Min++;
            if (Min == 60) {
              Min = 0;
              Ora++;
              if (Ora == 24) {
                Ora = 0;
              }
              if (jy != 0) {
                lcd.setCursor(4, 0);
                if (Ora < 10) {
                  lcd.print(0);
                }
                lcd.print(Ora);
              }
              else {
                jx = Ora;
              }
            }
            if (jy != 1) {
              lcd.setCursor(7, 0);
              if (Min < 10) {
                lcd.print(0);
              }
              lcd.print(Min);
            }
            else {
              jx = Min;
            }
          }
          if (jy != 2) {
            lcd.setCursor(10, 0);
            if (Sec < 10) {
              lcd.print(0);
            }
            lcd.print(Sec);
          }
        }
      }


      //Interfaccia 8
      if (s == 8) {
        if (inter == 0) {
          if (jy == 0) {
            if (r == 1) {
              MinX = 0;
              MaxX = 0;
              jx = 0;
            }
            lcd.print("Esegui");
            lam = 6;
            if (digitalRead(SW_pin) == LOW) {
              ripristino();
            }
          }
          if (jy == 1) {
            if (r == 1) {
              MinX = 0;
              MaxX = 0;
              jx = 0;
            }
            lcd.print("Esegui");
            lam = 6;
            if (digitalRead(SW_pin) == LOW) {
              backup();
            }
          }
          if (jy == 2) {
            if (r == 1) {
              MinX = 0;
              MaxX = 0;
              jx = 0;
            }
            lcd.print("X");
            lam = 1;
          }
          if (jy == 3) {
            t = 0;
            if (r == 1) {
            }
            else {
              inter = 1;
              v = 50;
              refresh = 1;
            }
          }
          if (refresh == 2) {
            lcd.setCursor(0, 0);
            lcd.print(F("Ripr.  "));
            if (profilo == 0) {
              lcd.print(F("Default"));
            }
            else {
              lcd.print(F("Backup"));
            }
          }
        }
        else {
          if (jy == 0) {
            if (r == 1) {
              MinX = 0;
              MaxX = 1;
              jx = chiedi;
            }
            chiedi = jx;
            if (chiedi == 0) {
              lcd.print("OFF");
              lam = 3;
            }
            else {
              lcd.print("ON ");
              lam = 2;
            }
          }
          if (jy == 1) {
            if (r == 1) {
              MinX = 0;
              MaxX = 10;
              jx = autoback;
            }
            autoback = jx;
            if (autoback == 0) {
              lcd.print("OFF");
              lam = 3;
            }
            else {
              lcd.print(" ");
              if (autoback < 10) {
                lcd.print("_");
              }
              lcd.print(autoback);
              lam = 3;
            }
          }
          if (jy == 3 || jy == 2) {
            t = 0;
            if (r == 1) {
            }
            else {
              inter = 0;
              v = 50;
              refresh = 1;
            }
          }
          if (refresh == 2) {
            lcd.setCursor(0, 0);
            lcd.print(F("Chiedi Auto"));
          }
        }
      }

      // Interfaccia 9
      if (s == 9) {
        if (jy == 0) {
          if (r == 1) {
            MinX = 0;
            MaxX = 1;
            jx = autodayact;
          }
          autodayact = jx;;
          if (jx == 1) {
            lcd.print("ON ");
          }
          else {
            lcd.print("OFF");
          }
          lam = 3;
        }
        if (jy == 1) {
          if (r == 1) {
            MinX = 0;
            MaxX = 3;
            jx = 3 - adstdby;
          }
          adstdby = 3 - jx;
          if (adstdby == 0) {
            lcd.print("OFF");
          }
          else {
            lcd.print(" ");
            lcd.print(jx + 1);
            lcd.print(" ");
          }
          lam = 3;
        }
        if (refresh == 2) {
          lcd.setCursor(0, 0);
          lcd.print(F("Giorni St.by"));
        }
      }

      // Interfaccia 10
      if (s == 10) {
        if (jy == 0) {
          if (r == 1) {
            MinX = 0;
            MaxX = 0;
            jx = 0;
          }
          lcd.print("Imposta");
          lam = 7;
        }
        if (jy == 1) {
          if (r == 1) {
            MinX = 0;
            MaxX = 0;
            jx = 0;
          }
          lcd.print("Ignora");
          lam = 6;
        }
        if (digitalRead(SW_pin) == LOW && jy == 0) {
          lcd.clear();
          refresh = 1;
          s = 6;
          if (s == 6) { /// Per il supporto ad altre notifiche
            manual = false;
            Ripeti = 2;
            ora = true;
          }
        }
        if (refresh == 2) {
          lcd.setCursor(1, 0);
          lcd.print(F("Cosa vuoi fare?"));
        }
      }
      /*if(r == 1 && refresh >= 1){
          Serial.println(jx);
        }*/

      // Rallenta aggiornamento variabile
      if (ra == true) {
        if (rallenta == 1) {
          delay(100);
          rallenta = 0;
        }
        ra = false;
      }


      //Backup automatico
      if (digitalRead(SW_pin) == LOW && refresh == 0) {
        v = 0;
        t = 0;
        if (profilo == 0) {
          if (rilcamb() > 0) {
            profilo = 1;
          }
        }
        if (rilcamb() >= autoback && autoback > 0) {
          lcd.clear();
          lcd.setCursor(5, 0);
          lcd.print(F("Backup"));
          lcd.setCursor(4, 1);
          lcd.print(F("eseguito"));
          backup();
          delay(500);
        }
      }
    }
    lcd.clear();


    // Ridefinizione della sveglia
    if (s == 2) {
      c = 1;
      Clear(true, true);
    }
    if (Ripeti == 2) {
      if (jy == 3) {
        ora = true;
      }
      else {
        ora = false;
      }
    }
  }
  while (digitalRead(SW_pin) == LOW);

  // Luce display
  if (light > 0) {
    light--;
    if (py == 1) {
      if (luxmin <= dark && inv == false) {
        inv = true;
        Inv = durlight - light;
      }
      if (inv == true) {
        if (light <= durlight - invo - Inv * semp) {
          if (luxmin <= dark) {
            light = 0;
          }
        }
      }
    }
    if (light == 0) {
      digitalWrite(2, LOW);
      t = 300;
      py = 0;
      inv = false;
      Inv = 0;
      reloadinf = true;
    }

    // Indicatore sveglia
    lcd.setCursor(0, 1);
    if (c == 1) {
      if (amb <= 5) {
        lcd.write(1);
        lcd.print(sv);
      }
      else {
        lcd.print("  ");
      }
      if (tswitch > 3 && al == 0) {
        if (light > durlight - 10) {
          lcd.setCursor(4, 1);
          stampasv(1);
          lcd.print(" ");
        }
        if (light == durlight - 15) {
          data();
          tswitch = 0;
        }
      }
    }
    else {
      lcd.print("  ");
    }

    // Indicatore modalità
    lcd.setCursor(0, 0);
    if (Ripeti != 2) {
      lcd.write(Ripeti + 2);
    }
    else {
      if (mode[cal] == -1 || manual == true) {
        lcd.print("M ");
      }
      else if (mode[cal] == 0) {
        lcd.print("X ");
      }
      else {
        lcd.write(4);
        lcd.print(mode[cal]);
      }
    }
  }

  // on/off e spegni LCD
  if (digitalRead(3) == HIGH) {
    tswitch = 0;
    antlam = 0;
    onoff++;
    if (sve > 0) {
      sve = 50;
    }
    if (adstdby > 0 && fine1 == false) {
      fine1 = true;
      durwakeup += (int)((calstdby * sleep / 300) / adstdby);
      calstdby1 = 0;
      //Serial.println(durwakeup);
      EEPROM.update(11, durwakeup / 20);
      if (durwakeup <= 0) {
        setnot(3);
        durwakeup = 20;
      }
    }
    Light();
    if (Switch == 2) {
      light = 1;
      while (digitalRead(3) == HIGH && onoff < 10 * 4) {
        onoff++;
        if (onoff == 10 * 4) {
          light = durlight;
        }
        delay(10);
      }
      Switch = 0;
      tswitch = 0;
    }
    else {
      Switch = 1;
    }
    if (onoff == 10 * 4) {
      if (al == 0) {
        Clear(false, true);
        if (Ripeti == 2) {
          sve = 50;
        }
        Switch = 0;
        tswitch = 0;
        if (c == 0) {
          Clear(true, false);
          c = 1;
          tone(4, melody[4], 20);
        }
        else {
          clock.armAlarm1(false);
          c = 0;
          tone(4, melody[1], 20);
        }
      }
      else {
        goto togliposticipo;
      }
    }
  }
  else {
    onoff = 0;
    if (Switch >= 1) {
      Switch = 2;
      tswitch = tswitch + 1;
      if (tswitch == 6) {
        Switch = 0;
      }
    }
  }

  // Selettore rapido sveglie
  if (al == 0) {
    x = 10 - analogRead(X_pin) / 100;
    y = analogRead(Y_pin) / 100;
    if (x > 8 || x < 2) {
      Light();
      reloadinf = true;
      if (Ripeti == 2) {
        sve = 50;
      }
      if (c == 0) {
        c = 1;
        sv = 0;
      }
      if (x > 8) {
        sv = sv + 1;
        if (sv == 5) {
          sv = 1;
        }
      }
      if (x < 2) {
        sv = sv - 1;
        if (sv == 0) {
          sv = 4;
        }
      }
      if (sv <= 0) {
        sv = 1;
      }
      o1 = SV[sv * 2 - 2];
      m1 = SV[sv * 2 - 1];
      Clear(true, false);
      lcd.clear();
      lcd.setCursor(5, 0);
      stampasv(1);
      lcd.setCursor(3, 1);
      lcd.print(F("Sveglia "));
      lcd.print(sv);
      delay(700);
      lcd.clear();
    }


    // Selettore modalità
    else if (y > 8 || y < 2) {
      Light();
      reloadinf = true;
      lcd.clear();
      lcd.setCursor(1, 0);
      if (Ripeti == 2) {
        if (manual == false || mode[cal] == -1) {
          manual = true;
          sve = 0;
          lcd.print("Manuale M");
        }
        else {
          manual = false;
          sve = 0;
          if (mode[day] == -1) {
            sv = mode[cal];
            oggmanual = true;
          }
          ora = true;
          lcd.print(F("Automatico "));
        }
      }
      else if (Ripeti == 1) {
        Ripeti = 0;
        lcd.print(F("Una volta "));
      }
      else if (Ripeti == 0) {
        Ripeti = 1;
        lcd.print(F("Ogni giorno "));
      }
      if (manual == false || Ripeti != 2) {
        lcd.write(Ripeti + 2);
      }
      delay(700);
      lcd.clear();
    }
  }

  // Rileva manuale
  lcd.setCursor(2, 1);
  if (sve > 0 && manual == false && Ripeti == 2) {
    lcd.print("!");
    sve--;
    if (mode[cal] == -1) {
      sve = 0;
      manual = true;
    }
    if (sve == 0) {
      if (c == 0) {
        o2 = SV[sv * 2 - 2];
        m2 = SV[sv * 2 - 1];
        if (dt.hour * 100 + dt.minute * 100 / 60 > o2 * 100 + m2 * 100 / 60) {
          manual = true;
          tone(4, melody[4], 25);
        }
      }
      else {
        if (((o1 * 100 + m1 * 100 / 60) < (dt.hour * 100 + dt.minute * 100 / 60) && (sv != mode[cal]))) {
          manual = true;
          tone(4, melody[4], 25);
        }
      }
    }
  }
  else {
    sve = 0;
    lcd.print(" ");
  }

  // Risparmio energetico
  if (i > 0) {
    if (light == 0) {
      i--;
    }
    if (i == 0) {
      risveglio = true;
      fine1 = false;
      lcd.clear();
    }
  }
  else {
    dmin = (o1 * 60 + m1) - (dt.hour * 60 + dt.minute);
    if (dmin == 1 || dmin == 0) {
      t = 100;
    }
    else {
      Watchdog.sleep(sleep);
      t = 0;
      antlam = 0;

      if (adstdby > 0 && fine1 == false) {
        if (calstdby * sleep / 300 < 55 * 20) {
          calstdby++;
        }
        else {
          fine1 = true;
          calstdby1++;
          if (calstdby1 == 3 + adstdby) {
            calstdby1 = 0;
            if (durwakeup > 40) {
              durwakeup -= 20;
              Serial.println(durwakeup);
              EEPROM.update(11, durwakeup / 20);
              if (durwakeup <= 0) {
                setnot(3);
                durwakeup = 20;
              }
            }
          }
        }
      }
    }
  }

  // Comandi da seriale
  /*if (stringComplete) {
    Serial.println(inputString);
    if (inputString == F("suona")) {
      inputString = ""; // eccezione
      suona = true;
    }
    else if (inputString == F("luce")) {
      Light();
    }
    else if (inputString == F("buio")) {
      light = 1;
      i = 2;
    }
    else if (inputString == F("ora = true")) {
      ora = true;
    }
    else if (inputString == F("mezzanotte")) {
      clock.setDateTime(dt.year, dt.month, day, 23, 59, 55);
    }
    else if (inputString == F("manuale")) {
      sve = 50;
    }
    else if (inputString == F("backup")) {
      backup();
    }
    else if (inputString == F("ripristino")) {
      ripristino();
    }
    else if (inputString == F("giorno")) {
      gset(dt.year);
      light = durlight;
      reloadinf = true;
    }
    else {
      Serial.println(F("Comando non riconosciuto"));
    }
    inputString = "";
    stringComplete = false;
    } */

  // Notifiche
  if (light > 0 && al == 0) {
    if (ifnot > 0) {
      if (ifnot > 1) {
        lcd.setCursor(14, 0);
        lcd.print(ifnot);
      }
      else {
        lcd.setCursor(15, 0);
      }
      amb1 = (amb1 + 1) % 10;
      if (amb1 <= 5) {
        lcd.print("*");
      }
      else {
        lcd.print(" ");
      }
    }
    if (push == true) {
      push = false;
      light = durlight;
      reloadinf = true;
      lcd.clear();
      mostranot(true);
      delay(1500);
      lcd.clear();
    }
  }

  // Sensore di luce
  if (luxarray[0] > dark + fotores + luxtoll) {
    antlam = stop + 1;
  }
  Delay(2);
  if (lum(true) == true && antlam <= stop) {
    if (light == 0) {
      antlam++;
    }
    if (digitalRead(6) == HIGH) {
      Light();
      Dark();
      inv = false;
      py = 1;
      if (antlam == stop) {
        py = 0;
        setnot(1);
      }
      volfoto++;
      if (al == 1 && it == 0) {
        it = 1;
        tone(4, melody[3], 20);
      }
    }
  }
}

//Aggiorna display
void home(boolean all) {
  orologio();
  if (reloadinf == true && light >= durlight - 1 || all == true) {
    temp(false); //true
    data();
    reloadinf = false;
  }
}

// Ora e data
void orologio() {
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
void data() {
  lcd.setCursor(4, 1);
  lcd.print(printday[day]);
  lcd.print(" ");
  if ((dt.day) < 10) {
    lcd.print(0);
  }
  lcd.print(dt.day);
}

// Accensione display e riattivamento
void Light() {
  light = durlight;
  i = durwakeup;
  t = 100;
  if (adstdby > 0) {
    calstdby = 0;
  }
  digitalWrite(2, HIGH);
}

// Gestione termistore
int temp(boolean interfaccia) {
  tempReading = analogRead(A7);
  double tempC = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempC = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempC * tempC)) * tempC) - 273.15 + 1.5;
  /*float restemp = tempC - (int)tempC;
    tempC -= restemp;
    if (restemp >= 0.5) {
    tempC++;
    } */
  if (interfaccia) {
    lcd.setCursor(12, 1);
    if (tempC < 10) {
      lcd.print(0);
    }
    lcd.print(tempC);
    //lcd.write(5);
  }
  return tempC;
}

// Buio dinamico
void Dark() {
  if (darkmode == 1 && risveglio == true) {
    dark = luxmin;
  }
  risveglio = false;
  luxmin = luxarray[0];
}

// Pulizia variabili e reimposta sveglia
void Clear(boolean s, boolean var) {
  if (s == true) {
    if (o1 == 0 && m1 == 0) {
      s1 = 7;
    }
    else {
      s1 = 0;
    }
    clock.armAlarm1(false);
    clock.clearAlarm1();
    clock.setAlarm1(0, o1, m1, s1, DS3231_MATCH_H_M_S);
  }
  if (var == true) {
    al = 0;
    d = 0;
    it = 0;
    post = 0;
  }
}

// Delay senza perdita di velocità
void Delay(int mode) {
  if (mode == 1) {
    if (fer % 3 == 0 && fer >= 275) {
      ta = 250;
    }
    else {
      ta = 130;
    }
    lum(false);
    for (/*null*/; ta >= 0 && digitalRead(3) == LOW; ta--) {
      //if (lum(false) == true && luxmin <= dark + luxtoll && antlam <= stop) {
      //ta = 0;
      //}
      delay(1);
    }
  }
  else if (mode == 2) {
    for (ta = t / sleepmode; ta >= 0 && digitalRead(3) == LOW; ta--) {
      delay(sleepmode);
      if (clock.isAlarm1() && c == 1) {
        suona = true;
      }
      if (Serial.read() == 's') {
        suona = true;
        o1 = dt.hour;
        m1 = dt.minute;
      }
      if ((digitalRead(6) == LOW && light == 0) || (lum(false) == true && antlam <= stop) || millis() - scpu > t - sleepmode) {
        ta = 0;
      }
    }
  }
  else if (mode == 3) {
    for (ta = t; ta > 0; ta--) {
      x = 10 - analogRead(X_pin) / 100;
      y = analogRead(Y_pin) / 100;
      delay(1);
      if (quic == true) {
        if (x >= 7 || x <= 3 || y >= 7 || y <= 3 || digitalRead(SW_pin) == LOW) {
          ta = 0;
        }
      }
      else if (y == 5 && x == 5) {
        quic = true;
      }
    }
  }
}

// Gestione giorni, mesi e anni
int MaxDay(int mese) {
  if (mese == 1 || mese == 3 || mese == 5 || mese == 7 || mese == 8 || mese == 10 || mese == 12) {
    return (31);
  }
  else if (mese == 2) {
    if (bisestile(dt.year)) {
      return (29);
    }
    return (28);
  }
  else {
    return (30);
  }
}
void gset(int year) {
  int an;
  int gior = 0;
  int me;
  for (an = 2000; an < year; an++ ) {
    gior += 365 + bisestile(an);
  }
  for (me = 1; me < dt.month; me++) {
    gior += MaxDay(me);
  }
  gior += dt.day + 4;
  day = gior % 7;
  settind = (gior + 1) / 7;
  settind = settind % 6;
  EEPROM.update(32, settind);
}
boolean bisestile(int year2) {
  if ((year2 % 4 == 0 && year2 % 100 != 0) || year2 % 400 == 0) {
    return true;
  }
  return false;
}

// Lettura e scrittura EEPROM
const int varmax = 71;
void ripristino() {
  int read;
  for (int ind = 0; ind < varmax + 1; ind++) {
    read = EEPROM.read(ind);
    switch (ind) {
      case 0: {
          chiedi = read;
          break;
        }
      case 1: {
          autoback = read;
          break;
        }
      case 2 ... 10: {
          SV[ind - 2] = read;
          break;
        }
      case 11: {
          durwakeup = read * 20;
          break;
        }
      case 12: {
          durlight = read * 20;
          light = durlight;
          break;
        }
      case 13: {
          sleep = read * 200;
          break;
        }
      case 14: {
          fotores = read;
          fotores1 = read;
          break;
        }
      case 15: {
          dark = read;
          break;
        }
      case 16: {
          darkmode = read;
          break;
        }
      case 17: {
          adjustlight = 1;
          break;
        }
      case 18: {
          sleepmode = read * 5;
          break;
        }
      case 19: {
          stop = read;
          break;
        }
      case 20 ... 26: {
          mode[ind - 20] = read - 1;
          break;
        }
      case 27: {
          invo = read;
          break;
        }
      case 28: {
          Inv = read;
          break;
        }
      case 29: {
          sv = read - 1;
          break;
        }
      case 30: {
          Ripeti = read;
          break;
        }
      case 31: {
          luxvel = read;
          break;
        }
      case 32: {
          settind = read;
          Serial.println(read);
          break;
        }
      case 33 ... 67: {
          autoday[(int)((ind - 33) / 7)][(ind - 33) % 7] = read - 1;
          Serial.print(printday[(ind - 33) % 7]);
          Serial.print("  ");
          Serial.println(read - 1);
          break;
        }
      case 68: {
          autodayact = read;
          break;
        }
      case 69: {
          profilo = read;
          break;
        }
      case 70: {
          luxtoll = read;
          break;
        }
      case 71: {
          adstdby = read;
          break;
        }
      default: {
          break;
        }
    }
  }
  abclean();
  o1 = SV[sv * 2 - 2];
  m1 = SV[sv * 2 - 1];
  Clear(true, false);
}
void backup() {
  int read;
  //Serial.println("Backup...");
  for (int ind = 0; ind < varmax + 1; ind++) {
    switch (ind) {
      case 0: {
          read = chiedi;
          break;
        }
      case 1: {
          read = autoback;
          break;
        }
      case 2 ... 10: {
          read = SV[ind - 2];
          break;
        }
      case 11: {
          read = durwakeup / 20;
          break;
        }
      case 12: {
          read = durlight / 20;
          break;
        }
      case 13: {
          read = sleep / 200;
          break;
        }
      case 14: {
          read = fotores;
          break;
        }
      case 15: {
          read = dark;
          break;
        }
      case 16: {
          read = darkmode;
          break;
        }
      case 17: {
          read = adjustlight;
          break;
        }
      case 18: {
          read = sleepmode / 5;
          break;
        }
      case 19: {
          read = stop;
          break;
        }
      case 20 ... 26: {
          read = mode[ind - 20] + 1;
          break;
        }
      case 27: {
          read = invo;
          break;
        }
      case 28: {
          read = Inv;
          break;
        }
      case 29: {
          read = sv + 1;
          break;
        }
      case 30: {
          read = Ripeti;
          break;
        }
      case 31: {
          read = luxvel;
          break;
        }
      case 32: {
          ind = 67;
          break;
        }
      case 68: {
          read = autodayact;
          break;
        }
      case 69: {
          read = profilo;
          break;
        }
      case 70: {
          read = luxtoll;
          break;
        }
      case 71: {
          read = adstdby;
          break;
        }
      default: {
          break;
        }
    }
    EEPROM.update(ind, read);
  }
  //Serial.println("Fine backup...");
  abclean();
}

// Pulizia cambiamenti variabili
void abclean() {
  for (r = 0; r < 8; r++) {
    for (q = 0; q < 8; q++) {
      autobackup[r][q] = 0;
    }
  }
}

// Conto variabili cambiate
int rilcamb() {
  int count = 0;
  for (r = 1; r < 9; r++) {
    for (q = 0; q < 8; q++) {
      if (autobackup[r][q] == 1) {
        count = count + 1;
      }
    }
  }
  return count;
}

//Sensore di luce avanzato
void setluxeq() {
  int lux = analogRead(A3);
  luxmin = lux;
  maxlux1 = lux;
  for (a = 0; a < maxlung; a++) {
    luxarray[a] = lux;
  }
}
void setluxmin() {
  for (a = 0; a < luxvel; a++) {
    if (luxarray[a] < luxmin) {
      luxmin = luxarray[a];
    }
  }
}
int diff = 0;
boolean lum(boolean prec) {
  if (prec == true) {
    for (a = luxvel; a >= 0; a--) {
      luxarray[a + 1] = luxarray[a];
      //Serial.print(luxarray[a + 1]);
      //Serial.print("\t");
    }
    //Serial.println("");
    luxarray[0] = maxlux1;


    if (light % 5 == 0) {
      lcd.setCursor(12, 1);
      if (maxlux1 < 100) {
        lcd.print(0);
        if (maxlux1 < 10) {
          lcd.print(0);
        }
      }
      lcd.print(maxlux1);
    }


    diff = luxarray[0] - luxmin;
    if (luxarray[0] < luxmin) {
      luxmin = luxarray[0];
    }
    else if (luxarray[luxvel + 1] == luxmin) {
      setluxmin();
    }
    maxlux1 = 0;
  }
  else {
    if (analogRead(A3) > maxlux1) {
      maxlux1 = analogRead(A3);
      diff = maxlux1 - luxmin;
    }
  }
  if (diff > fotores) {
    return true;
  }
  return false;
}

// Gestione sveglie
void stampasv(int sv) {
  int o = 0;
  int m = 0;
  if (sv == 1) {
    o = o1;
    m = m1;
  }
  else {
    o = o2;
    m = m2;
  }
  if (o < 10) {
    lcd.print(0);
  }
  lcd.print(o);
  lcd.print(":");
  if (m < 10) {
    lcd.print(0);
  }
  lcd.print(m);
}
void svdomani() {
  cal = (day + 1) % 7;
  o2 = SV[mode[cal] * 2 - 2];
  m2 = SV[mode[cal] * 2 - 1];
}
void svoggi() {
  sv = mode[day];
}
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
      suona = true;
    }
    else {
      inputString += inChar;
    }
  }
}
