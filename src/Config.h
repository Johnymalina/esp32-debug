// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include "Secrets.h"

// INFO Debug related config

#define DEBUG_ACTIVE

#define SERIAL_DEBUG

#define WEBSERIAL_DEBUG

// INFO Network connection related config

#define NETWORK_CONNECTION_ETH

#define NETWORK_CONNECTION_WIFI

#define STATIC_IP

#define IP_ADDRESS 10, 10, 42, 5
#define DEFAULT_GATEWAY 10, 10, 42, 1
#define SUBNET_MASK 255, 255, 255, 0
#define HOSTNAME "Lora2MQTT Gateway"

/* SSID and Password set in Secrets.h>

#define WIFI_SSID "YourSSID"
#define WIFI_PASSWORD "YourPassword"

 */

#endif // CONFIG_H
