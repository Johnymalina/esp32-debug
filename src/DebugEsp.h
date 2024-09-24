#ifndef DEBUG_ESP_H
#define DEBUG_ESP_H

#include "Arduino.h"
#include "Config.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

// Log levels
enum LogLevel
{
    INFO,
    WARNING,
    ERROR
};

// Conditionally compile debug code only when DEBUG_ACTIVE is defined
#ifdef DEBUG_ACTIVE

class DebugEsp
{
public:
    DebugEsp();
    void begin(unsigned long baudRate);
    void debE(String message, bool newline);
    void debI(String message, bool newline);
    void debW(String message, bool newline);
    void debActivityIndicator();
    void debActivityIndicatorStop();

private:
    void printLog(LogLevel level, String message, bool newLine);
    int activityState;
};

#else // DEBUG_ACTIVE is not defined, so ignore debug

class DebugEsp
{
public:
    DebugEsp() {}
    void begin(unsigned long baudRate) {}
    void debE(String message, bool newline) {}
    void debI(String message, bool newline) {}
    void debW(String message, bool newline) {}
    void debActivityIndicator() {}
    void debActivityIndicatorStop() {}
};

#endif // DEBUG_ACTIVE

#endif // DEBUG_LOGGER_H
