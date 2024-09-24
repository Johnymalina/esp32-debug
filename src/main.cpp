#include "DebugEsp.h"

DebugEsp debug;

void setup()
{
  debug.begin(9600); // Initialize Serial at 115200 baud rate
  debug.debI("Initializing sensors...", true);
  while (millis() < 5000)
  {
    debug.debActivityIndicator();
    delay(100);
  }
  debug.debActivityIndicatorStop();

  debug.debI("Sensor Initialized", true);

  debug.debE("Failed to connect to WiFi ", true);

  debug.debI("WifiStarted", true);
}

void loop()
{
}
