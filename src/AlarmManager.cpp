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
    Serial.println("Alarm triggered!");
}

void AlarmManager::stopAlarm() {
    digitalWrite(LED_PIN, LOW);
    isAlarmActive = false;
    Serial.println("Alarm stopped!");
}