#include "TimeManager.h"
#include <ArduinoJson.h>

void TimeManager::init() {
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
}

String TimeManager::getCurrentTimeString() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "Failed to obtain time";
    }
    char timeString[9];
    strftime(timeString, sizeof(timeString), "%H:%M:%S", &timeinfo);
    return String(timeString);
}

String TimeManager::getCurrentDayString() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to get local time");
        return "Failed to obtain day";
    }
    char dayString[10];
    strftime(dayString, sizeof(dayString), "%A", &timeinfo);
    return String(dayString);
}

String TimeManager::getTimeJsonString() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to get local time jsonstring");
        return "{\"error\": \"Failed to obtain time\"}";
    }

    JsonDocument doc;
    doc["hour"] = timeinfo.tm_hour;
    doc["minute"] = timeinfo.tm_min;
    doc["second"] = timeinfo.tm_sec;
    doc["day"] = getCurrentDayString();
    doc["date"] = timeinfo.tm_mday;
    doc["month"] = timeinfo.tm_mon + 1;
    doc["year"] = timeinfo.tm_year + 1900;

    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

bool TimeManager::isAlarmTimeMatching(const String& alarmTime, const String& alarmDays) {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return false;
    }

    char currentTimeString[6];
    strftime(currentTimeString, sizeof(currentTimeString), "%H:%M", &timeinfo);

    String currentDay = getCurrentDayString();
    
    return (String(currentTimeString) == alarmTime) && 
           (alarmDays.indexOf(currentDay) != -1) && 
           (timeinfo.tm_sec == 0);  // Hanya cocok pada detik ke-0
}