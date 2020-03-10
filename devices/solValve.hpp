#ifndef FIMAS_SOLVALVE
#define FIMAS_SOLVALVE

//Include mbed header file
#include "mbed.h"

//Include the base device header file
#include "baseDevice.hpp"

/*
 * Solenoid valve class containing key methods to control a solenoid valve.
 * Based off of the baseDevice class
 */

class solValve : public baseDevice {
    //Public API
public:
    //pin specifies the pin that the solenoid valve is connected to
    //deviceID uniquely identifies the device
    solValve(PinName pin, unsigned short deviceID);
}

#endif
