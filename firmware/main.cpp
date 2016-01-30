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

/* Declare a text objects [page id:0,component id:1, component name: "t0"]. */
NexPage home = NexPage(0, 0, "home");
NexText t0 = NexText(0, 4, "t0");
NexText t2 = NexText(0, 6, "t2");
NexText t3 = NexText(0, 7, "t3");
NexText t5 = NexText(0, 9, "t5");
NexText t6 = NexText(0, 10, "t6");
NexText t7 = NexText(0, 11, "t7");
NexText t8 = NexText(0, 12, "t8");
NexText t10 = NexText(0, 14, "t10");
NexText t12 = NexText(0, 16, "t12");
NexText t14 = NexText(0, 18, "t14");
NexText t16 = NexText(0, 20, "t16");
NexText t18 = NexText(0, 22, "t18");
NexText t20 = NexText(0, 24, "t20");
NexText t22 = NexText(0, 26, "t22");
NexButton b0 = NexButton(0, 3, "b0");
NexButton b1 = NexButton(0, 2, "b1");
NexButton b2 = NexButton(0, 1, "b2");

NexPage settings = NexPage(1, 0, "settings");
NexText tx0 = NexText(1, 4, "tx0");
NexText tx1 = NexText(1, 5, "tx1");
NexDSButton bt0 = NexDSButton(1, 6, "bt0");
NexDSButton bt1 = NexDSButton(1, 7, "bt1");
NexButton n0 = NexButton(1, 1, "n0");
NexButton n1 = NexButton(1, 3, "n1");

NexPage about = NexPage(2, 0, "about");
NexButton bu0 = NexButton(2, 2, "bu0");

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

/* Write Location to the screen */
void writeLocation()
{
  Serial.println("function: writeLocation");

  t2.setText("Koivukehä");
}

/* Button components pop callback functions. */
void b0PopCallback(void *ptr)
{
  Serial.println("b0PopCallback");
  Serial.print("ptr=");
  Serial.println((uint32_t)ptr);

  second.show();
}

void b1PopCallback(void *ptr)
{
  Serial.println("b1PopCallback");
  Serial.print("ptr=");
  Serial.println((uint32_t)ptr);

  // History page TBD!
}

void b2PopCallback(void *ptr)
{
  Serial.println("b2PopCallback");
  Serial.print("ptr=");
  Serial.println((uint32_t)ptr);

  settings.show();
  // Set dualbutton states as saved.
  bt0.setValue((uint32_t)langCode);
  bt1.setValue((uint32_t)tempScale);
}

void bt0PopCallback(void *ptr)
{
  uint32_t dual_state;
  Serial.println("bt0PopCallback");
  Serial.print("ptr=");
  Serial.println((uint32_t)ptr);

  // EEPROM
  // Address 1 = 0/1 for language (0: English, 1: Finnish)
  bt0.getValue(&dual_state);
  if(dual_state) {
    Serial.println("Language: FI");
    langCode = 1;
  }
  else {
    Serial.println("Language: EN");
    langCode = 0;
  }

  int8_t eepromLang = EEPROM.read(1);
  if(langCode != eepromLang) {
    Serial.print("Writing to EEPROM! Value: ");
    Serial.println(langCode);
    EEPROM.write(1, langCode);
  }
}

void bt1PopCallback(void *ptr)
{
  uint32_t dual_state;
  Serial.println("bt1PopCallback");
  Serial.print("ptr=");
  Serial.println((uint32_t)ptr);

  // EEPROM
  // Address 1 = 0/1 for temperature scale (0: Celsius, 1: Fahrenheit)
  bt1.getValue(&dual_state);
  if(dual_state) {
    Serial.println("Scale: F");
    tempScale = 1;
  }
  else {
    Serial.println("Scale: °C");
    tempScale = 0;
  }

  int8_t eepromScale = EEPROM.read(2);
  if(tempScale != eepromScale) {
    Serial.print("Writing to EEPROM! Value: ");
    Serial.println(tempScale);
    EEPROM.write(2, tempScale);
  }
}

void n0PopCallback(void *ptr)
{
  Serial.println("n0PopCallback");
  Serial.print("ptr=");
  Serial.println((uint32_t)ptr);

  home.show();
  writeLocation();
}

void n1PopCallback(void *ptr)
{
  Serial.println("n1PopCallback");
  Serial.print("ptr=");
  Serial.println((uint32_t)ptr);

  about.show();
}

void bu0PopCallback(void *ptr)
{
  Serial.println("bu0PopCallback");
  Serial.print("ptr=");
  Serial.println((uint32_t)ptr);

  settings.show();
  // Set dualbutton values as saved.
  bt0.setValue((uint32_t)langCode);
  bt1.setValue((uint32_t)tempScale);
}

void u0PopCallback(void *ptr)
{
  Serial.println("u0PopCallback");
  Serial.print("ptr=");
  Serial.println((uint32_t)ptr);

  home.show();
  writeLocation();

  /*int addr = 0;
  char tempInChar[32];
  EEPROM.get(addr, tempInChar);
  Serial.print("EEPROM temp: ");
  Serial.println((String)tempInChar);*/
}

/*  */
void myHandler(const char *event, const char *data)
{
  //Serial.println("myHandler");
  //Serial.print(event);
  //Serial.print(", data: ");

  if (data) {
    //Serial.println(data);

    if ((String)event == "Outside_Temperature")
    {
      int addr = 0;
      //EEPROM.put(addr, data);
      t0.setText(data);
    }
    if((String)event == "Outside_Humidity")
    {
      int addr = 1;
      //EEPROM.put(addr, data);
      t8.setText(data);
    }
  }
  /* else
    Serial.println("NULL"); */
}



void setup() {
  Serial.begin(9600);

  Particle.subscribe("Outside_Temperature", myHandler, MY_DEVICES);
  Particle.subscribe("Outside_Humidity", myHandler, MY_DEVICES);

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

  writeLocation();
}

void loop() {
  nexLoop(nex_listen_list);
}
