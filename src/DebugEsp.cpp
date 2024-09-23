#include "DebugEsp.h"

#ifdef DEBUG_ACTIVE

// Constructor
DebugEsp::DebugEsp() {}

// Initialize the logger with the baud rate
void DebugEsp::begin(unsigned long baudRate)
{
#ifdef SERIAL_DEBUG
    Serial.begin(baudRate);
    delay(2000); // Give some time for Serial to start
#endif

#ifdef WEBSERIAL_DEBUG

#endif
}

// Print without new line for errors
void DebugEsp::debE(const char *message, bool newline)
{
#ifdef SERIAL_DEBUG
    printLog(ERROR, message, newline);
#endif // SERIAL_DEBUG
}

// Log info with new line
void DebugEsp::debI(const char *message, bool newline)
{
#ifdef SERIAL_DEBUG
    printLog(INFO, message, newline);
#endif // SERIAL_DEBUG
}

// Log warnings with new line
void DebugEsp::debW(const char *message, bool newline)
{
#ifdef SERIAL_DEBUG
    printLog(WARNING, message, newline);
#endif // SERIAL_DEBUG
}

void DebugEsp::debActivityIndicator()
{
#ifdef SERIAL_DEBUG
    const char activityChars[] = {'|', '/', '-', '\\'};
    Serial.print("\b");
    Serial.print(activityChars[activityState]);
    activityState = (activityState + 1) % 4;
#endif // SERIAL_DEBUG
}

void DebugEsp::debActivityIndicatorStop()
{
#ifdef SERIAL_DEBUG
    Serial.println();
#endif // SERIAL_DEBUG
}

#ifdef SERIAL_DEBUG

void DebugEsp::printLog(LogLevel level, const char *message, bool newLine)
{
    switch (level)
    {
    case INFO:
        Serial.print("[INFO] ");
        break;
    case WARNING:
        Serial.print("[WARNING] ");
        break;
    case ERROR:
        Serial.print("[ERROR] ");
        break;
    }

    if (newLine)
    {
        Serial.println(message);
    }
    else
    {
        Serial.print(message);
    }
}
#endif // SERIAL_DEBUG

#endif // DEBUG_ACTIVE
