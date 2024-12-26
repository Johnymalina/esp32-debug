#include "NetworkConnection.h"
#include <Arduino.h>
#include "DebugEsp.h"
#include "Config.h"

noDelay timeoutConnection(5000);
int maxReconnect = 5;
int reconnectCount = 0;

void setCallback()
{
    debug.debI("Network Callback Active", true);

    WiFi.onEvent(NetworkConnection::WiFiEvent);
}

bool ethBegin()
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
            return false;
        }
    }

    debug.debActivityIndicatorStop();
    return true;

#else
    return false;
#endif
}

bool wifiBegin()
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
            return false;
        }
    }

    debug.debActivityIndicatorStop();
    return true;

#else
    return false;
#endif
}

NetworkConnection::NetworkConnection()
    : _netConnected(false), _ethConnected(false), _wifiConnected(false)
{
}

void NetworkConnection::WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {

    case ARDUINO_EVENT_ETH_CONNECTED:
        debug.debI("Ethernet Network Connected", true);
        network._ethConnected = true;
        network._netConnected = true;
        break;

    case ARDUINO_EVENT_ETH_GOT_IP:
        debug.debI(String("Ethernet IPv4: ") + ETH.localIP().toString(), true);
        debug.debI(String("Hostname: ") + ETH.getHostname(), true);
        debug.debI(String("MAC: ") + ETH.macAddress(), true);
        debug.debI(String("Speed: ") + ETH.linkSpeed() + String("Mbps"), true);
        break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
        if (network._netConnected)
        {
            debug.debW("ETH Disconnected", true);
        }
        network._ethConnected = false;
        network._netConnected = false;
        break;

    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        debug.debActivityIndicatorStop();
        debug.debI("WiFi connected", true);
        network._wifiConnected = true;
        network._netConnected = true;
        break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:

        debug.debI(String("SSID: ") + WiFi.SSID(), true);
        debug.debI(String("Wlan IPv4: ") + WiFi.localIP().toString(), true);
        debug.debI(String("Hostname: ") + WiFi.getHostname(), true);
        debug.debI(String("MAC: ") + WiFi.macAddress(), true);
        debug.debI(String("Signal: ") + WiFi.getTxPower() + String("dB"), true);
        break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        if (network._netConnected)
        {
            debug.debW("WiFi disconnected", true);
        }
        network._wifiConnected = false;
        network._netConnected = false;
        break;

    default:
        break;
    }
}

void NetworkConnection::begin()
{
    debug.debI("Starting network...", true);

    setCallback();

    if (!ethBegin())
    {
        wifiBegin();
    }
}

bool NetworkConnection::isConnected()
{
    if (!_ethConnected && !_wifiConnected)
    {

        if (reconnectCount == 0)
        {
            Serial.println("First connection attempt");
            timeoutConnection.start();
            wifiBegin();
            reconnectCount++;
        }

        if (timeoutConnection.update())
        {
            reconnectCount++;
            timeoutConnection.start();
            debug.debW("Reconnect count: " + String(reconnectCount), true);

            if (reconnectCount >= maxReconnect)
            {
                debug.debW("Max reconnect reached. Restarting", true);
                delay(5000);
                ESP.restart();
            }
        }
    }
    else if (_ethConnected && _wifiConnected)
    {
        WiFi.disconnect();
    }

    if (_netConnected && reconnectCount > 0)
    {
        reconnectCount = 0;
    }

    return _netConnected;
}

// TODO Periodically check connection status wlan/ethernet. Make sense to add also if connected when its not possible to publish this status when network is not connected?