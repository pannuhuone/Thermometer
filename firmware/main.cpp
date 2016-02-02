/*
* FILE:        main.cpp
* PURPOSE:     Nextion touch screen controller
* LICENSE:     GPL v3 (http://www.gnu.org/licenses/gpl.html)
*
* Decription:
* TBD
*
* Short descrition:
* TBD
*
* Teemu Kulma teemu.kulma@iki.fi
*/

#include "main.h"
#include "Nextion.h"

// EEPROM
// Address 0 = 117 if values have been saved
// Address 1 = 0/1 for language (0: English, 1: Finnish)
// Address 1 = 0/1 for temperature scale (0: Celsius, 1: Fahrenheit)
int8_t langCode = 0;
int8_t tempScale = 0;

// Current values
int currentPage = HOME_SCREEN;
float currentOutsideTemperatureC = 0.0;
float currentOutsideHumidity = 0.0;

// Time / date variables
int currentWeekday = 0;

/* Declare a text objects [page id:0,component id:1, component name: "t0"]. */
/* Home screen */
NexPage home = NexPage(0, 0, "home");
NexText t0 = NexText(0, 4, "t0");
NexText t1 = NexText(0, 5, "t1");
NexText t2 = NexText(0, 6, "t2");
NexText t3 = NexText(0, 7, "t3");
NexText t4 = NexText(0, 8, "t4");
NexText t5 = NexText(0, 9, "t5");
NexText t6 = NexText(0, 10, "t6");
NexText t7 = NexText(0, 11, "t7");
NexText t8 = NexText(0, 12, "t8");
NexText t10 = NexText(0, 14, "t10");
NexText t12 = NexText(0, 16, "t12");
NexText t13 = NexText(0, 17, "t13");
NexText t14 = NexText(0, 18, "t14");
NexText t15 = NexText(0, 19, "t15");
NexText t16 = NexText(0, 20, "t16");
NexText t17 = NexText(0, 21, "t17");
NexText t18 = NexText(0, 22, "t18");
NexText t19 = NexText(0, 23, "t19");
NexText t20 = NexText(0, 24, "t20");
NexText t21 = NexText(0, 25, "t21");
NexText t22 = NexText(0, 26, "t22");
NexText t23 = NexText(0, 27, "t23");
NexButton b0 = NexButton(0, 3, "b0");
NexButton b1 = NexButton(0, 2, "b1");
NexButton b2 = NexButton(0, 1, "b2");

/* Settings screen */
NexPage settings = NexPage(1, 0, "settings");
NexText tx0 = NexText(1, 4, "tx0");
NexText tx1 = NexText(1, 5, "tx1");
NexDSButton bt0 = NexDSButton(1, 6, "bt0");
NexDSButton bt1 = NexDSButton(1, 7, "bt1");
NexButton n0 = NexButton(1, 1, "n0");
NexButton n1 = NexButton(1, 3, "n1");

/* About page */
NexPage about = NexPage(2, 0, "about");
NexButton bu0 = NexButton(2, 2, "bu0");

/* Second page */
NexPage second = NexPage(4, 0, "second");
NexText d0 = NexText(4, 3, "d0");
NexText d2 = NexText(4, 5, "d2");
NexText d4 = NexText(4, 7, "d4");
NexText d6 = NexText(4, 9, "d6");
NexButton u0 = NexButton(4, 11, "u0");

/* Register a button object to the touch event list. */
NexTouch *nex_listen_list[] =
{
    &b0, &b1, &b2,
    &bt0, &bt1,
    &n0, &n1,
    &bu0,
    &u0,
    NULL
};

/* Write Location to the home screen */
void writeLocation()
{
  dbSerialPrintln("writeLocation");
  dbSerialPrintln("Koivukehä");
  t2.setText("Koivukehä");
}

/* ********** SCREEN RENDER FUNCTIONS ********** */
/* ********************************************* */

/* Rendering home screen */
void renderHomeScreen() {
  dbSerialPrintln("renderHomeScreen");
  writeLocation();

  // Render outside temperature
  char bufTemp[10];
  if(tempScale == 0)
    sprintf(bufTemp, "%.1f", currentOutsideTemperatureC);
  else {
    sprintf(bufTemp, "%.1f", currentOutsideTemperatureC * 1.8 + 32); // Celsius to Fahrenheit conversion
    dbSerialPrint("Temp in F: ");
    dbSerialPrintln(bufTemp);
  }
  t0.setText(bufTemp);

  // Render outside humidity
  char bufHumid[10];;
  sprintf(bufHumid, "%.1f", currentOutsideHumidity);
  t8.setText(bufHumid);

  // Render correct temperature scale based on the selection
  if(tempScale == 0) {
    t1.setText("°C");
    t4.setText("°C");
    t13.setText("°C");
    t15.setText("°C");
    t17.setText("°C");
    t19.setText("°C");
    t21.setText("°C");
    t23.setText("°C");
  }
  else {
    t1.setText("F");
    t4.setText("F");
    t13.setText("F");
    t15.setText("F");
    t17.setText("F");
    t19.setText("F");
    t21.setText("F");
    t23.setText("F");
  }

  // Render days of week for forecast
  dbSerialPrint("Time: ");
  dbSerialPrint(Time.hour());
  dbSerialPrint(":");
  dbSerialPrintln(Time.minute());
  dbSerialPrint("Day of week: ");
  dbSerialPrintln(Time.weekday());
  // If language selection is english
  if(langCode==0) {
    t5.setText(daysOfWeek_en[currentWeekday]);
    t6.setText(daysOfWeek_en[currentWeekday + 1]);
    t7.setText(daysOfWeek_en[currentWeekday + 2]);
  }
  // If language selection is finnish
  if(langCode==1) {
    t5.setText(daysOfWeek_fi[currentWeekday]);
    t6.setText(daysOfWeek_fi[currentWeekday + 1]);
    t7.setText(daysOfWeek_fi[currentWeekday + 2]);
  }
}

/* Rendering settings screen */
void renderSettingsScreen() {
  // Set dualbutton states as saved.
  bt0.setValue((uint32_t)langCode);
  bt1.setValue((uint32_t)tempScale);
}

/* Refreshing part of the screen items */
void refreshScreen(int screen) {
  dbSerialPrintln("refreshScreen");
  switch(screen) {
    case HOME_SCREEN:
    /* Refresh outside temporary */
    char bufTemp[10];
    if(tempScale == 0)
      sprintf(bufTemp, "%.1f", currentOutsideTemperatureC);
    else
      sprintf(bufTemp, "%.1f", currentOutsideTemperatureC * 1.8 + 32); // Celsius to Fahrenheit conversion
    t0.setText(bufTemp);
    /* Refresh outside humidity */
    char bufHumid[10];;
    sprintf(bufHumid, "%.1f", currentOutsideHumidity);
    t8.setText(bufHumid);
    break;
    case SECOND_SCREEN:
    /* TBD */
    break;
  }
}

/* Forwarding to correct screen render function. */
void renderScreen(int screenNum) {
  dbSerialPrintln("renderScreen");

  switch(screenNum) {
    case HOME_SCREEN:
    dbSerialPrintln("HOME_SCREEN");
    currentPage = HOME_SCREEN;
    home.show();
    renderHomeScreen();
    break;
    case SETTINGS_SCREEN:
    dbSerialPrintln("SETTINGS_SCREEN");
    currentPage = SETTINGS_SCREEN;
    settings.show();
    renderSettingsScreen();
    break;
    case ABOUT_SCREEN:
    dbSerialPrintln("ABOUT_SCREEN");
    currentPage = ABOUT_SCREEN;
    about.show();
    break;
    case SECOND_SCREEN:
    dbSerialPrintln("SECOND_SCREEN");
    currentPage = SECOND_SCREEN;
    second.show();
    break;
    default:
    dbSerialPrintln("DEFAULT");
    currentPage = HOME_SCREEN;
    home.show();
    renderHomeScreen();
    break;
  }
}

/* ****** BUTTON SELECTION FUNCTIONS ******* */
/* ***************************************** */
void b0PopCallback(void *ptr) {
  dbSerialPrintln("b0PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);

  renderScreen(SECOND_SCREEN);
}

void b1PopCallback(void *ptr) {
  dbSerialPrintln("b1PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);

  // History page TBD!
}

void b2PopCallback(void *ptr) {
  dbSerialPrintln("b2PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);

  renderScreen(SETTINGS_SCREEN);
}

void bt0PopCallback(void *ptr)
{
  uint32_t dual_state;
  dbSerialPrintln("bt0PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);

  // EEPROM
  // Address 1 = 0/1 for language (0: English, 1: Finnish)
  bt0.getValue(&dual_state);
  if(dual_state) {
    dbSerialPrintln("Language: FI");
    langCode = 1;
  }
  else {
    dbSerialPrintln("Language: EN");
    langCode = 0;
  }

  int8_t eepromLang = EEPROM.read(1);
  if(langCode != eepromLang) {
    dbSerialPrint("Writing to EEPROM! Value: ");
    dbSerialPrintln(langCode);
    EEPROM.write(1, langCode);
  }
}

void bt1PopCallback(void *ptr)
{
  uint32_t dual_state;
  dbSerialPrintln("bt1PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);

  // EEPROM
  // Address 1 = 0/1 for temperature scale (0: Celsius, 1: Fahrenheit)
  bt1.getValue(&dual_state);
  if(dual_state) {
    dbSerialPrintln("Scale: F");
    tempScale = 1;
  }
  else {
    dbSerialPrintln("Scale: °C");
    tempScale = 0;
  }

  int8_t eepromScale = EEPROM.read(2);
  if(tempScale != eepromScale) {
    dbSerialPrint("Writing to EEPROM! Value: ");
    dbSerialPrintln(tempScale);
    EEPROM.write(2, tempScale);
  }
}

void n0PopCallback(void *ptr)
{
  dbSerialPrintln("n0PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);

  renderScreen(HOME_SCREEN);
}

void n1PopCallback(void *ptr)
{
  dbSerialPrintln("n1PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);

  renderScreen(ABOUT_SCREEN);
}

void bu0PopCallback(void *ptr)
{
  dbSerialPrintln("bu0PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);

  renderScreen(SETTINGS_SCREEN);
}

void u0PopCallback(void *ptr)
{
  dbSerialPrintln("u0PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);

  renderScreen(HOME_SCREEN);
}

/* TBD */
void dataHandler(const char *event, const char *data)
{
  dbSerialPrintln("dataHandler");

  if (data) {
    if ((String)event == "Outside_Temperature")
    {
      float fTemp = atof(data);

      if(fTemp != currentOutsideTemperatureC) {
        currentOutsideTemperatureC = fTemp;
        refreshScreen(currentPage);
      }
    }

    if((String)event == "Outside_Humidity")
    {
      float fHumid = atof(data);

      if(fHumid != currentOutsideHumidity) {
        currentOutsideHumidity = fHumid;
        refreshScreen(currentPage);
      }
    }
  }
  else
    dbSerialPrintln("NULL");
}

/* ******************************** */
/* ************* SETUP ************ */
/* ******************************** */

void setup() {
  Serial.begin(9600);

  Particle.subscribe("Outside_Temperature", dataHandler, MY_DEVICES);
  Particle.subscribe("Outside_Humidity", dataHandler, MY_DEVICES);

  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  nexInit();

  /* Register the pop event callback functions for the button components. */
  b0.attachPop(b0PopCallback);
  b1.attachPop(b1PopCallback);
  b2.attachPop(b2PopCallback);
  bt0.attachPop(bt0PopCallback, &bt0);
  bt1.attachPop(bt1PopCallback, &bt1);
  n0.attachPop(n0PopCallback);
  n1.attachPop(n1PopCallback);
  bu0.attachPop(bu0PopCallback);
  u0.attachPop(u0PopCallback);

  // See if this EEPROM has saved data
  if(EEPROM.read(0)==117) {
    // Set language
    if(EEPROM.read(1)==1) {
      langCode = 1;
      bt0.setValue((uint32_t)langCode);
    }
    else {
      langCode = 0;
    }
    // Set temperature scale
    if(EEPROM.read(2)==1) {
      tempScale = 1;
      bt1.setValue((uint32_t)tempScale);
    }
    else
      tempScale = 0;
  } else {
        // Initialize
        EEPROM.write(0, 117);
        // Language
        EEPROM.write(1, 0);
        // Temperature scale
        EEPROM.write(2, 0);
    }

  // Set timezone
  Time.zone(TIMEZONE_OFFSET);
  // Set current day of the week
  currentWeekday = Time.weekday();

  renderScreen(HOME_SCREEN);
}


/* ******************************* */
/* ************* LOOP ************ */
/* ******************************* */

void loop() {
  nexLoop(nex_listen_list);

  // Change forecast days of week after midnight
  if(currentWeekday < Time.weekday()) {
    currentWeekday = Time.weekday();
    renderScreen(HOME_SCREEN);
  }
}
