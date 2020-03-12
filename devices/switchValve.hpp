#ifndef FIMAS_SWITCHVALVE
#define FIMAS_SWITCHVALVE

//Include mbed header file
#include "mbed.h"

//Include the base device header file
#include "baseDevice.hpp"

/*
 * Switching valve class containing key methods to control a switching valve.
 * Based off of the baseDevice class
 */

class switchValve : public baseDevice {
    //Public API
public:
    //pin specifies the pin that the switching valve step input is connected to
    //deviceID uniquely identifies the device
    switchValve(PinName pin, unsigned short deviceID);

    //pin1 specifies the pin that the switching valve step input is connected to
    //pin2 specifies the pin that the switching valve home input is connected to
    //deviceID uniquely identifies the device
    switchValve(PinName pin1, PinName pin2, unsigned short deviceID);

    //Change the state of the switching valve
    //The valve can be in one of ten states and can operated in two modes
    unsigned short changeState(unsigned short newState);

    //Protected
protected:
    //create the signal pulses needed to change the state of the switching valve
    //pin determines the pin to generate the pulses on
    //noPulses determines the number of pulses generated
    void pulse(unsigned short pin, unsigned short noPulses);
};

#endif
