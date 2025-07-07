/**
 * @file mqtt_parse_send.cpp
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Parse received LoRa packet and publish to MQTT broker
 * @version 0.1
 * @date 2025-07-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */
/**
 * @file mqtt_parse_send.cpp
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Parse received LoRa packet and publish to MQTT broker
 * @version 0.1
 * @date 2024-08-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "main.h"
#include <ArduinoJson.h>
#include <RAK_LPP.h>

#ifndef JSON_BUFF_SIZE
/** Default JSON buffer size */
#define JSON_BUFF_SIZE 4096
#endif

/** JSON document for sending and response */
JsonDocument rcvd_json;

RAK_LPP decoded(255);

/** Buffer for serialized JSON response */
char in_out_buff[JSON_BUFF_SIZE];

/** Buffer for the MQTT topic */
char mqtt_topic[1024];

bool mqtt_parse_send(uint8_t *data, uint16_t data_len)
{
	// Create topic as char array
	snprintf(mqtt_topic, 64, "rak3112_p2p/%02X%02X%02X%02X", g_lorawan_settings.node_device_eui[4], g_lorawan_settings.node_device_eui[5],
			 g_lorawan_settings.node_device_eui[6], g_lorawan_settings.node_device_eui[7]);

	MYLOG("PARSE", "Topic is %s", mqtt_topic);

	// Decode with RAK_LPP
	JsonObject mqtt_out = rcvd_json.to<JsonObject>();
#if MY_DEBUG > 0
	decoded.decodeMQTT(data, data_len, mqtt_out);
	MYLOG("PARSE", "JSON as String:");
	serializeJson(mqtt_out, Serial);
	Serial.println("");
#endif
	serializeJson(mqtt_out, in_out_buff);

	if (!publish_mqtt(mqtt_topic, in_out_buff))
	{
		MYLOG("PARSE", "Send request failed");
		return false;
	}
	return true;
}
