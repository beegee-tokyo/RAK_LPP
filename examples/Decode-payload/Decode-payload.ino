/**
 * @file Decode-payload.ino
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Simple encode and decode example
 * @version 0.1
 * @date 2025-07-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <Arduino.h>
#include <RAK_LPP.h>

/** JSON document for sending and response */
JsonDocument decoded_json;

// RAK_LPP instance
RAK_LPP payload(255);

void setup()
{
	Serial.begin(115200);
	delay(5000);

	Serial.println("RAK_LPP simple encode/decode example");
	Serial.println("====================================");

	// Reset Payload
	payload.reset();
	Serial.printf("Size after reset = %d\n", payload.getSize());

	// Add humidity from RAK1901
	Serial.println("Adding Humidity 45.3 %RH");
	payload.addRelativeHumidity(LPP_CHANNEL_HUMID, 45.3);
	// Add temperature from RAK1901
	Serial.println("Adding Temperature 23.8 degC");
	payload.addTemperature(LPP_CHANNEL_TEMP, 23.8);
	// add barometric pressure from RAK1902
	Serial.println("Adding Barometric Pressure 1024.4 mBar");
	payload.addBarometricPressure(LPP_CHANNEL_PRESS_2, 1024.4);
	// Add CO2 concentration from RAK12037
	Serial.println("Adding CO2 729 ppm");
	payload.addConcentration(LPP_CHANNEL_CO2_2, 729);
	// Add particulate matter 1.0 values from RAK12039
	Serial.println("Adding Particulate matter 1.0 15 ug/m3");
	payload.addVoc_index(LPP_CHANNEL_PM_1_0, 15);
	// Add particulate matter 2.5 values from RAK12039
	Serial.println("Adding Particulate matter 2.5 22 ug/m3");
	payload.addVoc_index(LPP_CHANNEL_PM_2_5, 22);
	// Add particulate matter 10 values from RAK12039
	Serial.println("Adding Particulate matter 10.0 4 ug/m3");
	payload.addVoc_index(LPP_CHANNEL_PM_10_0, 4);
	// Add VOC value from RAK12047
	Serial.println("Adding VOC index 116");
	payload.addVoc_index(LPP_CHANNEL_VOC, 116);

	Serial.printf("Payload size %d\n", payload.getSize());

	Serial.println("====================================");
	// Decode to array
	Serial.println("Decoded as Array");
	JsonArray root = decoded_json.to<JsonArray>();
	payload.decode(payload.getBuffer(), payload.getSize(), root);
	serializeJsonPretty(root, Serial);
	Serial.println("");
	Serial.println("====================================");

	// Decode to array for MQTT
	Serial.println("Decoded as MQTT Array");
	JsonObject mqtt_out = decoded_json.to<JsonObject>();
	payload.decodeMQTT(payload.getBuffer(), payload.getSize(), mqtt_out);
	serializeJsonPretty(mqtt_out, Serial);
	Serial.println("");
	Serial.println("====================================");
}

void loop()
{
	// put your main code here, to run repeatedly:
}
