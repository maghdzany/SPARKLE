#include "WebServer.h"
#include <LittleFS.h>
#include "TimeManager.h"

AsyncWebServer WebServer::server(80);

void WebServer::initializeServer() {
    if (!LittleFS.begin()) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    setupServerRoutes();
    server.begin();
}

void WebServer::setupServerRoutes() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(LittleFS, "/index.html", "text/html");
    });

    server.on("/api/time", HTTP_GET, [](AsyncWebServerRequest* request) {
        String timeJson = TimeManager::getTimeJsonString();
        request->send(200, "application/json", timeJson);
    });

    server.on("/api/add", HTTP_POST, [](AsyncWebServerRequest* request) {
        String label, time, repeat;
        if (request->hasParam("label", true)) label = request->getParam("label", true)->value();
        if (request->hasParam("time", true)) time = request->getParam("time", true)->value();
        if (request->hasParam("repeat", true)) repeat = request->getParam("repeat", true)->value();

        String newEntry = "{\"label\":\"" + label + "\",\"time\":\"" + time + "\",\"repeat\":\"" + repeat + "\"}";
        AlarmManager::addNewAlarm(newEntry);
        request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Alarm added\"}");
    });

    server.on("/api/get", HTTP_GET, [](AsyncWebServerRequest* request) {
        String data = AlarmManager::getAllAlarmsJson();
        request->send(200, "application/json", data);
    });

    server.on("/api/delete", HTTP_POST, [](AsyncWebServerRequest* request) {
        if (request->hasParam("id", true)) {
            int id = request->getParam("id", true)->value().toInt();
            AlarmManager::removeAlarmById(id);
            request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Alarm deleted\"}");
        } else {
            request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"ID missing\"}");
        }
    });

    server.on("/api/clear", HTTP_POST, [](AsyncWebServerRequest* request) {
        AlarmManager::clearAllAlarms();
        request->send(200, "application/json", "{\"status\":\"success\",\"message\":\"All alarms cleared\"}");
    });
}