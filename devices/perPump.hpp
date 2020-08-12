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
    perPump(PinName pin, uint8_t pinindex, unsigned short deviceID);

    //Change the state of the Peristaltic Pump
    //Only two states are valid for the pump, on and off
    //Hence newstate is 0 for off and any non-zero value for on
    unsigned short changeState(unsigned short newState);

    //Tests the operation of the pump
    //Returns 0 if the pump is operating normally, non-zero otherwise
    unsigned short testDevice();
};

#endif
