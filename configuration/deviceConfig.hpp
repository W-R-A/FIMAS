#ifndef FIMAS_DEVICECONFIG
#define FIMAS_DEVICECONFIG

//Include the mbed header file
#include "mbed.h"

//Include theJSON Parser header file
#include "MbedJSONValue.h"

//Include the hardware header file
#include "hardware.hpp"

//Include the serial interface header file
#include "serialInterface.hpp"

//Include the string header to assist with working with JSON
#include <string>

//Include headers to parse strings
#include<vector>
#include<sstream>

//Function Prototypes
uint8_t configDevicesSerial(std::string const& devConfig);

#endif