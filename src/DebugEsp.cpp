#include "DebugEsp.h"

#ifdef DEBUG_ACTIVE

// Constructor
DebugEsp::DebugEsp() {}

// Initialize the logger with the baud rate
void DebugEsp::begin(unsigned long baudRate)
{
    Serial.begin(baudRate);
    delay(2000); // Give some time for Serial to start
}

// Print without new line for errors
void DebugEsp::debE(const char *message, bool newline)
{
    printLog(ERROR, message, newline);
}

// Log info with new line
void DebugEsp::debI(const char *message, bool newline)
{
    printLog(INFO, message, newline);
}

// Log warnings with new line
void DebugEsp::debW(const char *message, bool newline)
{
    printLog(WARNING, message, newline);
}

void DebugEsp::debActivityIndicator()
{
    const char activityChars[] = {'|', '/', '-', '\\'};
    Serial.print("\b");                         // Move cursor back to overwrite the previous character
    Serial.print(activityChars[activityState]); // Print the current activity character
    activityState = (activityState + 1) % 4;    // Update the state to the next character
}

void DebugEsp::debActivityIndicatorStop()
{
    Serial.println(); // Update the state to the next character
}

// Helper function for logging messages with or without newline
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

#endif // DEBUG_ACTIVE
