| <img src="./assets/RAK-Whirls.png" alt="RAKWireless" width=500%> | <img src="./assets/RUI3.jpg" alt="RUI3" width=15%> | <img src="./assets/rakstar.jpg" alt="RAKstar" > |    
| :-: | :-: | :-: |     

# ⚠️ BETA! ⚠️
This library is still in testing phase!

# RUI3/Arduino library WisBlock and WisDuo modules for Low Power Payload decoding. Based on the CayenneLPP library from ElectronicCats

This library is based on the CayenneLPP library with sensor definitions that are often used in RUI3 and WisBlock examples.    
The extensions are 
- Add short GNSS location data
- Add precise GNSS location data
- Add Fieldtester data packet
- Add VOC sensor data
- Add device ID, used for LoRa P2P and LoRa Mesh applications

The library was as well updated to work with ArduinoJson V7.x

----

# Installation

In Arduino IDE open Sketch->Include Library->Manage Libraries then search for RUI3-WisBlock-Cayenne.

In PlatformIO open PlatformIO Home, switch to libraries and search for RUI3-WisBlock-Cayenne.
Or install the library project dependencies by adding

```log
lib_deps =
  beegee-tokyo/RAK_LPP
```

into **`platformio.ini`**

For manual installation download the archive, unzip it and place the RUI3-WisBlock-Cayenne folder into the library directory.
In Arduino IDE this is usually <arduinosketchfolder>/libraries/
In PlatformIO this is usually <project-folder/lib>

----

# Usage

To use it, declare an instance of the RAK_LPP class.

----

# Example

- [Decode-payload](./examples/Decode-payload) ArduinoIDE example how to create a payload and how to decode a payload
- [RAK3112-P2P-MQTT-Gateway-PIO](./examples/RAK3112-P2P-MQTT-Gateway-PIO/) LoRa P2P to MQTT broker bridge example.
- [RUI3 Best Practice](https://github.com/RAKWireless/RUI3-Best-Practice) Collection of RUI3 example code.

----

# This library provides the following methods:

## Construct a new RAK_LPP object     
The constructor takes a buffer size for the initialization.     
For LoRa, the buffer size should be limited to 255 bytes. For LoRaWAN, the buffer size can be adjusted depending on the LoRaWAN region and used datarate, which defines the max allowed payload size

```cpp     
RAK_LPP g_solution_data(uint8_t size);     
```     
### Parameters:
@param size Size of buffer for the CayenneLPP formated payload
    
### Usage:     
```cpp     
RAK_LPP g_solution_data(255);
```
	 
## All existing functions from the ElectronicCats CayenneLPP library are supported.

```cpp
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
```

## Add short GNSS location data (WisBlock standard format)     
Adds location data as 3 byte lon/lat 0.0001 °, 3 bytes alt 0.01 meter (Cayenne LPP default)      

```cpp     
uint8_t addGNSS_4(uint8_t channel, int32_t latitude, int32_t longitude, int32_t altitude);    
```     
### Parameters:
@param channel sensor ID     
@param latitude (latitude in degrees * 10^7)     
@param longitude (longitude * 10^7)          
@param altitude (altitude * 10^3)          
@return bytes added to the buffer or 0 if the buffer is full 
    
### Usage:     
```cpp     
g_solution_data.addGNSS_4(LPP_CHANNEL_GPS, latitude, longitude, altitude);    
```
	 
   
## Add precise GNSS location data (WisBlock standard format)     
Adds location data as 4 byte lon/lat 0.000001 °, 3 bytes alt 0.01 meter (Customized Cayenne LPP, higher precision)  

   
```cpp     
uint8_t addGNSS_6(uint8_t channel, int32_t latitude, int32_t longitude, int32_t altitude);    
```     
### Parameters:
@param channel sensor ID     
@param latitude (latitude in degrees * 10^7)     
@param longitude (longitude * 10^7)          
@param altitude (altitude * 10^3)          
@return bytes added to the buffer or 0 if the buffer is full 
    
### Usage:     
```cpp     
g_solution_data.addGNSS_6(LPP_CHANNEL_GPS, latitude, longitude, altitude);    
```
	 
     
## Add VOC sensor value     
Adds VOC sensor value in Cayenne LPP format.    
This can be used for RAK12047 SGP40 VOC sensor and for the RAK12039 PMSA003I particulate matter sensor  
    
```cpp     
	uint8_t addVoc_index(uint8_t channel, uint32_t voc_index);
```     
### Parameters:
@param channel sensor ID     
@param voc measured VOC or PM value     
@return bytes added to the buffer or 0 if the buffer is full 

    
### Usage:     
```cpp     
g_solution_data.addVoc_index(LPP_CHANNEL_VOC, voc_index);
```


## Add device ID     
Adds a 4 byte device address to the payload.    
This can be used for LoRa P2P or LoRa Mesh application to add an device identifier to the payload  
    
```cpp     
	uint8_t addDevID(uint8_t channel, uint8_t *dev_id);
```     
### Parameters:
@param channel sensor ID     
@param dev_id array of 4 bytes containing the device address/ID     
@return bytes added to the buffer or 0 if the buffer is full 

    
### Usage:     
```cpp     
uint8_t dev_id[8];
api.lorawan.deui.get(dev_id, 8);
g_solution_data.addDevID(LPP_CHANNEL_DEVID, &dev_id[4]);
```


## Add GNSS location data in Helium Mapper format     
Adds location data in Helium Mapper format.    
This is not Cayenne LPP format, it is a special data format used for Helium Mapper applications  

   
```cpp     
uint8_t addGNSS_H(int32_t latitude, int32_t longitude, int16_t altitude, int16_t accuracy, int16_t battery);    
```     
### Parameters:
@param latitude (latitude in degrees * 10^7)     
@param longitude (longitude * 10^7)          
@param altitude (altitude * 10^3)          
@param accuracy (accuracy * 10^2)          
@param battery (battery in mV * 10^2)          
@return bytes added to the buffer or 0 if the buffer is full 
    
### Usage:     
```cpp     
g_data_packet.addGNSS_H(latitude, longitude, altitude, accuracy, read_batt());    
```
	 
     
## Add GNSS location data in FieldTester format     
Adds location data in FieldTester format.    
This is not Cayenne LPP format, it is a special data format used for FieldTester applications  

    
```cpp     
uint8_t addGNSS_T(int32_t latitude, int32_t longitude, int16_t altitude, int16_t accuracy, int8_t sats);    
```     
### Parameters:
@param latitude (latitude in degrees * 10^7)     
@param longitude (longitude * 10^7)          
@param altitude (altitude in millimeter)          
@param accuracy (accuracy * 10^2)          
@param sats number of satellites          
@return bytes added to the buffer or 0 if the buffer is full 

    
### Usage:     
```cpp     
g_solution_data.addGNSS_T(latitude, longitude, altitude / 1000, accuracy, satellites);
```
	 
     
## Add GNSS location data in FieldTester V2 format     
Adds location data in FieldTester format.    
This is not Cayenne LPP format, it is a special data format used for FieldTester V2 applications  
    
```cpp     
	uint8_t addGNSS_T2(int32_t latitude, int32_t longitude, int16_t sequence_id);
```     
### Parameters:
@param latitude (latitude in degrees * 10^7)     
@param longitude (longitude * 10^7)          
@param sequence_id           
@return bytes added to the buffer or 0 if the buffer is full 

    
### Usage:     
```cpp     
g_solution_data.addGNSS_T2(latitude, longitude, (int16_t)packet_num);
```
	 
     
----
----

# LoRa® is a registered trademark or service mark of Semtech Corporation or its affiliates. 

----

# LoRaWAN® is a licensed mark.