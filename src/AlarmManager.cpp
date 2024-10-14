#include "AlarmManager.h"
#include "Storage.h"
#include "TimeManager.h"
#include "AudioManager.h"
#include <ArduinoJson.h>
#include "Relay.h"

bool AlarmManager::isAlarmActive = false;
unsigned long AlarmManager::alarmStartTime = 0;
String AlarmManager::alarmData = "[]";

void AlarmManager::init()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    loadAlarmData();
}

void AlarmManager::loadAlarmData()
{
    alarmData = Storage::getStringData("alarmData", "[]");
}

void AlarmManager::saveAlarmData()
{
    Storage::saveStringData("alarmData", alarmData.c_str());
}

void AlarmManager::checkAndTriggerAlarms()
{
    JsonDocument doc;
    deserializeJson(doc, alarmData);

    String currentTime = TimeManager::getCurrentTimeString();
    String currentDay = TimeManager::getCurrentDayString();

    for (JsonObject alarm : doc.as<JsonArray>())
    {
        if (alarm["active"].as<bool>() && TimeManager::isAlarmTimeMatching(alarm["time"], alarm["repeat"]))
        {
            triggerAlarm(alarm["ringtone"].as<int>(), alarm["active_relay"].as<uint8_t>());
            return;
        }
    }
}

String AlarmManager::addNewAlarm(const String &newAlarmJson)
{
    JsonDocument doc;
    deserializeJson(doc, newAlarmJson);
    doc["active_relay"] = doc["active_relay"].as<uint8_t>();

    String updatedNewAlarmJson;
    serializeJson(doc, updatedNewAlarmJson);

    alarmData = addAlarm(alarmData, updatedNewAlarmJson);
    saveAlarmData();
    return alarmData;
}

String AlarmManager::removeAlarmById(int id)
{
    alarmData = removeAlarmByIdHelper(alarmData, id);
    saveAlarmData();
    return alarmData;
}

String AlarmManager::getAllAlarmsJson()
{
    return alarmData;
}

void AlarmManager::clearAllAlarms()
{
    alarmData = "[]";
    saveAlarmData();
}

void AlarmManager::triggerAlarm(int ringtoneNumber, uint8_t activeRelays)
{
    digitalWrite(LED_PIN, HIGH);
    AudioManager::handlePlay(ringtoneNumber);

    // Activate relays
    for (int i = 0; i < 4; i++)
    {
        if (activeRelays & (1 << i))
        {
            unsigned long duration = Relay::getRelayDuration(i + 1);
            Relay::relayOnWithDuration(i + 1, duration);
        }
    }

    isAlarmActive = true;
    alarmStartTime = millis();

    // Update last_triggered time for the matched alarm
    JsonDocument doc;
    deserializeJson(doc, alarmData);

    for (JsonObject alarm : doc.as<JsonArray>())
    {
        if (alarm["active"].as<bool>() && TimeManager::isAlarmTimeMatching(alarm["time"], alarm["repeat"]))
        {
            alarm["last_triggered"] = TimeManager::getCurrentTimeString();
            break;
        }
    }

    serializeJson(doc, alarmData);
    saveAlarmData();
    Serial.println("Alarm triggered!");
}

void AlarmManager::stopAlarm()
{
    digitalWrite(LED_PIN, LOW);
    AudioManager::handleStop();
    isAlarmActive = false;
}

// Helper function to add alarm
String AlarmManager::addAlarm(const String &existingJson, const String &newJson)
{
    JsonDocument doc;
    if (existingJson.length() > 0)
    {
        deserializeJson(doc, existingJson);
    }
    else
    {
        doc.to<JsonArray>();
    }

    JsonDocument newDoc;
    deserializeJson(newDoc, newJson);
    JsonObject newData = newDoc.as<JsonObject>();

    newData["id"] = doc.size() + 1;
    bool isActive = newData["active"];
    newData["last_triggered"] = "";

    JsonObject orderedData = doc.add<JsonObject>();
    orderedData["id"] = newData["id"];
    orderedData["active"] = isActive;
    orderedData["label"] = newData["label"];
    orderedData["time"] = newData["time"];
    orderedData["repeat"] = newData["repeat"];
    orderedData["active_relay"] = newData["active_relay"];
    orderedData["ringtone"] = newData["ringtone"];
    orderedData["last_triggered"] = newData["last_triggered"];

    String result;
    serializeJson(doc, result);
    return result;
}

// Helper function to remove alarm by ID
String AlarmManager::removeAlarmByIdHelper(const String &existingJson, int id)
{
    JsonDocument doc;
    deserializeJson(doc, existingJson);

    JsonArray dataArray = doc.as<JsonArray>();

    for (auto it = dataArray.begin(); it != dataArray.end(); ++it)
    {
        if ((*it)["id"] == id)
        {
            dataArray.remove(it);
            break;
        }
    }

    int newId = 1;
    for (JsonObject obj : dataArray)
    {
        obj["id"] = newId++;
    }

    String result;
    serializeJson(doc, result);
    return result;
}

String AlarmManager::updateAlarm(int id, const String &updatedAlarmJson)
{
    JsonDocument doc;
    deserializeJson(doc, alarmData);

    JsonArray dataArray = doc.as<JsonArray>();
    for (JsonObject alarm : dataArray)
    {
        if (alarm["id"] == id)
        {
            JsonDocument updatedDoc;
            deserializeJson(updatedDoc, updatedAlarmJson);

            // Update all fields except 'id'
            for (JsonPair kv : updatedDoc.as<JsonObject>())
            {
                if (String(kv.key().c_str()) != "id")
                {
                    if (String(kv.key().c_str()) == "active_relay")
                    {
                        alarm[kv.key()] = kv.value().as<uint8_t>();
                    }
                    else
                    {
                        alarm[kv.key()] = kv.value();
                    }
                }
            }

            break;
        }
    }

    serializeJson(doc, alarmData);
    saveAlarmData();
    return alarmData;
}

bool AlarmManager::toggleAlarm(int id, bool active)
{
    JsonDocument doc;
    deserializeJson(doc, alarmData);

    JsonArray dataArray = doc.as<JsonArray>();
    for (JsonObject alarm : dataArray)
    {
        if (alarm["id"] == id)
        {
            alarm["active"] = active;
            serializeJson(doc, alarmData);
            saveAlarmData();
            return true;
        }
    }

    return false;
}