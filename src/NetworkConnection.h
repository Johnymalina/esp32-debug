#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER -1
#define ETH_PHY_TYPE ETH_PHY_LAN8720
#define ETH_PHY_ADDR 0
#define ETH_PHY_MDC 23
#define ETH_PHY_MDIO 18
#define NRST 5

#include <Arduino.h>
#include <WiFiClient.h>
#include <ETH.h>
#include <DebugEsp.h>

class NetworkConnection
{
public:
    NetworkConnection();
    void begin();
    void setCallback();
    bool isConnected();

private:
    volatile bool _netConnected;
    volatile bool _ethConnected;
    volatile bool _wifiConnected;

    bool ethBegin();
    bool wifiBegin();

    static void WiFiEvent(WiFiEvent_t event);
};

extern NetworkConnection network;

#endif