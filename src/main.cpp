#include "DebugEsp.h"

#include "NetworkConnection.h"

NetworkConnection network;

DebugEsp debug;

void setup()
{
  debug.begin(9600);
  debug.debI("Serial started", true);

  debug.debI("Starting network...", true);
  network.setCallback();
  network.begin();
}

void loop()
{
}
