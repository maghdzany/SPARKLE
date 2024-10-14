#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "Storage.h"
#include "TimeManager.h"
#include "AlarmManager.h"
#include "WebServer.h"
#include "AudioManager.h"
#include "Relay.h"

Storage storage;

unsigned long lastAudioCheck = 0;
const unsigned long audioCheckInterval = 5000;

// unsigned long lastCheckTime = 0;
// const unsigned long CHECK_INTERVAL = 1000;

void setup()
{
    Serial.begin(115200);

    Storage::init();
    AudioManager::init();
    TimeManager::init();
    AlarmManager::init();
    Relay::init();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    WebServer::initializeServer();
}

void loop()
{
    AlarmManager::checkAndTriggerAlarms();
    Relay::loop();
    //     unsigned long currentTime = millis();

    //   // Check every second
    //   if (currentTime - lastCheckTime >= CHECK_INTERVAL) {
    //     lastCheckTime = currentTime;

    //     // Check and update volume
    //     uint8_t storedVolume = storage.getGlobalVolume();
    //     uint8_t currentVolume = AudioManager::readVolume();

    //     if (storedVolume != currentVolume) {
    //       Serial.printf("Volume mismatch. Stored: %d, Current: %d. Updating...\n", storedVolume, currentVolume);
    //       AudioManager::handleVolume(storedVolume);
    //     }

    //     // Check and update equalizer
    //     uint8_t storedEqualizer = storage.getGlobalEqualizer();
    //     uint8_t currentEqualizer = AudioManager::readEqualizer();

    //     if (storedEqualizer != currentEqualizer) {
    //       Serial.printf("Equalizer mismatch. Stored: %d, Current: %d. Updating...\n", storedEqualizer, currentEqualizer);
    //       AudioManager::handleEqualizer(storedEqualizer);
    //     }
    //   }
}