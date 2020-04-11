#ifndef FIMAS_DEVICECONFIG
#define FIMAS_DEVICECONFIG

//Include the mbed header file
#include "mbed.h"

//Include theJSON Parser header file
#include "MbedJSONValue.h"

//Include the hardware header file
#include "hardware.hpp"

//Incldue the serial interface header file
#include "serialInterface.hpp"

//Function Prototypes
uint8_t configDevices(const char * configJSON);

#endif