#include "DebugEsp.h"

#ifdef WEBSERIAL_DEBUG

#include "NetworkConnection.h"

AsyncWebServer server(80);

noDelay timeoutSerial(5000);

#endif // WEBSERIAL_DEBUG

#ifdef DEBUG_ACTIVE

// Constructor
DebugEsp::DebugEsp()
{
}

// Initialize the logger with the baud rate
void DebugEsp::begin(unsigned long baudRate)
{
#ifdef SERIAL_DEBUG

    Serial.begin(baudRate);

    timeoutSerial.start();
    while (!Serial)
    {
        if (timeoutSerial.update())
        {
            ESP.restart();
        }
    }

#endif // SERIAL_DEBUG

#ifdef WEBSERIAL_DEBUG

    network.begin();

    if (network.isConnected())
    {
        WebSerial.begin(&server);
        server.begin();
        webserialDebugRunning = 1;
    }
    else
    {
        webserialDebugRunning = 0;
    }

#endif // WEBSERIAL_DEBUG

    if (serialDebugRunning)
    {
        debug.debI("Serial Running", true);
    }
    if (webserialDebugRunning)
    {
        debug.debI("WebSerial Running", true);
    }
    else
    {
        debug.debW("WebSerial could not be started", true);
    }
}

// Print without new line for errors
void DebugEsp::debE(String message, bool newline)
{
    printLog(ERROR, message, newline);
}

// Log info with new line
void DebugEsp::debI(String message, bool newline)
{
    printLog(INFO, message, newline);
}

// Log warnings with new line
void DebugEsp::debW(String message, bool newline)
{
    printLog(WARNING, message, newline);
}

void DebugEsp::debActivityIndicator()
{
    const char activityChars[] = {'|', '/', '-', '\\'};

#ifdef SERIAL_DEBUG

    Serial.print("\b");
    Serial.print(activityChars[activityState]);

#endif // SERIAL_DEBUG

#ifdef WEBSERIAL_DEBUG

    WebSerial.print("\b");
    WebSerial.print(activityChars[activityState]);

#endif // WEBSERIAL_DEBUG

    activityState = (activityState + 1) % 4;
}

void DebugEsp::debActivityIndicatorStop()
{
#ifdef SERIAL_DEBUG

    Serial.print("\b");
    Serial.print(" ");
    Serial.println();

#endif // SERIAL_DEBUG

#ifdef WEBSERIAL_DEBUG

    WebSerial.print("\b");
    WebSerial.print(" ");
    WebSerial.println();

#endif // WEBSERIAL_DEBUG
}

void DebugEsp::printLog(LogLevel level, String message, bool newLine)
{
#ifdef SERIAL_DEBUG

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

#endif // SERIAL_DEBUG

#ifdef WEBSERIAL_DEBUG

    switch (level)
    {
    case INFO:
        WebSerial.print("[INFO] ");
        break;

    case WARNING:
        WebSerial.print("[WARNING] ");
        break;

    case ERROR:
        WebSerial.print("[ERROR] ");
        break;
    }

    if (newLine)
    {
        WebSerial.println(message);
    }
    else
    {
        WebSerial.print(message);
    }

#endif // WEBSERIAL_DEBUG
}

#endif // DEBUG_ACTIVE
