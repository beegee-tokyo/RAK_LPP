/**
 * @file main.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Includes, defines and globals
 * @version 0.1
 * @date 2024-08-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _MAIN_H_
#define _MAIN_H_

// ATC+WIFI=RAKwirelessDemo:RAKwireless@2025:RAKwirelessDemo:RAKwireless@2025:192.168.230.162: :
// ATC+WIFI=RAKTap:RAKwireless@2025:RAKTap:RAKwireless@2025:10.42.0.1: :

#include <Arduino.h>
#include <WisBlock-API-V2.h>
#include <RAK_LPP.h>

// Debug output set to 0 to disable app debug output
#ifndef MY_DEBUG
#define MY_DEBUG 1
#endif

#if MY_DEBUG > 0
#define MYLOG(tag, ...)                        \
	if (tag)                                   \
		Serial.printf("[%s] ", tag);           \
	Serial.printf(__VA_ARGS__);                \
	Serial.printf("\n");                       \
	Serial.flush();                            \
	if (g_ble_uart_is_connected)               \
	{                                          \
		char buff[255];                        \
		sprintf(buff, __VA_ARGS__);            \
		sprintf(buff, "%s\r\n", buff);         \
		std::string txt = buff;                \
		uart_tx_characteristic->setValue(txt); \
		uart_tx_characteristic->notify();      \
		delay(50);                             \
	}
#else
#define MYLOG(...)
#endif

/** Define the version of your SW */
#ifndef SW_VERSION_1
#define SW_VERSION_1 1 // major version increase on API change / not backwards compatible
#endif
#ifndef SW_VERSION_2
#define SW_VERSION_2 0 // minor version increase on API change / backward compatible
#endif
#ifndef SW_VERSION_3
#define SW_VERSION_3 0 // patch version increase on bugfix, no affect on API
#endif

/** Application function definitions */
void setup_app(void);
bool init_app(void);
void app_event_handler(void);
void ble_data_handler(void) __attribute__((weak));
void lora_data_handler(void);

// Wakeup flags
#define PARSE 0b1000000000000000
#define N_PARSE 0b0111111111111111

// Cayenne LPP Channel numbers per sensor value
#define LPP_CHANNEL_BATT 1 // Base Board

// Globals
extern RAK_LPP g_solution_data;

// WiFi and MQTT stuff
void setup_wifi(void);
void reconnect_wifi(void);
bool publish_mqtt(char *topic, char *payload);
void check_mqtt(void);
extern String g_ssid_prim;
extern String g_ssid_sec;
extern String g_pw_prim;
extern String g_pw_sec;
extern char g_mqtt_server[];
extern char g_mqtt_user[];
extern char g_mqtt_pw[];
extern char g_mqtt_publish[];

// Parser
typedef struct _stParam
{
	char *argv[25];
	int argc;
} stParam;
bool mqtt_parse_send(uint8_t *data, uint16_t data_len);
bool parseBuff2Param(char *bufCmd, stParam *pParam, uint8_t maxargu);

#endif // _MAIN_H_