#include "DebugEsp.h"

#include "NetworkConnection.h"

NetworkConnection network;

DebugEsp debug;

void setup()
{
  debug.begin(9600); // Initialize Serial at 115200 baud rate
  debug.debI("Serial started", true);

  debug.debI("Starting network...", true);
  network.setCallback();
  network.begin();
}

void loop()
{
}
