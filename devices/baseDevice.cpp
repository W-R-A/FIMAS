#include "baseDevice.hpp"

//Constructor
//pin specifies the pin that the device is connected to.
//deviceID uniquely identifies the device
baseDevice::baseDevice(PinName pin, unsigned short deviceID) {
    //Initialise the control pin used, default output state of low
    this->controlPin1 = new DigitalOut(pin, 0);

    //Set the device ID
    this->devID = deviceID;
}

//Constructor
//Pin specifies the pin that the pump is connected to
perPump::perPump(PinName pin, unsigned short deviceID) {
    this->controlPin = new DigitalOut(pin, state);
    this->devID = deviceID;
}

//Destructor
perPump::~perPump() {
    delete controlPin;
}

//Change the state of the
//0 turns the pump off, 1 turns the pump on
void perPump::changeState(int newState) {
    //Disable interrupts during critical section of a state change
    CriticalSectionLock lock;

    //Update state variable
    state = newState;

    //Update device control pin
    controlPin->write(state);
}

unsigned short perPump::getID(void) {
    return devID;
}
