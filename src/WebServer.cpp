#include "WebServer.h"
#include <LittleFS.h>
#include "TimeManager.h"
#include "AlarmManager.h"
#include "AudioManager.h"
#include "Storage.h"
#include "Relay.h"

AsyncWebServer WebServer::server(80);

void WebServer::initializeServer()
{
    if (!LittleFS.begin())
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    setupServerRoutes();
    server.begin();
}

void WebServer::setupServerRoutes()
{
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");

    server.onNotFound([](AsyncWebServerRequest *request)
                      {
        if (request->method() == HTTP_OPTIONS) {
            request->send(200);
        } else {
            request->send(404);
        } });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", "text/html"); });

    server.on("/api/time", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String timeJson = TimeManager::getTimeJsonString();
        request->send(200, "application/json", timeJson); });

    server.on("/api/add", HTTP_POST, [](AsyncWebServerRequest *request)
              {
    String label, time, repeat, ringtone;
    bool active = false;
    uint8_t activeRelay = 0;

    if (request->hasParam("label", true)) label = request->getParam("label", true)->value();
    if (request->hasParam("time", true)) time = request->getParam("time", true)->value();
    if (request->hasParam("repeat", true)) repeat = request->getParam("repeat", true)->value();
    if (request->hasParam("ringtone", true)) ringtone = request->getParam("ringtone", true)->value();
    if (request->hasParam("active", true)) active = request->getParam("active", true)->value().equalsIgnoreCase("true");
    if (request->hasParam("active_relay", true)) activeRelay = request->getParam("active_relay", true)->value().toInt();

    // Create the new alarm JSON structure with all fields
    String newEntry = "{\"label\":\"" + label + "\",\"time\":\"" + time + "\",\"repeat\":\"" + repeat + 
                      "\",\"ringtone\":\"" + ringtone + "\",\"active\":" + (active ? "true" : "false") + 
                      ",\"active_relay\":" + String(activeRelay) + "}";
    
    // Add the alarm
    AlarmManager::addNewAlarm(newEntry);

    request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Alarm added\"}"); });

    server.on("/api/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    uint8_t volume = Storage::getGlobalVolume();
    uint8_t equalizer = Storage::getGlobalEqualizer();
    String alarmsJson = AlarmManager::getAllAlarmsJson();
    String relayDataJson = Relay::getAllRelayDataJson();
    String ringtoneList = Storage::getRingtoneList();

    String response = "{";
    response += "\"volume\":" + String(volume) + ",";
    response += "\"equalizer\":" + String(equalizer) + ",";
    response += "\"alarms\":" + alarmsJson + ",";
    response += "\"relays\":" + relayDataJson + ",";
    response += "\"ringtone_list\":" + ringtoneList;
    response += "}";

    request->send(200, "application/json", response); });

    server.on("/api/delete", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("id", true)) {
            int id = request->getParam("id", true)->value().toInt();
            AlarmManager::removeAlarmById(id);
            request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Alarm deleted\"}");
        } else {
            request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"ID missing\"}");
        } });

    server.on("/api/clear", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        AlarmManager::clearAllAlarms();
        request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"All alarms cleared\"}"); });

    server.on("/api/volume", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("value", true)) {
            int volume = request->getParam("value", true)->value().toInt();
            Storage::setGlobalVolume(volume);
            request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Volume updated\"}");
        } else {
            request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Volume value missing\"}");
        } });

    server.on("/api/equalizer", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("value", true)) {
            int eq = request->getParam("value", true)->value().toInt();
            Storage::setGlobalEqualizer(eq);
            request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Equalizer updated\"}");
        } else {
            request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Equalizer value missing\"}");
        } });

    server.on("/api/update", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("id", true) &&
            request->hasParam("label", true) &&
            request->hasParam("time", true) &&
            request->hasParam("repeat", true) &&
            request->hasParam("ringtone", true) &&
            request->hasParam("active", true) &&
            request->hasParam("active_relay", true)) {
            
            int id = request->getParam("id", true)->value().toInt();
            String label = request->getParam("label", true)->value();
            String time = request->getParam("time", true)->value();
            String repeat = request->getParam("repeat", true)->value();
            String ringtone = request->getParam("ringtone", true)->value();
            bool active = request->getParam("active", true)->value().equalsIgnoreCase("true");
            uint8_t activeRelay = request->getParam("active_relay", true)->value().toInt();

            String updatedAlarm = "{\"id\":" + String(id) + 
                                  ",\"label\":\"" + label + 
                                  "\",\"time\":\"" + time + 
                                  "\",\"repeat\":\"" + repeat + 
                                  "\",\"ringtone\":\"" + ringtone + 
                                  "\",\"active\":" + (active ? "true" : "false") + 
                                  ",\"active_relay\":" + String(activeRelay) + "}";
            
            if (AlarmManager::updateAlarm(id, updatedAlarm)) {
                request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Alarm updated\"}");
            } else {
                request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Failed to update alarm\"}");
            }
        } else {
            request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Missing parameters\"}");
        } });

    server.on("/api/toggle", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("id", true) && request->hasParam("active", true)) {
            int id = request->getParam("id", true)->value().toInt();
            bool active = request->getParam("active", true)->value().equalsIgnoreCase("true");

            if (AlarmManager::toggleAlarm(id, active)) {
                request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Alarm toggled\"}");
            } else {
                request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Failed to toggle alarm\"}");
            }
        } else {
            request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Missing parameters\"}");
        } });

    server.on("/api/play", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        uint8_t trackNumber = request->getParam("value", true)->value().toInt();
        AudioManager::handlePlay(trackNumber);
        request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Playing Audio Manually\"}"); });

    server.on("/api/stop", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        AudioManager::handleStop();
        request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Stopped Audio Manually\"}"); });

    server.on("/api/relay", HTTP_POST, [](AsyncWebServerRequest *request)
              {
    if (!request->hasParam("relayNumber", true) || !request->hasParam("action", true)) {
        request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Missing parameters\"}");
        return;
    }

    uint8_t relayNumber = request->getParam("relayNumber", true)->value().toInt();
    String action = request->getParam("action", true)->value();

    if (relayNumber < 1 || relayNumber > 4) {
        request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid relay number\"}");
        return;
    }

    if (action == "on") {
        Relay::relayOn(relayNumber);
        request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Relay turned ON\"}");
    } else if (action == "off") {
        Relay::relayOff(relayNumber);
        request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Relay turned OFF\"}");
    } else {
        request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid action\"}");
    } });

    server.on("/api/relayduration", HTTP_POST, [](AsyncWebServerRequest *request)
{
    if (request->hasParam("relayNumber", true) && request->hasParam("duration", true)) {
        uint8_t relayNumber = request->getParam("relayNumber", true)->value().toInt();
        unsigned long duration = request->getParam("duration", true)->value().toInt();
        if (relayNumber >= 1 && relayNumber <= 4) {
            Relay::saveRelayDuration(relayNumber, duration);
            String response = "{\"status\":\"success\",\"message\":\"Relay duration updated\",\"relayNumber\":" + String(relayNumber) + ",\"duration\":" + String(duration) + "}";
            request->send(200, "application/json", response);
        } else {
            request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid relay number\"}");
        }
    } else {
        request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Missing parameters\"}");
    }
});

    server.on("/api/relaylabel", HTTP_POST, [](AsyncWebServerRequest *request)
              {
    if (request->hasParam("relayNumber", true) && request->hasParam("label", true)) {
        uint8_t relayNumber = request->getParam("relayNumber", true)->value().toInt();
        String label = request->getParam("label", true)->value();
        if (relayNumber >= 1 && relayNumber <= 4) {
            Relay::saveRelayLabel(relayNumber, label);
            request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Relay label updated\"}");
        } else {
            request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid relay number\"}");
        }
    } else {
        request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Missing parameters\"}");
    } });
}