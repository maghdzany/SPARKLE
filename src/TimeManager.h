#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>
#include "config.h"

class TimeManager {
public:
    static void initializeTime();
    static String getCurrentTimeString();
    static String getCurrentDayString();
    static bool isAlarmTimeMatching(const String& alarmTime, const String& alarmDays);
    static String getTimeJsonString();
};

#endif // TIME_MANAGER_H