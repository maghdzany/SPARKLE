#ifndef ALARM_MANAGER_H
#define ALARM_MANAGER_H

#include <Arduino.h>
#include "Storage.h"
#include "TimeManager.h"
#include <ArduinoJson.h>

class AlarmManager {
public:
    static void initializeAlarmSystem();
    static void checkAndTriggerAlarms();
    static String addNewAlarm(const String& newAlarmJson);
    static String removeAlarmById(int id);
    static String getAllAlarmsJson();
    static void clearAllAlarms();

private:
    static void triggerAlarm();
    static void stopAlarm();
    static unsigned long alarmStartTime;
    static bool isAlarmActive;
};

#endif // ALARM_MANAGER_H