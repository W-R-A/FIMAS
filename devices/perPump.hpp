#ifndef FIMAS_PERPUMP
#define FIMAS_PERPUMP

//Include mbed header file
#include "mbed.h"

//Include the base device header file
#include "baseDevice.hpp"

/*
 * Peristaltic Pump class containing key methods to control a Peristaltic Pump.
 * Based off of the baseDevice class
 */

class perPump : public baseDevice {
    //Public API
public:
    //pin specifies the pin that the Peristaltic Pump is connected to
    //deviceID uniquely identifies the device
    perPump(PinName pin, unsigned short deviceID);
}

#endif
