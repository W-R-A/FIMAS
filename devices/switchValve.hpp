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
    switchValve(PinName pin, uint8_t pinindex, unsigned short deviceID);

    //pin1 specifies the pin that the switching valve step input is connected to
    //pin2 specifies the pin that the switching valve home input is connected to
    //deviceID uniquely identifies the device
    switchValve(PinName pin1, PinName pin2, uint8_t pin1index, uint8_t pin2index, unsigned short deviceID);

    //Change the state of the switching valve
    //The valve can be in one of ten states and can operated in two modes
    unsigned short changeState(unsigned short newState);

    //Tests the operation of the valve
    //Returns 0 if the valve is operating normally, non-zero otherwise
    unsigned short testDevice(void);

    //Protected
protected:
    //create the signal pulses needed to change the state of the switching valve
    void pulse(void);

    //signal the pulse ticker to create the required pulse signals
    void doPulse(unsigned short pin, unsigned short pulses);

    //Thread to generate pulses
    Ticker pulse_ticker;

    //Control pin for thread
    unsigned short pin;
    
    //Number of pulses
    unsigned short noPulses;

    //Is the pulse active
    volatile bool pulseActive;

    //Rising or falling edge
    volatile bool falling;

};

#endif
