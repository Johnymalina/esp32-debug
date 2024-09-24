#include <NetworkConnection.h>
#include <Arduino.h>
#include "DebugEsp.h"
#include "Config.h"

static bool eth_connected = false;

void WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case ARDUINO_EVENT_ETH_START:
        ETH.setHostname("lora2mqtt-gateway");

        debug.debI("Ethernet Network Started", true);

        break;
    case ARDUINO_EVENT_ETH_CONNECTED:

        debug.debI("Ethernet Network Connected", true);

        break;

    case ARDUINO_EVENT_ETH_GOT_IP:

        debug.debI(String("Ethernet IPv4: ") + ETH.localIP(), true);
        debug.debI(String("Hostname: ") + ETH.getHostname(), true);
        debug.debI(String("MAC: ") + ETH.macAddress(), true);
        debug.debI(String("Speed: ") + ETH.linkSpeed() + String("Mbps"), true);
        eth_connected = true;
        break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:

        debug.debW("ETH Disconnected", true);
        eth_connected = false;
        break;

    case ARDUINO_EVENT_ETH_STOP:

        debug.debW("ETH Stopped", true);
        eth_connected = false;
        break;
    case ARDUINO_EVENT_WIFI_READY:
        debug.debI("ARDUINO_EVENT_WIFI_READY", true);
        break;
    case ARDUINO_EVENT_WIFI_SCAN_DONE:
        debug.debI("ARDUINO_EVENT_WIFI_SCAN_DONE", true);
        break;
    case ARDUINO_EVENT_WIFI_STA_START:
        debug.debI("ARDUINO_EVENT_WIFI_STA_START", true);
        break;
    case ARDUINO_EVENT_WIFI_STA_STOP:
        debug.debI("ARDUINO_EVENT_WIFI_STA_STOP", true);
        break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        debug.debI("ARDUINO_EVENT_WIFI_STA_CONNECTED", true);
        break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        debug.debI("ARDUINO_EVENT_WIFI_STA_DISCONNECTED", true);
        break;
    case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
        debug.debI("ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE", true);
        break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
        debug.debI("ARDUINO_EVENT_WIFI_STA_GOT_IP", true);
        break;
    case ARDUINO_EVENT_WIFI_STA_LOST_IP:
        debug.debI("ARDUINO_EVENT_WIFI_STA_LOST_IP", true);
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
    ETH.begin();
    ETH.config(IPAddress(IP_ADDRESS), IPAddress(DEFAULT_GATEWAY), IPAddress(SUBNET_MASK));
#endif
    // TODO Fallback WLAN connection when ethernet is not avalaible
}

void NetworkConnection::setCallback()
{
    debug.debI("Network Callback Active", true);

    WiFi.onEvent(WiFiEvent);
}

// TODO Periodicaly check connection status wlan/ethernet. Make sense to add also if connected when its not possible to publish this status wehn network is not connected?