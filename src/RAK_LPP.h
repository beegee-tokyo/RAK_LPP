// Adapted 2025 from https://github.com/ElectronicCats/CayenneLPP to fit with extended requirements of RAKwireless WisBlock and WisDuo modules and devices

// Adapted from https://developer.mbed.org/teams/myDevicesIoT/code/Cayenne-LPP/

// Copyright © 2017 The Things Network
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef RAK_LPP_H
#define RAK_LPP_H

// Arduino framework
#ifdef ARDUINO
#include <Arduino.h>
#include <ArduinoJson.h>
#endif
// ESP-IDF framework
#if !defined(ARDUINO) && defined(IDF_VER)
#include <ArduinoJson.h>
#endif

#define LPP_DIGITAL_INPUT 0			// 1 byte
#define LPP_DIGITAL_OUTPUT 1		// 1 byte
#define LPP_ANALOG_INPUT 2			// 2 bytes, 0.01 signed
#define LPP_ANALOG_OUTPUT 3			// 2 bytes, 0.01 signed
#define LPP_GENERIC_SENSOR 100		// 4 bytes, unsigned
#define LPP_LUMINOSITY 101			// 2 bytes, 1 lux unsigned
#define LPP_PRESENCE 102			// 1 byte, bool
#define LPP_TEMPERATURE 103			// 2 bytes, 0.1°C signed
#define LPP_RELATIVE_HUMIDITY 104	// 1 byte, 0.5% unsigned
#define LPP_ACCELEROMETER 113		// 2 bytes per axis, 0.001G
#define LPP_BAROMETRIC_PRESSURE 115 // 2 bytes 0.1hPa unsigned
#define LPP_VOLTAGE 116				// 2 bytes 0.01V unsigned
#define LPP_CURRENT 117				// 2 bytes 0.001A unsigned
#define LPP_FREQUENCY 118			// 4 bytes 1Hz unsigned
#define LPP_PERCENTAGE 120			// 1 byte 1-100% unsigned
#define LPP_ALTITUDE 121			// 2 byte 1m signed
#define LPP_CONCENTRATION 125		// 2 bytes, 1 ppm unsigned
#define LPP_POWER 128				// 2 byte, 1W, unsigned
#define LPP_DISTANCE 130			// 4 byte, 0.001m, unsigned
#define LPP_ENERGY 131				// 4 byte, 0.001kWh, unsigned
#define LPP_DIRECTION 132			// 2 bytes, 1deg, unsigned
#define LPP_UNIXTIME 133			// 4 bytes, unsigned
#define LPP_GYROMETER 134			// 2 bytes per axis, 0.01 °/s
#define LPP_COLOUR 135				// 1 byte per RGB Color
#define LPP_GPS 136					// 3 byte lon/lat 0.0001 °, 3 bytes alt 0.01 meter (Cayenne LPP default)
#define LPP_GPS4 136				// 3 byte lon/lat 0.0001 °, 3 bytes alt 0.01 meter (Cayenne LPP default)
#define LPP_GPS6 137				// 4 byte lon/lat 0.000001 °, 3 bytes alt 0.01 meter (Customized Cayenne LPP, higher precision)
#define LPP_VOC 138					// 2 byte VOC index
#define WB_DEV_ID 255				// 4 byte device ID (used for P2P communication)
#define LPP_SWITCH 142				// 1 byte, 0/1

// Only Data Size
#define LPP_DIGITAL_INPUT_SIZE 1
#define LPP_DIGITAL_OUTPUT_SIZE 1
#define LPP_ANALOG_INPUT_SIZE 2
#define LPP_ANALOG_OUTPUT_SIZE 2
#define LPP_GENERIC_SENSOR_SIZE 4
#define LPP_LUMINOSITY_SIZE 2
#define LPP_PRESENCE_SIZE 1
#define LPP_TEMPERATURE_SIZE 2
#define LPP_RELATIVE_HUMIDITY_SIZE 1
#define LPP_ACCELEROMETER_SIZE 6
#define LPP_BAROMETRIC_PRESSURE_SIZE 2
#define LPP_VOLTAGE_SIZE 2
#define LPP_CURRENT_SIZE 2
#define LPP_FREQUENCY_SIZE 4
#define LPP_PERCENTAGE_SIZE 1
#define LPP_ALTITUDE_SIZE 2
#define LPP_POWER_SIZE 2
#define LPP_DISTANCE_SIZE 4
#define LPP_ENERGY_SIZE 4
#define LPP_DIRECTION_SIZE 2
#define LPP_UNIXTIME_SIZE 4
#define LPP_GYROMETER_SIZE 6
#define LPP_GPS_SIZE 9
#define LPP_SWITCH_SIZE 1
#define LPP_CONCENTRATION_SIZE 2
#define LPP_COLOUR_SIZE 3
#define LPP_GPS4_SIZE 9
#define LPP_GPS6_SIZE 11
#define LPP_GPSH_SIZE 14
#define LPP_GPST_SIZE 10
#define LPP_VOC_SIZE 2
#define WB_DEV_ID_SIZE 4

// Multipliers
#define LPP_DIGITAL_INPUT_MULT 1
#define LPP_DIGITAL_OUTPUT_MULT 1
#define LPP_ANALOG_INPUT_MULT 100
#define LPP_ANALOG_OUTPUT_MULT 100
#define LPP_GENERIC_SENSOR_MULT 1
#define LPP_LUMINOSITY_MULT 1
#define LPP_PRESENCE_MULT 1
#define LPP_TEMPERATURE_MULT 10
#define LPP_RELATIVE_HUMIDITY_MULT 2
#define LPP_ACCELEROMETER_MULT 1000
#define LPP_BAROMETRIC_PRESSURE_MULT 10
#define LPP_VOLTAGE_MULT 100
#define LPP_CURRENT_MULT 1000
#define LPP_FREQUENCY_MULT 1
#define LPP_PERCENTAGE_MULT 1
#define LPP_ALTITUDE_MULT 1
#define LPP_POWER_MULT 1
#define LPP_DISTANCE_MULT 1000
#define LPP_ENERGY_MULT 1000
#define LPP_DIRECTION_MULT 1
#define LPP_UNIXTIME_MULT 1
#define LPP_GYROMETER_MULT 100
#define LPP_GPS_LAT_LON_MULT 10000
#define LPP_GPS_ALT_MULT 100
#define LPP_SWITCH_MULT 1
#define LPP_CONCENTRATION_MULT 1
#define LPP_COLOUR_MULT 1

#define LPP_ERROR_OK 0
#define LPP_ERROR_OVERFLOW 1
#define LPP_ERROR_UNKOWN_TYPE 2

// Cayenne LPP Channel numbers per sensor value used in WisBlock API examples
#define LPP_CHANNEL_DEVID 0	  // Device ID, only used in LoRa P2P
#define LPP_CHANNEL_BATT 1	  // Base Board
#define LPP_CHANNEL_HUMID 2	  // RAK1901
#define LPP_CHANNEL_TEMP 3	  // RAK1901
#define LPP_CHANNEL_PRESS 4	  // RAK1902
#define LPP_CHANNEL_LIGHT 5	  // RAK1903
#define LPP_CHANNEL_HUMID_2 6 // RAK1906
#define LPP_CHANNEL_TEMP_2 7  // RAK1906
#define LPP_CHANNEL_PRESS_2 8 // RAK1906
#define LPP_CHANNEL_GAS_2 9	  // RAK1906
#define LPP_CHANNEL_GPS 10	  // RAK1910/RAK12500

/// \todo double used channel !!!!!!!!!!!!!!!!!!!!!!
#define LPP_CHANNEL_SOIL_TEMP 11 // RAK12035
#define LPP_CHANNEL_GPS_TOWER 11 // RAK13102

#define LPP_CHANNEL_SOIL_HUMID 12	   // RAK12035
#define LPP_CHANNEL_SOIL_HUMID_RAW 13  // RAK12035
#define LPP_CHANNEL_SOIL_VALID 14	   // RAK12035
#define LPP_CHANNEL_LIGHT2 15		   // RAK12010
#define LPP_CHANNEL_VOC 16			   // RAK12047
#define LPP_CHANNEL_GAS 17			   // RAK12004
#define LPP_CHANNEL_GAS_PERC 18		   // RAK12004
#define LPP_CHANNEL_CO2 19			   // RAK12008
#define LPP_CHANNEL_CO2_PERC 20		   // RAK12008
#define LPP_CHANNEL_ALC 21			   // RAK12009
#define LPP_CHANNEL_ALC_PERC 22		   // RAK12009
#define LPP_CHANNEL_TOF 23			   // RAK12014
#define LPP_CHANNEL_TOF_VALID 24	   // RAK12014
#define LPP_CHANNEL_GYRO 25			   // RAK12025
#define LPP_CHANNEL_GESTURE 26		   // RAK14008
#define LPP_CHANNEL_UVI 27			   // RAK12019
#define LPP_CHANNEL_UVS 28			   // RAK12019
#define LPP_CHANNEL_CURRENT_CURRENT 29 // RAK16000
#define LPP_CHANNEL_CURRENT_VOLTAGE 30 // RAK16000
#define LPP_CHANNEL_CURRENT_POWER 31   // RAK16000
#define LPP_CHANNEL_TOUCH_1 32		   // RAK14002
#define LPP_CHANNEL_TOUCH_2 33		   // RAK14002
#define LPP_CHANNEL_TOUCH_3 34		   // RAK14002
#define LPP_CHANNEL_CO2_2 35		   // RAK12037
#define LPP_CHANNEL_CO2_Temp_2 36	   // RAK12037
#define LPP_CHANNEL_CO2_HUMID_2 37	   // RAK12037
#define LPP_CHANNEL_TEMP_3 38		   // RAK12003
#define LPP_CHANNEL_TEMP_4 39		   // RAK12003
#define LPP_CHANNEL_PM_1_0 40		   // RAK12039
#define LPP_CHANNEL_PM_2_5 41		   // RAK12039
#define LPP_CHANNEL_PM_10_0 42		   // RAK12039
#define LPP_CHANNEL_EQ_EVENT 43		   // RAK12027
#define LPP_CHANNEL_EQ_SI 44		   // RAK12027
#define LPP_CHANNEL_EQ_PGA 45		   // RAK12027
#define LPP_CHANNEL_EQ_SHUTOFF 46	   // RAK12027
#define LPP_CHANNEL_EQ_COLLAPSE 47	   // RAK12027
#define LPP_CHANNEL_SWITCH 48		   // RAK13011
#define LPP_SH_WS 49				   // SensorHub RK900-09
#define LPP_SH_WD 50				   // SensorHub RK900-09
#define LPP_AUDIO_L_A 51			   // WisBlock Audio
#define LPP_AUDIO_L_C 52			   // WisBlock Audio
#define LPP_AUDIO_ALARM 53			   // WisBlock Audio
#define LPP_AUDIO_TYPE 54			   // WisBlock Audio
#define LPP_SH_SOIL_MOIST 55		   // SensorHub RK500-02
#define LPP_SH_EC 56				   // SensorHub RK500-02
#define LPP_SH_PH_H 57				   // SensorHub RK500-02
#define LPP_SH_PH_L 58				   // SensorHub RK500-02
#define LPP_SH_PYRANO 59			   // SensorHub RK200-03
#define LPP_SH_HUMID_PREC 60		   // SensorHub RK520-02
#define LPP_CHANNEL_WLEVEL 61		   // RAK12059
#define LPP_CHANNEL_WL_LOW 62		   // RAK12059
#define LPP_CHANNEL_WL_HIGH 63		   // RAK12059

/** uint16_t level union */
union int_union_s
{
	uint16_t val16 = 0;
	uint8_t val8[2];
};
/** Latitude/Longitude value union */
union latLong_s
{
	int32_t val32;
	int8_t val8[4];
};

class RAK_LPP
{

public:
	RAK_LPP(uint8_t size);
	~RAK_LPP();

	void reset(void);
	uint8_t getSize(void);
	uint8_t *getBuffer(void);
	uint8_t copy(uint8_t *buffer);
	uint8_t getError();

	// Decoder methods
	const char *getTypeName(uint8_t type);
// Arduino or ESP-IDF framework
#if defined(ARDUINO) || defined(IDF_VER)
	uint8_t decode(uint8_t *buffer, uint8_t size, JsonArray root);
	uint8_t decodeMQTT(uint8_t *buffer, uint8_t len, JsonObject root);
	uint8_t decodeTTN(uint8_t *buffer, uint8_t size, JsonObject root);
#endif

	// Original LPPv1 data types
	uint8_t addDigitalInput(uint8_t channel, uint32_t value);
	uint8_t addDigitalOutput(uint8_t channel, uint32_t value);
	uint8_t addAnalogInput(uint8_t channel, float value);
	uint8_t addAnalogOutput(uint8_t channel, float value);
	uint8_t addLuminosity(uint8_t channel, uint32_t value);
	uint8_t addPresence(uint8_t channel, uint32_t value);
	uint8_t addTemperature(uint8_t channel, float value);
	uint8_t addRelativeHumidity(uint8_t channel, float value);
	uint8_t addAccelerometer(uint8_t channel, float x, float y, float z);
	uint8_t addBarometricPressure(uint8_t channel, float value);
	uint8_t addGyrometer(uint8_t channel, float x, float y, float z);
	uint8_t addGPS(uint8_t channel, float latitude, float longitude, float altitude);

	// Additional data types
	uint8_t addUnixTime(uint8_t channel, uint32_t value);
	uint8_t addGenericSensor(uint8_t channel, float value);
	uint8_t addVoltage(uint8_t channel, float value);
	uint8_t addCurrent(uint8_t channel, float value);
	uint8_t addFrequency(uint8_t channel, uint32_t value);
	uint8_t addPercentage(uint8_t channel, uint32_t value);
	uint8_t addAltitude(uint8_t channel, float value);
	uint8_t addPower(uint8_t channel, uint32_t value);
	uint8_t addDistance(uint8_t channel, float value);
	uint8_t addEnergy(uint8_t channel, float value);
	uint8_t addDirection(uint8_t channel, float value);
	uint8_t addSwitch(uint8_t channel, uint32_t value);
	uint8_t addConcentration(uint8_t channel, uint32_t value);
	uint8_t addColour(uint8_t channel, uint8_t r, uint8_t g, uint8_t b);

	// Additional data types added by RAKwireless
	uint8_t addGNSS_4(uint8_t channel, int32_t latitude, int32_t longitude, int32_t altitude);
	uint8_t addGNSS_6(uint8_t channel, int32_t latitude, int32_t longitude, int32_t altitude);
	uint8_t addGNSS_H(int32_t latitude, int32_t longitude, int16_t altitude, int16_t accuracy, int16_t battery);
	uint8_t addGNSS_T(int32_t latitude, int32_t longitude, int16_t altitude, int16_t accuracy, int8_t sats);
	uint8_t addGNSS_T2(int32_t latitude, int32_t longitude, int16_t sequence_id);
	uint8_t addVoc_index(uint8_t channel, uint32_t voc_index);
	uint8_t addDevID(uint8_t channel, uint8_t *dev_id);

protected:
	bool isType(uint8_t type);
	uint8_t getTypeSize(uint8_t type);
	uint32_t getTypeMultiplier(uint8_t type);
	bool getTypeSigned(uint8_t type);

	float getValue(uint8_t *buffer, uint8_t size, uint32_t multiplier,
				   bool is_signed);
	uint32_t getValue32(uint8_t *buffer, uint8_t size);
	template <typename T>
	uint8_t addField(uint8_t type, uint8_t channel, T value);

	uint8_t *_buffer;
	uint8_t _maxsize;
	uint8_t _cursor;
	uint8_t _error = LPP_ERROR_OK;
};

#endif // RAK_LPP_H
