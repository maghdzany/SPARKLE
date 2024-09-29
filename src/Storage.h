#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <nvs_flash.h>
#include <nvs.h>

class Storage {
public:
    static void init();
    static void saveData(const char* key, const String& json);
    static String getData(const char* key);
    static void deleteData(const char* key);
    static String addAlarm(const String& existingJson, const String& newJson);
    static String removeAlarmById(const String& existingJson, int id);
    static void  setGlobalVolume(int volume);
    static int getGlobalVolume();
    static void setDefaultVolume();
};

#endif // STORAGE_H