#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

extern const char *WIFI_SSID;
extern const char *WIFI_PASSWORD;
extern const char *NTP_SERVER;
extern const long GMT_OFFSET_SEC;
extern const int DAYLIGHT_OFFSET_SEC;
extern const int LED_PIN;
extern const int RX_AUDIO;
extern const int TX_AUDIO;
extern const int DEFAULT_VOLUME;
extern const uint8_t DEFAULT_EQUALIZER;
extern const unsigned long RELAY_TIME;
extern const uint8_t RELAY_1;
extern const uint8_t RELAY_2;
extern const uint8_t RELAY_3;
extern const uint8_t RELAY_4;
extern const uint8_t DEFAULT_RELAY_STATE;

#endif // CONFIG_H