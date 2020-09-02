#ifndef FIMAS_DEVICECONFIG
#define FIMAS_DEVICECONFIG

//Include the mbed header file
#include "mbed.h"


//Include the string header
#include <string>

//Include headers to parse strings
#include <vector>

//Include sstream to work with parsing serial data
#include <sstream>

//Include the data manager header file
#include "dataManager.hpp"

//Function Prototypes

//Configure devices over the serial port
//Pass in the key parameters as a c++ string to create the device
//Returns zero on sucess, non zero on failure
uint8_t configDevicesSerial(std::string const& devConfig);

//Test a device with given ID
//Returns a string with the results of the tests
std::string testDeviceSerial(std::string const& devTest);

#endif