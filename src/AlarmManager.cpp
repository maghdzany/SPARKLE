#include "AlarmManager.h"
#include "config.h"

unsigned long AlarmManager::alarmStartTime = 0;
bool AlarmManager::isAlarmActive = false;

void AlarmManager::initializeAlarmSystem() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void AlarmManager::checkAndTriggerAlarms() {
    if (isAlarmActive) {
        if (millis() - alarmStartTime >= 10000) {  // 10 seconds
            stopAlarm();
            return;
        }
    }

    String alarms = Storage::getData("alarmData");
    JsonDocument doc;
    deserializeJson(doc, alarms);

    String currentTime = TimeManager::getCurrentTimeString();
    String currentDay = TimeManager::getCurrentDayString();

    for (JsonObject alarm : doc.as<JsonArray>()) {
        if (TimeManager::isAlarmTimeMatching(alarm["time"], alarm["repeat"])) {
            if (!isAlarmActive) {
                triggerAlarm();
            }
            return;
        }
    }
}

String AlarmManager::addNewAlarm(const String& newAlarmJson) {
    String existingAlarms = Storage::getData("alarmData");
    String updatedAlarms = Storage::addAlarm(existingAlarms, newAlarmJson);
    Storage::saveData("alarmData", updatedAlarms);
    return updatedAlarms;
}

String AlarmManager::removeAlarmById(int id) {
    String existingAlarms = Storage::getData("alarmData");
    String updatedAlarms = Storage::removeAlarmById(existingAlarms, id);
    Storage::saveData("alarmData", updatedAlarms);
    return updatedAlarms;
}

String AlarmManager::getAllAlarmsJson() {
    return Storage::getData("alarmData");
}

void AlarmManager::clearAllAlarms() {
    Storage::deleteData("alarmData");
}

void AlarmManager::triggerAlarm() {
    digitalWrite(LED_PIN, HIGH);
    alarmStartTime = millis();
    isAlarmActive = true;

    String alarms = Storage::getData("alarmData");
    JsonDocument doc;
    deserializeJson(doc, alarms);

    for (JsonObject alarm : doc.as<JsonArray>()) {
        if (TimeManager::isAlarmTimeMatching(alarm["time"], alarm["repeat"])) {
            alarm["active"] = true; // Set active to true
            alarm["last_triggered"] = TimeManager::getCurrentTimeString(); // Update last triggered time
        }
    }

    String updatedAlarms;
    serializeJson(doc, updatedAlarms);
    Storage::saveData("alarmData", updatedAlarms);
    Serial.println("Alarm triggered!");
}

void AlarmManager::stopAlarm() {
    digitalWrite(LED_PIN, LOW);
    isAlarmActive = false;

    String alarms = Storage::getData("alarmData");
    JsonDocument doc;
    deserializeJson(doc, alarms);

    for (JsonObject alarm : doc.as<JsonArray>()) {
        alarm["active"] = false; // Set active to false
    }

    String updatedAlarms;
    serializeJson(doc, updatedAlarms);
    Storage::saveData("alarmData", updatedAlarms);
    Serial.println("Alarm stopped!");
}