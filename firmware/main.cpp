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

#include "Nextion.h"
#include "application.h"

/*
 * Declare a text objects [page id:0,component id:1, component name: "t0"].
 */
NexText t0 = NexText(0, 1, "t0");
NexText t8 = NexText(0, 2, "t8");


int i = 0;
void myHandler(const char *event, const char *data)
{
  i++;
  //Serial.print(i);
  Serial.print(event);
  Serial.print(", data: ");
  if (data) {
    Serial.println(data);

    if ((String)event == "Outside_Temperature")
      t0.setText(data);
    if((String)event == "Outside_Humidity")
      t8.setText(data);
  }
  else
    Serial.println("NULL");
}

void setup() {
  Serial.begin(9600);

  Particle.subscribe("Outside_Temperature", myHandler, MY_DEVICES);
  Particle.subscribe("Outside_Humidity", myHandler, MY_DEVICES);

  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  nexInit();
}

void loop() {

}
