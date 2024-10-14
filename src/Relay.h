#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

class Relay
{
public:
    static void loop();
    static void init();
    static void relayOn(uint8_t relayNumber);
    static void relayOff(uint8_t relayNumber);
    static void relayOnWithDuration(uint8_t relayNumber, unsigned long duration);
    static uint8_t getRelayPin(uint8_t relayNumber);

    static void saveRelayState(uint8_t relayNumber, int state);
    static int getRelayState(uint8_t relayNumber);
    static void saveRelayDuration(uint8_t relayNumber, unsigned long duration);
    static unsigned long getRelayDuration(uint8_t relayNumber);

    // New functions for label and id
    static void saveRelayLabel(uint8_t relayNumber, const String &label);
    static String getRelayLabel(uint8_t relayNumber);

    // New function to get all relay data as JSON
    static String getAllRelayDataJson();

private:
    static const char *getRelayStateKey(uint8_t relayNumber);
    static const char *getRelayDurationKey(uint8_t relayNumber);
    static const char *getRelayLabelKey(uint8_t relayNumber);
    static const char *getRelayIdKey(uint8_t relayNumber);
    static unsigned long relayTimers[4];
    static void checkRelayTimers();
};

#endif // RELAY_H