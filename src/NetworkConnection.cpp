#include "NetworkConnection.h"
#include <Arduino.h>
#include "DebugEsp.h"
#include "Config.h"

volatile bool net_connected = false;

void WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {

    case ARDUINO_EVENT_ETH_START:
        debug.debI("Ethernet Network Started", true);
        break;

    case ARDUINO_EVENT_ETH_CONNECTED:
        debug.debI("Ethernet Network Connected", true);
        net_connected = true;
        break;

    case ARDUINO_EVENT_ETH_GOT_IP:
        debug.debI(String("Ethernet IPv4: ") + ETH.localIP().toString(), true);
        debug.debI(String("Hostname: ") + ETH.getHostname(), true);
        debug.debI(String("MAC: ") + ETH.macAddress(), true);
        debug.debI(String("Speed: ") + ETH.linkSpeed() + String("Mbps"), true);
        break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
        if (net_connected)
        {
            debug.debW("ETH Disconnected", true);
        }
        net_connected = false;
        break;

    case ARDUINO_EVENT_ETH_STOP:
        debug.debW("ETH Stopped", true);
        net_connected = false;
        break;

    case ARDUINO_EVENT_WIFI_STA_START:
        debug.debI("WiFi connecting...", false);
        break;

    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        debug.debActivityIndicatorStop();
        debug.debI("WiFi connected", true);
        net_connected = true;
        break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:

        debug.debI(String("SSID: ") + WiFi.SSID(), true);
        debug.debI(String("Wlan IPv4: ") + WiFi.localIP().toString(), true);
        debug.debI(String("Hostname: ") + WiFi.getHostname(), true);
        debug.debI(String("MAC: ") + WiFi.macAddress(), true);
        debug.debI(String("Signal: ") + WiFi.getTxPower() + String("dB"), true);
        break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        if (net_connected)
        {
            debug.debW("WiFi disconnected. Reconnecting...", true);
        }
        net_connected = false;
        break;

    case ARDUINO_EVENT_WIFI_STA_STOP:
        debug.debW("WiFi Stopped", true);
        net_connected = false;
        break;

    default:
        break;
    }
}

NetworkConnection::NetworkConnection()
{
}

void NetworkConnection::begin()
{

#ifdef NETWORK_CONNECTION_ETH
    ETH.setHostname(HOSTNAME);
    ETH.begin();
    ETH.config(IPAddress(IP_ADDRESS), IPAddress(DEFAULT_GATEWAY), IPAddress(SUBNET_MASK));
#endif
    WiFi.setHostname(HOSTNAME);
    WiFi.config(IPAddress(IP_ADDRESS), IPAddress(DEFAULT_GATEWAY), IPAddress(SUBNET_MASK));
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (!WiFi.isConnected())
    {
        debug.debActivityIndicator();
        delay(100);
    }

    debug.debActivityIndicatorStop();
    // TODO Fallback WLAN connection when ethernet is not available
}

void NetworkConnection::setCallback()
{
    debug.debI("Network Callback Active", true);

    WiFi.onEvent(WiFiEvent);
}

bool NetworkConnection::isConnected()
{
    return net_connected;
}

// TODO Periodically check connection status wlan/ethernet. Make sense to add also if connected when its not possible to publish this status when network is not connected?