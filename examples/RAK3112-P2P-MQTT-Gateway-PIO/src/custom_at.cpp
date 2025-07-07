/**
 * @file custom_at.cpp
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Custom AT commands to set WiFi and MQTT credentials
 * @version 0.1
 * @date 2025-04-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "main.h"

/**
 * @brief Returns the current WiFi and MQTT settings
 *
 * @return int
 */
static int at_query_wifi()
{
	snprintf(g_at_query_buf, ATQUERY_SIZE, "%s:%s:%s:%s:%s:%s:%s", g_ssid_prim.c_str(), g_pw_prim.c_str(), g_ssid_sec.c_str(), g_pw_sec.c_str(),
			 g_mqtt_server, g_mqtt_user, g_mqtt_pw);
	Serial.printf("%s\r\n", g_at_query_buf);
	return 0;
}

/**
 * @brief Command to set the custom variable
 *
 * @param str the new value for the variable without the AT part
 * @return int 0 if the command was succesfull, 5 if the parameter was wrong
 */
static int at_exec_wifi(char *str)
{
	char *param;

	param = strtok(str, ":");

	if (param != NULL)
	{
		/* Check WiFi AP 1 */
		g_ssid_prim = String(param);

		/* Check AP 1 PW */
		param = strtok(NULL, ":");
		if (param != NULL)
		{
			g_pw_prim = String(param);

			/** Check WiFi AP 2 */
			param = strtok(NULL, ":");
			if (param != NULL)
			{
				g_ssid_sec = String(param);

				/* Check AP 2 PW */
				param = strtok(NULL, ":");
				if (param != NULL)
				{
					g_pw_sec = String(param);

					// Check MQTT URL
					param = strtok(NULL, ":");
					if (param != NULL)
					{
						snprintf(g_mqtt_server, 128, param);

						// Check MQTT user
						param = strtok(NULL, ":");
						if (param != NULL)
						{
							snprintf(g_mqtt_user, 128, param);

							// Check MQTT password
							param = strtok(NULL, ":");
							if (param != NULL)
							{
								snprintf(g_mqtt_pw, 128, param);

								// // Check MQTT publish path
								// param = strtok(NULL, ":");
								// if (param != NULL)
								{
									snprintf(g_mqtt_pw, 128, param);
									// Save new settings
									Preferences preferences;
									preferences.begin("WiFiCred", false);
									preferences.putString("g_ssid_prim", g_ssid_prim);
									preferences.putString("g_ssid_sec", g_ssid_sec);
									preferences.putString("g_pw_prim", g_pw_prim);
									preferences.putString("g_pw_sec", g_pw_sec);
									preferences.putBool("valid", true);
									preferences.end();
									preferences.begin("MQTTCred", false);
									preferences.putString("g_mqtt_url", g_mqtt_server);
									preferences.putString("g_mqtt_user", g_mqtt_user);
									preferences.putString("g_mqtt_pw", g_mqtt_pw);
									preferences.putBool("valid", true);
									preferences.end();

									MYLOG("AT", "WiFi 1 >%s<", g_ssid_prim.c_str());
									MYLOG("AT", "WiFi 1 PW >%s<", g_pw_prim.c_str());
									MYLOG("AT", "WiFi 2 >%s<", g_ssid_sec.c_str());
									MYLOG("AT", "WiFi 2 PW >%s<", g_pw_sec.c_str());
									MYLOG("AT", "MQTT PW >%s<", g_mqtt_pw);
									MYLOG("AT", "MQTT Name >%s<", g_mqtt_user);
									MYLOG("AT", "MQTT URL >%s<", g_mqtt_server);

									return AT_SUCCESS;
								}
							}
						}
					}
				}
			}
		}
	}

	return 0;
}

/**
 * @brief List of all available commands with short help and pointer to functions
 *
 */
atcmd_t g_user_at_cmd_list_example[] = {
	/*|    CMD    |     AT+CMD?      |    AT+CMD=?    |  AT+CMD=value |  AT+CMD  |  Permissions  |*/
	// GNSS commands
	{"+WIFI", "Set/Get the WiFi and MQTT settings", at_query_wifi, at_exec_wifi, NULL, "RW"},
};

/** Number of user defined AT commands */
uint8_t g_user_at_cmd_num = 1; // sizeof(g_user_at_cmd_list_example) / sizeof(atcmd_t);

/** Pointer to the AT command list */
atcmd_t *g_user_at_cmd_list = g_user_at_cmd_list_example;

