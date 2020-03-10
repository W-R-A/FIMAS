#include "baseDevice.hpp"

//Constructor
//pin specifies the pin that the device is connected to.
//deviceID uniquely identifies the device
baseDevice::baseDevice(PinName pin, unsigned short deviceID) {
    //Initialise the control pin used, default output state of low
    this->controlPin1 = new DigitalOut(pin, 0);

    //Set the device ID
    this->devID = deviceID;

    //Set that this is a one pin device
    this->noPins = 1;

    //Initialise the state to be zero
    this->state = 0;
}

//Constructor
//pin1 and pin2 specify the pin(s) that the device is connected to.
//deviceID uniquely identifies the device
baseDevice::baseDevice(PinName pin1, PinName pin2, unsigned short deviceID) {
    //Initialise the control pin used, default output state of low
    this->controlPin1 = new DigitalOut(pin1, 0);

    //Initialise the second control pin used, default output state of low
    this->controlPin2 = new DigitalOut(pin2, 0);

    //Set the device ID
    this->devID = deviceID;

    //Set that this is a two pin device
    this->noPins = 2;

    //Initialise the state to be zero
    this->state = 0;
}

//Destructor
baseDevice::~baseDevice() {
    //Delete control pin one
    delete controlPin1;

    //If two pins used, delete the second control pin
    if (this->noPins == 2) {
        delete controlPin2;
    }
}

//Change the state of the internal state variable in an interrupt-safe way
void baseDevice::changeState(int newState) {
    //Disable interrupts during critical section of a state change
    CriticalSectionLock lock;

    //Update state variable
    state = newState;
}

//Get the ID of the device
unsigned short baseDevice::getID(void) {
    return devID;
}