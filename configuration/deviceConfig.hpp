#ifndef FIMAS_DEVICECONFIG
#define FIMAS_DEVICECONFIG

//Include the mbed header file
#include "mbed.h"

//Include the serial interface header file
#include "serialInterface.hpp"

//Include the string header
#include <string>

//Include headers to parse strings
#include<vector>

//Include sstream to work with parsing serial data
#include<sstream>

//Function Prototypes
uint8_t configDevicesSerial(std::string const& devConfig);

#endif