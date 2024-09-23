#include "Config.h"

#include "DebugEsp.h"

DebugEsp debug;

void setup()
{
  debug.begin(9600); // Initialize Serial at 115200 baud rate
  debug.debI("Initializing sensors...", true);
  debug.debW("Low battery warning", true);
  debug.debE("Failed to connect to WiFi ", true);
  while (millis() < 5000)
  {
    debug.debActivityIndicator();
    delay(100);
  }
  debug.debI("WifiStarted", true);
}

void loop()
{
}
