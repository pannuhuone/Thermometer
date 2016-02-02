#ifndef main_h
#define main_h

#define PHOTON_PREFIX_1       "Nextion_" // Prefix for sensor

// Timezone
const int TIMEZONE_OFFSET = 2;

// Weekdays for languages
const char * daysOfWeek_en[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char * daysOfWeek_fi[7] = {"Sunnuntai", "Maanantai", "Tiistai", "Keskiviikko", "Torstai", "Perjantai", "Lauantai"};

/* Screens */
const int HOME_SCREEN = 0;
const int SETTINGS_SCREEN = 1;
const int ABOUT_SCREEN = 2;
const int BOOT_SCREEN = 3; // Not in use at the moment
const int SECOND_SCREEN = 4;

/* Struct for refreshing screens
typedef struct {
 String element;
 float value;
} ScreenRefreshData;*/

#endif
