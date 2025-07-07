// Adapted 2025 from https://github.com/ElectronicCats/CayenneLPP to fit with extended requirements of RAKwireless WisBlock and WisDuo modules and devices

// Adapted from https://developer.mbed.org/teams/myDevicesIoT/code/Cayenne-LPP/

// Copyright © 2017 The Things Network
// Use of this source code is governed by the MIT license that can be found in the LICENSE file.

#include "RAK_LPP.h"

// ----------------------------------------------------------------------------

RAK_LPP::RAK_LPP(uint8_t size) : _maxsize(size)
{
	_buffer = (uint8_t *)malloc(size);
	_cursor = 0;
}

RAK_LPP::~RAK_LPP(void)
{
	free(_buffer);
}

void RAK_LPP::reset(void)
{
	_cursor = 0;
}

uint8_t RAK_LPP::getSize(void)
{
	return _cursor;
}

uint8_t *RAK_LPP::getBuffer(void)
{
	return _buffer;
}

uint8_t RAK_LPP::copy(uint8_t *dst)
{
	memcpy(dst, _buffer, _cursor);
	return _cursor;
}

uint8_t RAK_LPP::getError()
{
	uint8_t error = _error;
	_error = LPP_ERROR_OK;
	return error;
}

// ----------------------------------------------------------------------------

bool RAK_LPP::isType(uint8_t type)
{

	switch (type)
	{
	case LPP_DIGITAL_INPUT:
	case LPP_DIGITAL_OUTPUT:
	case LPP_ANALOG_INPUT:
	case LPP_ANALOG_OUTPUT:
	case LPP_GENERIC_SENSOR:
	case LPP_LUMINOSITY:
	case LPP_PRESENCE:
	case LPP_TEMPERATURE:
	case LPP_RELATIVE_HUMIDITY:
	case LPP_ACCELEROMETER:
	case LPP_BAROMETRIC_PRESSURE:
	case LPP_VOLTAGE:
	case LPP_CURRENT:
	case LPP_FREQUENCY:
	case LPP_PERCENTAGE:
	case LPP_ALTITUDE:
	case LPP_POWER:
	case LPP_DISTANCE:
	case LPP_ENERGY:
	case LPP_DIRECTION:
	case LPP_UNIXTIME:
	case LPP_GYROMETER:
	// case LPP_GPS: // Now LPP_GPS4
	case LPP_SWITCH:
	case LPP_CONCENTRATION:
	case LPP_COLOUR:
	case LPP_GPS4:
	case LPP_GPS6:
	case LPP_VOC:
	case WB_DEV_ID:
		return true;
	}

	return false;
}

const char *RAK_LPP::getTypeName(uint8_t type)
{

	switch (type)
	{
	case LPP_DIGITAL_INPUT:
		return "digital_in";
	case LPP_DIGITAL_OUTPUT:
		return "digital_out";
	case LPP_ANALOG_INPUT:
		return "analog_in";
	case LPP_ANALOG_OUTPUT:
		return "analog_out";
	case LPP_GENERIC_SENSOR:
		return "generic";
	case LPP_LUMINOSITY:
		return "luminosity";
	case LPP_PRESENCE:
		return "presence";
	case LPP_TEMPERATURE:
		return "temperature";
	case LPP_RELATIVE_HUMIDITY:
		return "humidity";
	case LPP_ACCELEROMETER:
		return "accelerometer";
	case LPP_BAROMETRIC_PRESSURE:
		return "barometer";
	case LPP_VOLTAGE:
		return "voltage";
	case LPP_CURRENT:
		return "current";
	case LPP_FREQUENCY:
		return "frequency";
	case LPP_PERCENTAGE:
		return "percentage";
	case LPP_ALTITUDE:
		return "altitude";
	case LPP_POWER:
		return "power";
	case LPP_DISTANCE:
		return "distance";
	case LPP_ENERGY:
		return "energy";
	case LPP_DIRECTION:
		return "direction";
	case LPP_UNIXTIME:
		return "time";
	case LPP_GYROMETER:
		return "gyrometer";
		// case LPP_GPS:  // Now LPP_GPS4
		return "gps";
	case LPP_SWITCH:
		return "switch";
	case LPP_CONCENTRATION:
		return "concentration";
	case LPP_COLOUR:
		return "colour";
	case LPP_GPS4:
		return "gps";
	case LPP_GPS6:
		return "gps";
	case LPP_VOC:
		return "voc";
	case WB_DEV_ID:
		return "node_id";
	default:
		return nullptr;
	}
}

uint8_t RAK_LPP::getTypeSize(uint8_t type)
{

	switch (type)
	{
	case LPP_DIGITAL_INPUT:
		return LPP_DIGITAL_INPUT_SIZE;
	case LPP_DIGITAL_OUTPUT:
		return LPP_DIGITAL_OUTPUT_SIZE;
	case LPP_ANALOG_INPUT:
		return LPP_ANALOG_INPUT_SIZE;
	case LPP_ANALOG_OUTPUT:
		return LPP_ANALOG_OUTPUT_SIZE;
	case LPP_GENERIC_SENSOR:
		return LPP_GENERIC_SENSOR_SIZE;
	case LPP_LUMINOSITY:
		return LPP_LUMINOSITY_SIZE;
	case LPP_PRESENCE:
		return LPP_PRESENCE_SIZE;
	case LPP_TEMPERATURE:
		return LPP_TEMPERATURE_SIZE;
	case LPP_RELATIVE_HUMIDITY:
		return LPP_RELATIVE_HUMIDITY_SIZE;
	case LPP_ACCELEROMETER:
		return LPP_ACCELEROMETER_SIZE;
	case LPP_BAROMETRIC_PRESSURE:
		return LPP_BAROMETRIC_PRESSURE_SIZE;
	case LPP_VOLTAGE:
		return LPP_VOLTAGE_SIZE;
	case LPP_CURRENT:
		return LPP_CURRENT_SIZE;
	case LPP_FREQUENCY:
		return LPP_FREQUENCY_SIZE;
	case LPP_PERCENTAGE:
		return LPP_PERCENTAGE_SIZE;
	case LPP_ALTITUDE:
		return LPP_ALTITUDE_SIZE;
	case LPP_POWER:
		return LPP_POWER_SIZE;
	case LPP_DISTANCE:
		return LPP_DISTANCE_SIZE;
	case LPP_ENERGY:
		return LPP_ENERGY_SIZE;
	case LPP_DIRECTION:
		return LPP_DIRECTION_SIZE;
	case LPP_UNIXTIME:
		return LPP_UNIXTIME_SIZE;
	case LPP_GYROMETER:
		return LPP_GYROMETER_SIZE;
	// case LPP_GPS: // Now LPP_GPS4
	// 	return LPP_GPS_SIZE;
	case LPP_SWITCH:
		return LPP_SWITCH_SIZE;
	case LPP_CONCENTRATION:
		return LPP_CONCENTRATION_SIZE;
	case LPP_COLOUR:
		return LPP_COLOUR_SIZE;
	case LPP_GPS4:
		return LPP_GPS4_SIZE;
	case LPP_GPS6:
		return LPP_GPS6_SIZE;
	case LPP_VOC:
		return LPP_VOC_SIZE;
	case WB_DEV_ID:
		return WB_DEV_ID_SIZE;
	default:
		return 0;
	}
}

uint32_t RAK_LPP::getTypeMultiplier(uint8_t type)
{

	switch (type)
	{
	case LPP_DIGITAL_INPUT:
		return LPP_DIGITAL_INPUT_MULT;
	case LPP_DIGITAL_OUTPUT:
		return LPP_DIGITAL_OUTPUT_MULT;
	case LPP_ANALOG_INPUT:
		return LPP_ANALOG_INPUT_MULT;
	case LPP_ANALOG_OUTPUT:
		return LPP_ANALOG_OUTPUT_MULT;
	case LPP_GENERIC_SENSOR:
		return LPP_GENERIC_SENSOR_MULT;
	case LPP_LUMINOSITY:
		return LPP_LUMINOSITY_MULT;
	case LPP_PRESENCE:
		return LPP_PRESENCE_MULT;
	case LPP_TEMPERATURE:
		return LPP_TEMPERATURE_MULT;
	case LPP_RELATIVE_HUMIDITY:
		return LPP_RELATIVE_HUMIDITY_MULT;
	case LPP_ACCELEROMETER:
		return LPP_ACCELEROMETER_MULT;
	case LPP_BAROMETRIC_PRESSURE:
		return LPP_BAROMETRIC_PRESSURE_MULT;
	case LPP_VOLTAGE:
		return LPP_VOLTAGE_MULT;
	case LPP_CURRENT:
		return LPP_CURRENT_MULT;
	case LPP_FREQUENCY:
		return LPP_FREQUENCY_MULT;
	case LPP_PERCENTAGE:
		return LPP_PERCENTAGE_MULT;
	case LPP_ALTITUDE:
		return LPP_ALTITUDE_MULT;
	case LPP_POWER:
		return LPP_POWER_MULT;
	case LPP_DISTANCE:
		return LPP_DISTANCE_MULT;
	case LPP_ENERGY:
		return LPP_ENERGY_MULT;
	case LPP_DIRECTION:
		return LPP_DIRECTION_MULT;
	case LPP_UNIXTIME:
		return LPP_UNIXTIME_MULT;
	case LPP_GYROMETER:
		return LPP_GYROMETER_MULT;
	case LPP_SWITCH:
		return LPP_SWITCH_MULT;
	case LPP_CONCENTRATION:
		return LPP_CONCENTRATION_MULT;
	case LPP_COLOUR:
		return LPP_COLOUR_MULT;
	default:
		return 0;
	}
}

bool RAK_LPP::getTypeSigned(uint8_t type)
{

	switch (type)
	{
	case LPP_ANALOG_INPUT:
	case LPP_ANALOG_OUTPUT:
	case LPP_TEMPERATURE:
	case LPP_ACCELEROMETER:
	case LPP_ALTITUDE:
	case LPP_GYROMETER:
	// case LPP_GPS: // Now LPP_GPS4
	case LPP_GPS4:
	case LPP_GPS6:
		return true;
	}
	return false;
}

// ----------------------------------------------------------------------------

template <typename T>
uint8_t RAK_LPP::addField(uint8_t type, uint8_t channel, T value)
{

	// Check type
	if (!isType(type))
	{
		_error = LPP_ERROR_UNKOWN_TYPE;
		return 0;
	}

	// Type definition
	uint8_t size = getTypeSize(type);
	uint32_t multiplier = getTypeMultiplier(type);
	bool is_signed = getTypeSigned(type);

	// check buffer overflow
	if ((_cursor + size + 2) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}

	// check sign
	bool sign = value < 0;
	if (sign)
		value = -value;

	// get value to store
	uint32_t v = value * multiplier;

	// format an uint32_t as if it was an int32_t
	if (is_signed & sign)
	{
		uint32_t mask = (1 << (size * 8)) - 1;
		v = v & mask;
		if (sign)
			v = mask - v + 1;
	}

	// header
	_buffer[_cursor++] = channel;
	_buffer[_cursor++] = type;

	// add bytes (MSB first)
	for (uint8_t i = 1; i <= size; i++)
	{
		_buffer[_cursor + size - i] = (v & 0xFF);
		v >>= 8;
	}

	// update & return _cursor
	_cursor += size;
	return _cursor;
}

uint8_t RAK_LPP::addDigitalInput(uint8_t channel, uint32_t value)
{
	return addField(LPP_DIGITAL_INPUT, channel, value);
}

uint8_t RAK_LPP::addDigitalOutput(uint8_t channel, uint32_t value)
{
	return addField(LPP_DIGITAL_OUTPUT, channel, value);
}

uint8_t RAK_LPP::addAnalogInput(uint8_t channel, float value)
{
	return addField(LPP_ANALOG_INPUT, channel, value);
}

uint8_t RAK_LPP::addAnalogOutput(uint8_t channel, float value)
{
	return addField(LPP_ANALOG_OUTPUT, channel, value);
}

uint8_t RAK_LPP::addGenericSensor(uint8_t channel, float value)
{
	return addField(LPP_GENERIC_SENSOR, channel, value);
}

uint8_t RAK_LPP::addLuminosity(uint8_t channel, uint32_t value)
{
	return addField(LPP_LUMINOSITY, channel, value);
}

uint8_t RAK_LPP::addPresence(uint8_t channel, uint32_t value)
{
	return addField(LPP_PRESENCE, channel, value);
}

uint8_t RAK_LPP::addTemperature(uint8_t channel, float value)
{
	return addField(LPP_TEMPERATURE, channel, value);
}

uint8_t RAK_LPP::addRelativeHumidity(uint8_t channel, float value)
{
	return addField(LPP_RELATIVE_HUMIDITY, channel, value);
}

uint8_t RAK_LPP::addVoltage(uint8_t channel, float value)
{
	return addField(LPP_VOLTAGE, channel, value);
}

uint8_t RAK_LPP::addCurrent(uint8_t channel, float value)
{
	return addField(LPP_CURRENT, channel, value);
}

uint8_t RAK_LPP::addFrequency(uint8_t channel, uint32_t value)
{
	return addField(LPP_FREQUENCY, channel, value);
}

uint8_t RAK_LPP::addPercentage(uint8_t channel, uint32_t value)
{
	return addField(LPP_PERCENTAGE, channel, value);
}

uint8_t RAK_LPP::addAltitude(uint8_t channel, float value)
{
	return addField(LPP_ALTITUDE, channel, value);
}

uint8_t RAK_LPP::addPower(uint8_t channel, uint32_t value)
{
	return addField(LPP_POWER, channel, value);
}

uint8_t RAK_LPP::addDistance(uint8_t channel, float value)
{
	return addField(LPP_DISTANCE, channel, value);
}

uint8_t RAK_LPP::addEnergy(uint8_t channel, float value)
{
	return addField(LPP_ENERGY, channel, value);
}

uint8_t RAK_LPP::addBarometricPressure(uint8_t channel, float value)
{
	return addField(LPP_BAROMETRIC_PRESSURE, channel, value);
}

uint8_t RAK_LPP::addUnixTime(uint8_t channel, uint32_t value)
{
	return addField(LPP_UNIXTIME, channel, value);
}

uint8_t RAK_LPP::addDirection(uint8_t channel, float value)
{
	return addField(LPP_DIRECTION, channel, value);
}

uint8_t RAK_LPP::addSwitch(uint8_t channel, uint32_t value)
{
	return addField(LPP_SWITCH, channel, value);
}

uint8_t RAK_LPP::addConcentration(uint8_t channel, uint32_t value)
{
	return addField(LPP_CONCENTRATION, channel, value);
}

uint8_t RAK_LPP::addColour(uint8_t channel, uint8_t r, uint8_t g, uint8_t b)
{
	// check buffer overflow
	if ((_cursor + LPP_COLOUR_SIZE + 2) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}
	_buffer[_cursor++] = channel;
	_buffer[_cursor++] = LPP_COLOUR;
	_buffer[_cursor++] = r;
	_buffer[_cursor++] = g;
	_buffer[_cursor++] = b;

	return _cursor;
}

uint8_t RAK_LPP::addAccelerometer(uint8_t channel, float x, float y, float z)
{

	// check buffer overflow
	if ((_cursor + LPP_ACCELEROMETER_SIZE + 2) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}

	int16_t vx = x * LPP_ACCELEROMETER_MULT;
	int16_t vy = y * LPP_ACCELEROMETER_MULT;
	int16_t vz = z * LPP_ACCELEROMETER_MULT;

	_buffer[_cursor++] = channel;
	_buffer[_cursor++] = LPP_ACCELEROMETER;
	_buffer[_cursor++] = vx >> 8;
	_buffer[_cursor++] = vx;
	_buffer[_cursor++] = vy >> 8;
	_buffer[_cursor++] = vy;
	_buffer[_cursor++] = vz >> 8;
	_buffer[_cursor++] = vz;

	return _cursor;
}

uint8_t RAK_LPP::addGyrometer(uint8_t channel, float x, float y, float z)
{

	// check buffer overflow
	if ((_cursor + LPP_GYROMETER_SIZE + 2) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}

	int16_t vx = x * LPP_GYROMETER_MULT;
	int16_t vy = y * LPP_GYROMETER_MULT;
	int16_t vz = z * LPP_GYROMETER_MULT;

	_buffer[_cursor++] = channel;
	_buffer[_cursor++] = LPP_GYROMETER;
	_buffer[_cursor++] = vx >> 8;
	_buffer[_cursor++] = vx;
	_buffer[_cursor++] = vy >> 8;
	_buffer[_cursor++] = vy;
	_buffer[_cursor++] = vz >> 8;
	_buffer[_cursor++] = vz;

	return _cursor;
}

uint8_t RAK_LPP::addGPS(uint8_t channel, float latitude, float longitude, float altitude)
{

	// check buffer overflow
	if ((_cursor + LPP_GPS_SIZE + 2) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}

	int32_t lat = latitude * LPP_GPS_LAT_LON_MULT;
	int32_t lon = longitude * LPP_GPS_LAT_LON_MULT;
	int32_t alt = altitude * LPP_GPS_ALT_MULT;

	_buffer[_cursor++] = channel;
	_buffer[_cursor++] = LPP_GPS;
	_buffer[_cursor++] = lat >> 16;
	_buffer[_cursor++] = lat >> 8;
	_buffer[_cursor++] = lat;
	_buffer[_cursor++] = lon >> 16;
	_buffer[_cursor++] = lon >> 8;
	_buffer[_cursor++] = lon;
	_buffer[_cursor++] = alt >> 16;
	_buffer[_cursor++] = alt >> 8;
	_buffer[_cursor++] = alt;

	return _cursor;
}

uint8_t RAK_LPP::addGNSS_4(uint8_t channel, int32_t latitude, int32_t longitude, int32_t altitude)
{
	// check buffer overflow
	if ((_cursor + LPP_GPS4_SIZE + 2) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}
	_buffer[_cursor++] = channel;
	_buffer[_cursor++] = LPP_GPS4;

	latLong_s pos_union;

	// Save default Cayenne LPP precision
	pos_union.val32 = latitude / 1000; // Cayenne LPP 0.0001 ° Signed MSB
	_buffer[_cursor++] = pos_union.val8[2];
	_buffer[_cursor++] = pos_union.val8[1];
	_buffer[_cursor++] = pos_union.val8[0];

	pos_union.val32 = longitude / 1000; // Cayenne LPP 0.0001 ° Signed MSB
	_buffer[_cursor++] = pos_union.val8[2];
	_buffer[_cursor++] = pos_union.val8[1];
	_buffer[_cursor++] = pos_union.val8[0];

	pos_union.val32 = altitude / 10; // Cayenne LPP 0.01 meter Signed MSB
	_buffer[_cursor++] = pos_union.val8[2];
	_buffer[_cursor++] = pos_union.val8[1];
	_buffer[_cursor++] = pos_union.val8[0];

	return _cursor;
}

uint8_t RAK_LPP::addGNSS_6(uint8_t channel, int32_t latitude, int32_t longitude, int32_t altitude)
{
	// check buffer overflow
	if ((_cursor + LPP_GPS6_SIZE + 2) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}
	_buffer[_cursor++] = channel;
	_buffer[_cursor++] = LPP_GPS6;

	latLong_s pos_union;

	pos_union.val32 = latitude / 10; // Custom 0.000001 ° Signed MSB
	_buffer[_cursor++] = pos_union.val8[3];
	_buffer[_cursor++] = pos_union.val8[2];
	_buffer[_cursor++] = pos_union.val8[1];
	_buffer[_cursor++] = pos_union.val8[0];

	pos_union.val32 = longitude / 10; // Custom 0.000001 ° Signed MSB
	_buffer[_cursor++] = pos_union.val8[3];
	_buffer[_cursor++] = pos_union.val8[2];
	_buffer[_cursor++] = pos_union.val8[1];
	_buffer[_cursor++] = pos_union.val8[0];

	pos_union.val32 = altitude / 10; // Cayenne LPP 0.01 meter Signed MSB
	_buffer[_cursor++] = pos_union.val8[2];
	_buffer[_cursor++] = pos_union.val8[1];
	_buffer[_cursor++] = pos_union.val8[0];

	return _cursor;
}

uint8_t RAK_LPP::addGNSS_H(int32_t latitude, int32_t longitude, int16_t altitude, int16_t accuracy, int16_t battery)
{
	// check buffer overflow
	if ((_cursor + LPP_GPSH_SIZE) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}

	latLong_s pos_union;

	pos_union.val32 = latitude / 100; // Custom 0.00001 ° Signed MSB
	_buffer[_cursor++] = pos_union.val8[0];
	_buffer[_cursor++] = pos_union.val8[1];
	_buffer[_cursor++] = pos_union.val8[2];
	_buffer[_cursor++] = pos_union.val8[3];

	pos_union.val32 = longitude / 100; // Custom 0.00001 ° Signed MSB
	_buffer[_cursor++] = pos_union.val8[0];
	_buffer[_cursor++] = pos_union.val8[1];
	_buffer[_cursor++] = pos_union.val8[2];
	_buffer[_cursor++] = pos_union.val8[3];

	pos_union.val32 = altitude / 1000;
	_buffer[_cursor++] = pos_union.val8[0];
	_buffer[_cursor++] = pos_union.val8[1];

	pos_union.val32 = accuracy;
	_buffer[_cursor++] = pos_union.val8[0];
	_buffer[_cursor++] = pos_union.val8[1];

	int_union_s batt_level;

	batt_level.val16 = battery;
	_buffer[_cursor++] = batt_level.val8[0];
	_buffer[_cursor++] = batt_level.val8[1];

	return _cursor;
}

uint8_t RAK_LPP::addGNSS_T(int32_t latitude, int32_t longitude, int16_t altitude, int16_t accuracy, int8_t sats)
{
	// check buffer overflow
	if ((_cursor + LPP_GPST_SIZE) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}

	// latitude = latitude / 1000;
	// longitude = longitude / 1000;
	altitude = altitude / 1000;

	uint64_t t = 0;
	uint64_t l = 0;
	if (longitude < 0)
	{
		t |= 0x800000000000L;
		l = -longitude;
	}
	else
	{
		l = longitude;
	}
	if (l / 10000000 >= 180)
	{
		l = 8372093;
	}
	else
	{
		if (l < 107)
		{
			l = 0;
		}
		else
		{
			l = (l - 107) / 215;
		}
	}
	t |= (l & 0x7FFFFF);

	if (latitude < 0)
	{
		t |= 0x400000000000L;
		l = -latitude;
	}
	else
	{
		l = latitude;
	}
	if (l / 10000000 >= 90)
	{
		l = 8333333;
	}
	else
	{
		if (l < 53)
		{
			l = 0;
		}
		else
		{
			l = (l - 53) / 108;
		}
	}
	t |= (l << 23) & 0x3FFFFF800000;

	// Add the location to the package
	_buffer[_cursor++] = (t >> 40) & 0xFF;
	_buffer[_cursor++] = (t >> 32) & 0xFF;
	_buffer[_cursor++] = (t >> 24) & 0xFF;
	_buffer[_cursor++] = (t >> 16) & 0xFF;
	_buffer[_cursor++] = (t >> 8) & 0xFF;
	_buffer[_cursor++] = (t) & 0xFF;
	_buffer[_cursor++] = ((altitude + 1000) >> 8) & 0xFF;
	_buffer[_cursor++] = ((altitude + 1000)) & 0xFF;
	_buffer[_cursor++] = (uint8_t)accuracy * 10;
	_buffer[_cursor++] = sats;

	return _cursor;
}

uint8_t RAK_LPP::addGNSS_T2(int32_t latitude, int32_t longitude, int16_t sequence_id)
{
	// check buffer overflow
	if ((_cursor + LPP_GPST_SIZE) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}

	// latitude = latitude / 1000;
	// longitude = longitude / 1000;
	// altitude = altitude / 1000;

	uint64_t t = 0;
	uint64_t l = 0;
	if (longitude < 0)
	{
		t |= 0x800000000000L;
		l = -longitude;
	}
	else
	{
		l = longitude;
	}
	if (l / 10000000 >= 180)
	{
		l = 8372093;
	}
	else
	{
		if (l < 107)
		{
			l = 0;
		}
		else
		{
			l = (l - 107) / 215;
		}
	}
	t |= (l & 0x7FFFFF);

	if (latitude < 0)
	{
		t |= 0x400000000000L;
		l = -latitude;
	}
	else
	{
		l = latitude;
	}
	if (l / 10000000 >= 90)
	{
		l = 8333333;
	}
	else
	{
		if (l < 53)
		{
			l = 0;
		}
		else
		{
			l = (l - 53) / 108;
		}
	}
	t |= (l << 23) & 0x3FFFFF800000;

	// Add the location to the package
	_buffer[_cursor++] = (t >> 40) & 0xFF;
	_buffer[_cursor++] = (t >> 32) & 0xFF;
	_buffer[_cursor++] = (t >> 24) & 0xFF;
	_buffer[_cursor++] = (t >> 16) & 0xFF;
	_buffer[_cursor++] = (t >> 8) & 0xFF;
	_buffer[_cursor++] = (t) & 0xFF;
	_buffer[_cursor++] = 0x56; // 'V'
	_buffer[_cursor++] = 0x32; // '2'
	_buffer[_cursor++] = (sequence_id >> 8) & 0xff;
	_buffer[_cursor++] = sequence_id & 0xff;

	return _cursor;
}

uint8_t RAK_LPP::addVoc_index(uint8_t channel, uint32_t voc_index)
{
	// check buffer overflow
	if ((_cursor + LPP_VOC_SIZE + 2) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}
	_buffer[_cursor++] = channel;
	_buffer[_cursor++] = LPP_VOC;

	int_union_s voc_union;

	voc_union.val16 = voc_index; // VOC index
	_buffer[_cursor++] = voc_union.val8[1];
	_buffer[_cursor++] = voc_union.val8[0];

	return _cursor;
}

uint8_t RAK_LPP::addDevID(uint8_t channel, uint8_t *dev_id)
{
	// check buffer overflow
	if ((_cursor + WB_DEV_ID_SIZE + 2) > _maxsize)
	{
		_error = LPP_ERROR_OVERFLOW;
		return 0;
	}
	_buffer[_cursor++] = channel;
	_buffer[_cursor++] = WB_DEV_ID;

	_buffer[_cursor++] = dev_id[0];
	_buffer[_cursor++] = dev_id[1];
	_buffer[_cursor++] = dev_id[2];
	_buffer[_cursor++] = dev_id[3];

	return _cursor;
}

// ----------------------------------------------------------------------------

float RAK_LPP::getValue(uint8_t *buffer, uint8_t size, uint32_t multiplier, bool is_signed)
{

	uint32_t value = 0;
	for (uint8_t i = 0; i < size; i++)
	{
		value = (value << 8) + buffer[i];
	}

	int sign = 1;
	if (is_signed)
	{
		uint32_t bit = 1ul << ((size * 8) - 1);
		if ((value & bit) == bit)
		{
			value = (bit << 1) - value;
			sign = -1;
		}
	}

	return sign * ((float)value / multiplier);
}

uint32_t RAK_LPP::getValue32(uint8_t *buffer, uint8_t size)
{

	uint32_t value = 0;
	for (uint8_t i = 0; i < size; i++)
	{
		value = (value << 8) + buffer[i];
	}

	return value;
}

#if defined(ARDUINO) || defined(IDF_VER)
uint8_t RAK_LPP::decode(uint8_t *buffer, uint8_t len, JsonArray root)
{

	uint8_t count = 0;
	uint8_t index = 0;

	while ((index + 2) < len)
	{

		count++;

		// Get channel #
		uint8_t channel = buffer[index++];

		// Get data type
		uint8_t type = buffer[index++];
		if (!isType(type))
		{
			_error = LPP_ERROR_UNKOWN_TYPE;
			return 0;
		}

		// Type definition
		uint8_t size = getTypeSize(type);
		uint32_t multiplier = getTypeMultiplier(type);
		bool is_signed = getTypeSigned(type);

		// Check buffer size
		if (index + size > len)
		{
			_error = LPP_ERROR_OVERFLOW;
			return 0;
		}

		// Init object
		JsonObject data = root.add<JsonObject>();
		data["channel"] = channel;
		data["type"] = type;
#ifdef ARDUINO
		data["name"] = String(getTypeName(type));
#else
		data["name"] = std::string(getTypeName(type));
#endif

		// Parse types
		if (false)
		{
		}
		else if (LPP_COLOUR == type)
		{

			JsonObject object = data["value"].to<JsonObject>();
			object["r"] = getValue(&buffer[index], 1, multiplier, is_signed);
			object["g"] = getValue(&buffer[index + 1], 1, multiplier, is_signed);
			object["b"] = getValue(&buffer[index + 2], 1, multiplier, is_signed);
		}
		else if (LPP_ACCELEROMETER == type)
		{
			JsonObject object = data["value"].to<JsonObject>();
			object["x"] = getValue(&buffer[index], 2, multiplier, is_signed);
			object["y"] = getValue(&buffer[index + 2], 2, multiplier, is_signed);
			object["z"] = getValue(&buffer[index + 4], 2, multiplier, is_signed);
		}
		else if (LPP_GYROMETER == type)
		{
			JsonObject object = data["value"].to<JsonObject>();
			object["x"] = getValue(&buffer[index], 2, multiplier, is_signed);
			object["y"] = getValue(&buffer[index + 2], 2, multiplier, is_signed);
			object["z"] = getValue(&buffer[index + 4], 2, multiplier, is_signed);
		}
		else if (LPP_GPS == type)
		{
			JsonObject object = data["value"].to<JsonObject>();
			object["latitude"] = getValue(&buffer[index], 3, 10000, is_signed);
			object["longitude"] = getValue(&buffer[index + 3], 3, 10000, is_signed);
			object["altitude"] = getValue(&buffer[index + 6], 3, 100, is_signed);
		}
		else if (LPP_GENERIC_SENSOR == type)
		{
			data["value"] = getValue32(&buffer[index], size);
		}
		else if (LPP_UNIXTIME == type)
		{
			data["value"] = getValue32(&buffer[index], size);
		}
		else if (LPP_VOC == type)
		{
			data["value"] = getValue32(&buffer[index], size);
		}
		else if (WB_DEV_ID == type)
		{
			data["value"] = getValue32(&buffer[index], size);
		}
		else
		{
			data["value"] = getValue(&buffer[index], size, multiplier, is_signed);
		}

		index += size;
	}

	return count;
}

uint8_t RAK_LPP::decodeMQTT(uint8_t *buffer, uint8_t len, JsonObject root)
{

	uint8_t count = 0;
	uint8_t index = 0;

	while ((index + 2) < len)
	{

		count++;

		// Get channel #
		uint8_t channel = buffer[index++];

		// Get data type
		uint8_t type = buffer[index++];
		if (!isType(type))
		{
			_error = LPP_ERROR_UNKOWN_TYPE;
			return 0;
		}

		// Type definition
		uint8_t size = getTypeSize(type);
		uint32_t multiplier = getTypeMultiplier(type);
		bool is_signed = getTypeSigned(type);

		// Check buffer size
		if (index + size > len)
		{
			_error = LPP_ERROR_OVERFLOW;
			return 0;
		}

		// Init object
		String name = String(getTypeName(type)) + "_" + String(channel);

		// Parse types
		if (false)
		{
		}
		else if (LPP_COLOUR == type)
		{
			String detail_name = String(getTypeName(type)) + "_r_" + String(channel);
			root[detail_name] = getValue(&buffer[index], 1, multiplier, is_signed);
			detail_name = name + String(getTypeName(type)) + "_g_" + String(channel);
			root[detail_name] = getValue(&buffer[index + 1], 1, multiplier, is_signed);
			detail_name = name + String(getTypeName(type)) + "_b_" + String(channel);
			root[detail_name] = getValue(&buffer[index + 2], 1, multiplier, is_signed);
		}
		else if (LPP_ACCELEROMETER == type)
		{
			String detail_name = String(getTypeName(type)) + "_x_" + String(channel);
			root[detail_name] = getValue(&buffer[index], 2, multiplier, is_signed);
			detail_name = name + String(getTypeName(type)) + "_y_" + String(channel);
			root[detail_name] = getValue(&buffer[index + 2], 2, multiplier, is_signed);
			detail_name = name + String(getTypeName(type)) + "_z_" + String(channel);
			root[detail_name] = getValue(&buffer[index + 4], 2, multiplier, is_signed);
		}
		else if (LPP_GYROMETER == type)
		{
			String detail_name = String(getTypeName(type)) + "_x_" + String(channel);
			root[detail_name] = getValue(&buffer[index], 2, multiplier, is_signed);
			detail_name = name + String(getTypeName(type)) + "_y_" + String(channel);
			root[detail_name] = getValue(&buffer[index + 2], 2, multiplier, is_signed);
			detail_name = name + String(getTypeName(type)) + "_z_" + String(channel);
			root[detail_name] = getValue(&buffer[index + 4], 2, multiplier, is_signed);
		}
		else if (LPP_GPS == type)
		{
			String detail_name = "latitude_" + String(channel);
			root[detail_name] = getValue(&buffer[index], 3, 10000, is_signed);
			detail_name = "longitude_" + String(channel);
			root[detail_name] = getValue(&buffer[index + 3], 3, 10000, is_signed);
			detail_name = "altitude_" + String(channel);
			root[detail_name] = getValue(&buffer[index + 6], 3, 100, is_signed);
		}
		else if (LPP_GENERIC_SENSOR == type)
		{
			root[name] = getValue32(&buffer[index], size);
		}
		else if (LPP_UNIXTIME == type)
		{
			root[name] = getValue32(&buffer[index], size);
		}
		else if (LPP_VOC == type)
		{
			root[name] = getValue32(&buffer[index], size);
		}
		else if (WB_DEV_ID == type)
		{
			root["node_id"] = getValue32(&buffer[index], size);
		}
		else
		{
			root[name] = getValue(&buffer[index], size, multiplier, is_signed);
		}

		index += size;
	}

	return count;
}

uint8_t RAK_LPP::decodeTTN(uint8_t *buffer, uint8_t len, JsonObject root)
{

	uint8_t count = 0;
	uint8_t index = 0;

	while ((index + 2) < len)
	{

		count++;

		// Get channel #
		uint8_t channel = buffer[index++];

		// Get data type
		uint8_t type = buffer[index++];
		if (!isType(type))
		{
			_error = LPP_ERROR_UNKOWN_TYPE;
			return 0;
		}

		// Type definition
		uint8_t size = getTypeSize(type);
		uint32_t multiplier = getTypeMultiplier(type);
		bool is_signed = getTypeSigned(type);

		// Check buffer size
		if (index + size > len)
		{
			_error = LPP_ERROR_OVERFLOW;
			return 0;
		}

		// Init object
		String name = String(getTypeName(type)) + "_" + channel;

		// Parse types
		if (false)
		{
		}
		else if (LPP_COLOUR == type)
		{
			JsonObject object = root[name].to<JsonObject>();
			object["r"] = getValue(&buffer[index], 1, multiplier, is_signed);
			object["g"] = getValue(&buffer[index + 1], 1, multiplier, is_signed);
			object["b"] = getValue(&buffer[index + 2], 1, multiplier, is_signed);
		}
		else if (LPP_ACCELEROMETER == type)
		{

			JsonObject object = root[name].to<JsonObject>();
			object["x"] = getValue(&buffer[index], 2, multiplier, is_signed);
			object["y"] = getValue(&buffer[index + 2], 2, multiplier, is_signed);
			object["z"] = getValue(&buffer[index + 4], 2, multiplier, is_signed);
		}
		else if (LPP_GYROMETER == type)
		{

			JsonObject object = root[name].to<JsonObject>();
			object["x"] = getValue(&buffer[index], 2, multiplier, is_signed);
			object["y"] = getValue(&buffer[index + 2], 2, multiplier, is_signed);
			object["z"] = getValue(&buffer[index + 4], 2, multiplier, is_signed);
		}
		else if (LPP_GPS == type)
		{

			JsonObject object = root[name].to<JsonObject>();
			object["latitude"] = getValue(&buffer[index], 3, 10000, is_signed);
			object["longitude"] = getValue(&buffer[index + 3], 3, 10000, is_signed);
			object["altitude"] = getValue(&buffer[index + 6], 3, 100, is_signed);
		}
		else if (LPP_GENERIC_SENSOR == type)
		{
			root[name] = getValue32(&buffer[index], size);
		}
		else if (LPP_UNIXTIME == type)
		{
			root[name] = getValue32(&buffer[index], size);
		}
		else if (LPP_VOC == type)
		{
			root[name] = getValue32(&buffer[index], size);
		}
		else if (WB_DEV_ID == type)
		{
			root[name] = getValue32(&buffer[index], size);
		}
		else
		{

			root[name] = getValue(&buffer[index], size, multiplier, is_signed);
		}

		index += size;
	}

	return count;
}
#endif
