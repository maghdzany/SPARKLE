#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESPAsyncWebServer.h>
#include "AlarmManager.h"

class WebServer {
public:
    static void initializeServer();

private:
    static AsyncWebServer server;
    static void setupServerRoutes();
};

#endif // WEB_SERVER_H