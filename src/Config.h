// config.h
#ifndef CONFIG_H
#define CONFIG_H

// INFO Debug related config

#define DEBUG_ACTIVE // Comment out to deactivate debug completely

#define SERIAL_DEBUG // Comment out to deactivate SERIAL debug completely

#define WEBSERIAL_DEBUG // Comment out to deactivate WEBSERIAL debug completely

// INFO Network connection related config

// #define NETWORK_CONNECTION_ETH

#define NETWORK_CONNECTION_WIFI

#define IP_ADDRESS 10, 10, 42, 5
#define DEFAULT_GATEWAY 10, 10, 42, 1
#define SUBNET_MASK 255, 255, 255, 0
#define HOSTNAME "Lora2MQTT Gateway"

#endif // CONFIG_H
