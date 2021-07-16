//#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include "images.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

#include "RTClib.h"
RTC_DS3231 rtc;

//RTC
#define clock_interrupt 2
DateTime now;

#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#define DHTPIN 7
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

//EEPROM
#define EEPROM_used 1

//Buttons
#define button_up 3
#define button_confirm 4
#define button_down 5
byte scrolling_time = 10;
byte bouncing_time = 45;
unsigned long int last_millis;
unsigned long int millis_gap;
enum buttons {
  up,
  confirm,
  down
};
int buttonPressed;
int previousButton;
int triggButton = -1;


//Oled
bool orientation;
byte n_rows;
enum alignment {
  left,
  right,
  center
};
enum interfaces {
  back = -1,
  displayInter,
  buttonsInter,
  //////////////////// Don't touch them, add interfaces only above
  homeInter,
  commandInter,
  wifiInter,
  settingsInter,
  questionInter
  ///////////////////
};

typedef struct {
  byte font;
  byte x;
  byte y;
  String data;
} elements;
elements element[10];

typedef struct {
  byte type;
  byte x;
  byte y;
  byte height;
  byte width;
} special_elements;
special_elements special_element[10];

enum special_element_types {
  rect,
  circle,
  filledCircle,
  rectangle,
  filledRectangle,
  roundRectangle,
  filledRoundRectangle
};

typedef struct {
  byte type;
  byte x;
  byte y;
  byte ref;
} icon_elements;
icon_elements icon_element[10];

struct parameters{
  int address;
  int data = -1;
  int min;
  int max;
};
parameters parameter;

bool details_list = false;
typedef struct {
  byte type;
  int data;
} details_element_list;
details_element_list details_elements_list[20];

enum details_element_types{
  empty,
  txt,
  image
};

int element_counter = 0;
int special_element_counter = 0;
int icon_element_counter = 0;
int interface;
int loaded_interface;
int previous_interface;
int history_interface[5];
bool oled_updated = false;
String elements_list[20];
bool title_list;
int begin_list;
int dialog_interface;

//Timers
unsigned long int millis_time;
unsigned int timer_track;
int prescaler;
int timer_trigg;
bool timer_need;
