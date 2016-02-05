#ifndef main_h
#define main_h

#include "application.h"

#define PHOTON_PREFIX_1       "Nextion_" // Prefix for sensor

// forecast.io API
#define HOOK_RESP	"hook-response/forecastio_webhook/0"
#define HOOK_PUB	"forecastio_webhook"

// Timezone
const int TIMEZONE_OFFSET = 2;

// Display brightness
const int DISPLAY_BRIGHTNESS = 50;

// Weekdays for languages
const char * daysOfWeek_en[8] = {"", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char * daysOfWeek_fi[8] = {"", "Sunnuntai", "Maanantai", "Tiistai", "Keskiviikko", "Torstai", "Perjantai", "Lauantai"};

// Screens
const int HOME_SCREEN = 0;
const int SETTINGS_SCREEN = 1;
const int ABOUT_SCREEN = 2;
const int BOOT_SCREEN = 3; // Not in use at the moment
const int SECOND_SCREEN = 4;

// Sleep states
enum {
  STATE_AWAKE,
  STATE_DIM_SCREEN,
  STATE_SCREEN_OFF
};

// Weather states
enum {
  WEATHER_READY,
  WEATHER_REQUESTING,
  WEATHER_AVAILABLE
};

/* Weather icons from forecast.io */
/* Name mapped to Nextion picture ID */
enum {
  CLEAR_DAY_LIGHT=30,
  CLEAR_NIGHT_LIGHT=32,
  RAIN_LIGHT=34,
  SNOW_LIGHT=28,
  SLEET_LIGHT=36,
  WIND_LIGHT=38,
  FOG_LIGHT=40,
  CLOUDY_LIGHT=42,
  PARTLY_CLOUDY_DAY_LIGHT=26,
  PARTLY_CLOUDY_NIGHT_LIGHT=44,
  CLEAR_DAY_DARK=29,
  CLEAR_NIGHT_DARK=31,
  RAIN_DARK=33,
  SNOW_DARK=27,
  SLEET_DARK=35,
  WIND_DARK=37,
  FOG_DARK=39,
  CLOUDY_DARK=41,
  PARTLY_CLOUDY_DAY_DARK=25,
  PARTLY_CLOUDY_NIGHT_DARK=43
};

// Weather data store
typedef struct {
  String summ;
  int weekday;
  int icon;
  int minTemp;
  int maxTemp;
} WeatherData;

/* Struct for refreshing screens
typedef struct {
 String element;
 float value;
} ScreenRefreshData;*/

#endif
