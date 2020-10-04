#ifndef FIMAS_HARDWARE_H
#define FIMAS_HARDWARE_H

//Include mbed header
#include "mbed.h"

//Include array header
#include <array>

//Include the base device class
#include "baseDevice.hpp"

//Include derived device classes
#include "perPump.hpp"
#include "sixValve.hpp"
#include "solValve.hpp"
#include "switchValve.hpp"

typedef enum {
    PERPUMP = 1, 
    SIXVALVE = 2, 
    SOLVALVE = 3, 
    SWITCHVALVE = 4
} devices_t;

//Define an array to hold the pins used for the digital outputs
extern const array<PinName, 8> digitalOutputs;

//Define an array to hold the pins used for the digital inputs
extern const array<PinName, 4> digitalInputs;

//Calculate the number of digital inputs and outpus defined
const short maxDevices = digitalOutputs.size() + digitalInputs.size();

#endif