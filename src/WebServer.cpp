#include "WebServer.h"
#include <LittleFS.h>
#include "TimeManager.h"
#include "AlarmManager.h"
#include "AudioManager.h"

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

    if (request->hasParam("label", true)) label = request->getParam("label", true)->value();
    if (request->hasParam("time", true)) time = request->getParam("time", true)->value();
    if (request->hasParam("repeat", true)) repeat = request->getParam("repeat", true)->value();
    if (request->hasParam("ringtone", true)) ringtone = request->getParam("ringtone", true)->value();
    if (request->hasParam("active", true)) active = request->getParam("active", true)->value().equalsIgnoreCase("true");

    // Create the new alarm JSON structure with all fields
    String newEntry = "{\"label\":\"" + label + "\",\"time\":\"" + time + "\",\"repeat\":\"" + repeat + "\",\"ringtone\":\"" + ringtone + "\",\"active\":" + (active ? "true" : "false") + "}";
    
    // Add the alarm
    AlarmManager::addNewAlarm(newEntry);
    
    request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Alarm added\"}"); });

    server.on("/api/get", HTTP_GET, [](AsyncWebServerRequest* request) {
    // 1. Dapatkan volume dari NVS
    int volume = Storage::getGlobalVolume();

    // 2. Dapatkan equalizer dari AudioManager
    String equalizer = AudioManager::handleReadEqualizer();

    // 3. Dapatkan data alarm
    String alarmsJson = AlarmManager::getAllAlarmsJson();

    // 4. Dapatkan daftar ringtone dari AudioManager
    String ringtoneList = AudioManager::handleListTracks();

    // 5. Buat respons JSON lengkap
    String response = "{";
    response += "\"volume\":" + String(volume) + ",";
    response += "\"equalizer\":\"" + equalizer + "\",";
    response += "\"alarms\":" + alarmsJson + ",";
    response += "\"ringtone_list\":" + ringtoneList;
    response += "}";

    // 6. Kirim respons
    request->send(200, "application/json", response);
});


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
}