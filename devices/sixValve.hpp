#ifndef FIMAS_SIXVALVE
#define FIMAS_SIXVALVE

//Include mbed header file
#include "mbed.h"

//Include the base device header file
#include "baseDevice.hpp"

/*
 * Six-port valve class containing key methods to control a six-port valve.
 * Based off of the baseDevice class
 */

class sixValve : public baseDevice {
    //Public API
public:
    //pin1 specifies the pin that the six-port valve is connected to
    //deviceID uniquely identifies the device
    sixValve(PinName pin1, PinName pin2, uint8_t pin1index, uint8_t pin2index, unsigned short deviceID);

    //Change the state of the six-port valve
    //Only two states are valid for the valve, position A and position B
    //Hence newstate is 0 for position A and any non-zero valve for position B
    unsigned short changeState(unsigned short newState);

    //Tests the operation of the valve
    //Returns 0 if the valve is operating normally, non-zero otherwise
    unsigned short testDevice();
};

#endif
