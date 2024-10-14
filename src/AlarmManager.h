#ifndef ALARM_MANAGER_H
#define ALARM_MANAGER_H

#include <Arduino.h>
#include "Storage.h"
#include "TimeManager.h"
#include <ArduinoJson.h>
#include "config.h"
#include "AudioManager.h"

class AlarmManager
{
public:
    static void init();
    static void checkAndTriggerAlarms();
    static String addNewAlarm(const String &newAlarmJson);
    static String removeAlarmById(int id);
    static String getAllAlarmsJson();
    static void clearAllAlarms();
    static void triggerAlarm(int ringtoneNumber, uint8_t relays);
    static void stopAlarm();
    static String updateAlarm(int id, const String &updatedAlarmJson);
    static bool toggleAlarm(int id, bool active);
    struct Alarm
    {
        int id;
        bool active;
        String label;
        String time;
        String repeat;
        uint8_t relays; // Bitfield untuk menyimpan relay yang aktif
        int ringtone;
        String last_triggered;
    };

private:
    static bool isAlarmActive;
    static unsigned long alarmStartTime;
    static const int LED_PIN = 2;
    static const int RELAY_TIME = 60;
    static String alarmData;

    static void loadAlarmData();
    static void saveAlarmData();
    static String addAlarm(const String &existingJson, const String &newJson);
    static String removeAlarmByIdHelper(const String &existingJson, int id);
};

#endif // ALARM_MANAGER_H