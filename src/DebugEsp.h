#ifndef DEBUG_ESP_H
#define DEBUG_ESP_H

#include "Arduino.h"
#include "Config.h"

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
    void debE(const char *message, bool newline);
    void debI(const char *message, bool newline);
    void debW(const char *message, bool newline);
    void debActivityIndicator();

private:
    void printLog(LogLevel level, const char *message, bool newLine);
    int activityState;
};

#else // DEBUG_ACTIVE is not defined, so ignore debug

class DebugEsp
{
public:
    DebugEsp() {}
    void begin(unsigned long baudRate) {}
    void debE(const char *message, bool newline) {}
    void debI(const char *message, bool newline) {}
    void debW(const char *message, bool newline) {}
    void debActivityIndicator() {}
};

#endif // DEBUG_ACTIVE

#endif // DEBUG_LOGGER_H
