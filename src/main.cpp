#include "DebugEsp.h"

#include "NetworkConnection.h"

NetworkConnection network;

DebugEsp debug;

void setup()
{
  debug.begin(9600);
}

void loop()
{
  debug.debI("Hmm", true);
  delay(2000);
}
