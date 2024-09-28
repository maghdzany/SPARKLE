#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "Storage.h"
#include "TimeManager.h"
#include "AlarmManager.h"
#include "WebServer.h"

void setup() {
    Serial.begin(115200);

    Storage::init();
    TimeManager::initializeTime();
    AlarmManager::initializeAlarmSystem();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    WebServer::initializeServer();
}

void loop() {
    AlarmManager::checkAndTriggerAlarms();
    delay(1000);  // Check every second
}