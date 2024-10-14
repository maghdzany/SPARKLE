#include "Relay.h"
#include "config.h"
#include "Storage.h"
#include <ArduinoJson.h>

void Relay::init()
{
    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);
    pinMode(RELAY_3, OUTPUT);
    pinMode(RELAY_4, OUTPUT);

    // Check and set default labels if not present
    for (int i = 1; i <= 4; i++)
    {
        String label = getRelayLabel(i);
        if (label.isEmpty())
        {
            saveRelayLabel(i, "Relay" + String(i));
        }
    }

    // Check and set default states if not present
    for (int i = 1; i <= 4; i++)
    {
        if (Storage::getData(getRelayStateKey(i), -1) == -1)
        {
            saveRelayState(i, 0);
        }
    }

    // Check and set default durations if not present
    for (int i = 1; i <= 4; i++)
    {
        if (Storage::getData(getRelayDurationKey(i), 0) == 0)
        {
            saveRelayDuration(i, RELAY_TIME);
        }
    }

    // Set initial relay states
    digitalWrite(RELAY_1, getRelayState(1) ? HIGH : LOW);
    digitalWrite(RELAY_2, getRelayState(2) ? HIGH : LOW);
    digitalWrite(RELAY_3, getRelayState(3) ? HIGH : LOW);
    digitalWrite(RELAY_4, getRelayState(4) ? HIGH : LOW);
}

void Relay::relayOn(uint8_t relayNumber)
{
    digitalWrite(getRelayPin(relayNumber), HIGH);
    saveRelayState(relayNumber, 1);
    Serial.print("Relay ");
    Serial.print(relayNumber);
    Serial.println(" ON");
}

void Relay::relayOff(uint8_t relayNumber)
{
    digitalWrite(getRelayPin(relayNumber), LOW);
    saveRelayState(relayNumber, 0);
    Serial.print("Relay ");
    Serial.print(relayNumber);
    Serial.println(" OFF");
}

unsigned long Relay::relayTimers[4] = {0, 0, 0, 0};

void Relay::relayOnWithDuration(uint8_t relayNumber, unsigned long duration)
{
    relayOn(relayNumber);
    relayTimers[relayNumber - 1] = millis() + (duration * 1000); // Convert seconds to milliseconds
}

void Relay::checkRelayTimers()
{
    unsigned long currentTime = millis();
    for (int i = 0; i < 4; i++)
    {
        if (relayTimers[i] > 0 && currentTime >= relayTimers[i])
        {
            relayOff(i + 1);
            relayTimers[i] = 0;
        }
    }
}

void Relay::loop()
{
    checkRelayTimers();
}

void Relay::saveRelayState(uint8_t relayNumber, int state)
{
    Storage::saveData(getRelayStateKey(relayNumber), state);
}

int Relay::getRelayState(uint8_t relayNumber)
{
    return Storage::getData(getRelayStateKey(relayNumber), 0);
}

void Relay::saveRelayDuration(uint8_t relayNumber, unsigned long duration)
{
    if (relayNumber >= 1 && relayNumber <= 4)
    {
        const char* key = getRelayDurationKey(relayNumber);
        Storage::saveData(key, static_cast<int32_t>(duration));
    }
}

unsigned long Relay::getRelayDuration(uint8_t relayNumber)
{
    if (relayNumber >= 1 && relayNumber <= 4)
    {
        const char* key = getRelayDurationKey(relayNumber);
        return static_cast<unsigned long>(Storage::getData(key, RELAY_TIME));
    }
    return RELAY_TIME;
}

void Relay::saveRelayLabel(uint8_t relayNumber, const String &label)
{
    if (relayNumber >= 1 && relayNumber <= 4)
    {
        String key = "relay_label_" + String(relayNumber);
        Storage::saveStringData(key.c_str(), label.c_str());
    }
}

String Relay::getRelayLabel(uint8_t relayNumber)
{
    if (relayNumber >= 1 && relayNumber <= 4)
    {
        String key = "relay_label_" + String(relayNumber);
        String defaultLabel = "Relay " + String(relayNumber);
        return Storage::getStringData(key.c_str(), defaultLabel.c_str());
    }
    return "Unknown";
}

String Relay::getAllRelayDataJson()
{
    JsonDocument doc;
    JsonArray relayArray = doc.to<JsonArray>();

    for (uint8_t i = 1; i <= 4; i++)
    {
        JsonObject relayObj = relayArray.add<JsonObject>();
        relayObj["number"] = i;
        relayObj["state"] = getRelayState(i);
        relayObj["duration"] = getRelayDuration(i);
        relayObj["label"] = getRelayLabel(i);
    }

    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

const char *Relay::getRelayStateKey(uint8_t relayNumber)
{
    static char key[12];
    snprintf(key, sizeof(key), "relay_state_%d", relayNumber);
    return key;
}

const char* Relay::getRelayDurationKey(uint8_t relayNumber)
{
    static char key[15];
    snprintf(key, sizeof(key), "relay_dur_%d", relayNumber);
    return key;
}

const char *Relay::getRelayLabelKey(uint8_t relayNumber)
{
    static char key[12];
    snprintf(key, sizeof(key), "relay_label_%d", relayNumber);
    return key;
}

uint8_t Relay::getRelayPin(uint8_t relayNumber)
{
    switch (relayNumber)
    {
    case 1:
        return RELAY_1;
    case 2:
        return RELAY_2;
    case 3:
        return RELAY_3;
    case 4:
        return RELAY_4;
    default:
        return 0;
    }
}