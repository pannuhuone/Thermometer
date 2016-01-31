#ifndef main_h
#define main_h

#define PHOTON_PREFIX_1       "Nextion_" // Prefix for sensor

const char * daysOfWeek_en[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const char * daysOfWeek_fi[7] = {"Maanantai", "Tiistai", "Keskiviikko", "Torstai", "Perjantai", "Lauantai", "Sunnuntai"};

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
