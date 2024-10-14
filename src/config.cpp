#include "config.h"

const char* WIFI_SSID = "Sandemo";
const char* WIFI_PASSWORD = "88888888";
const char* NTP_SERVER = "pool.ntp.org";
const long GMT_OFFSET_SEC = 25200;  // GMT+7 for Indonesia
const int DAYLIGHT_OFFSET_SEC = 0;
const int LED_PIN = 2;  // LED pin for alarm output
const int RX_AUDIO = 16;
const int TX_AUDIO = 17;
const int DEFAULT_VOLUME = 10;
const uint8_t DEFAULT_EQUALIZER = 3;  // POP
const unsigned long RELAY_TIME = 5;
const uint8_t RELAY_1 = 18;
const uint8_t RELAY_2 = 19;
const uint8_t RELAY_3 = 21;
const uint8_t RELAY_4 = 22;
const uint8_t DEFAULT_RELAY_STATE = LOW;