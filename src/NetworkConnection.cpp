#include "NetworkConnection.h"
#include <Arduino.h>
#include "DebugEsp.h"
#include "Config.h"

noDelay timeoutConnection(5000);

volatile bool _netConnected = false;

void WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {

    case ARDUINO_EVENT_ETH_CONNECTED:
        debug.debI("Ethernet Network Connected", true);
        _netConnected = true;
        break;

    case ARDUINO_EVENT_ETH_GOT_IP:
        debug.debI(String("Ethernet IPv4: ") + ETH.localIP().toString(), true);
        debug.debI(String("Hostname: ") + ETH.getHostname(), true);
        debug.debI(String("MAC: ") + ETH.macAddress(), true);
        debug.debI(String("Speed: ") + ETH.linkSpeed() + String("Mbps"), true);
        break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
        if (_netConnected)
        {
            debug.debW("ETH Disconnected", true);
        }
        _netConnected = false;
        break;

    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        debug.debActivityIndicatorStop();
        debug.debI("WiFi connected", true);
        _netConnected = true;
        break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:

        debug.debI(String("SSID: ") + WiFi.SSID(), true);
        debug.debI(String("Wlan IPv4: ") + WiFi.localIP().toString(), true);
        debug.debI(String("Hostname: ") + WiFi.getHostname(), true);
        debug.debI(String("MAC: ") + WiFi.macAddress(), true);
        debug.debI(String("Signal: ") + WiFi.getTxPower() + String("dB"), true);
        break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        if (_netConnected)
        {
            debug.debW("WiFi disconnected. Reconnecting...", true);
        }
        _netConnected = false;
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
    debug.debI("Starting network...", true);

    setCallback();

    ethBegin();

    if (!_netConnected)
    {
        wifiBegin();
    }
    // TODO Fallback WLAN connection when ethernet is not available
}

bool NetworkConnection::ethBegin()
{
#ifdef NETWORK_CONNECTION_ETH

    debug.debI("Ethernet connecting...", true);
    ETH.begin();
    ETH.setHostname(HOSTNAME);

#ifdef STATIC_IP

    ETH.config(IPAddress(IP_ADDRESS), IPAddress(DEFAULT_GATEWAY), IPAddress(SUBNET_MASK));

#endif

    timeoutConnection.start();
    while (!ETH.linkUp())
    {
        debug.debActivityIndicator();
        delay(100);

        if (timeoutConnection.update())
        {
            debug.debActivityIndicatorStop();
            _netConnected = 0;
            return 0;
        }
    }

    debug.debActivityIndicatorStop();
    _netConnected = 1;
    return 1;

#endif
}

bool NetworkConnection::wifiBegin()
{
#ifdef NETWORK_CONNECTION_WIFI

    WiFi.setHostname(HOSTNAME);

#ifdef STATIC_IP

    WiFi.config(IPAddress(IP_ADDRESS), IPAddress(DEFAULT_GATEWAY), IPAddress(SUBNET_MASK));

#endif

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    debug.debI("WiFi Connecting...", true);
    timeoutConnection.start();
    while (!WiFi.isConnected())
    {
        debug.debActivityIndicator();
        delay(100);

        if (timeoutConnection.update())
        {
            debug.debActivityIndicatorStop();
            _netConnected = 0;
            return 0;
        }
    }

    debug.debActivityIndicatorStop();
    _netConnected = 1;
    return 1;

#endif
}

void NetworkConnection::setCallback()
{
    debug.debI("Network Callback Active", true);

    WiFi.onEvent(WiFiEvent);
}

bool NetworkConnection::isConnected()
{
    if (!_netConnected)
    {
        return 0;
    }
    return 1;
}

// TODO Periodically check connection status wlan/ethernet. Make sense to add also if connected when its not possible to publish this status when network is not connected?