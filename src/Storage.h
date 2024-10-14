#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <nvs_flash.h>
#include <nvs.h>

class Storage {
public:
    static void init();
    static void saveData(const char* key, int32_t value);
    static int32_t getData(const char* key, int32_t defaultValue);
    static void clearData(const char* key);
    static String addAlarm(const String& existingJson, const String& newJson);
    static String removeAlarmById(const String& existingJson, int id);
    static void setGlobalVolume(uint8_t volume);
    static uint8_t getGlobalVolume();
    static void setGlobalEqualizer(uint8_t equalizer);
    static uint8_t getGlobalEqualizer();
    static String getRingtoneList();
    static void saveStringData(const char* key, const char* value);
    static String getStringData(const char* key, const char* defaultValue);
    static String listAllData();

};

#endif // STORAGE_H