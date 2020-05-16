#include "solValve.hpp"

//pin specifies the pin that the solenoid valve is connected to
//deviceID uniquely identifies the device
//Constructor is inhertited from baseDevice
solValve::solValve(PinName pin, unsigned short deviceID) : baseDevice(pin, deviceID) {}

//Change the state of the solenoid valve
//Only two states are valid for the valve, on and off
//Hence newstate is 0 for off and any non-zero valve for on
unsigned short solValve::changeState(unsigned short newState)
{
    //If the newstate is non-zero, and the pump is not already running, turn the valve on
    if (newState) {
        if (this->state == 1) {
            return this->state;
        }
        else {
            this->controlPin1->write(1);
            updateState(1);
            return this->state;
        }
    }
    //If the newstate is zero, and the pump is running, turn the valve off
    else {
        if (this->state == 0) {
            return this->state;
        }
        else {
            this->controlPin1->write(0);
            updateState(0);
            return this->state;
        }
    }
}

//Tests the operation of the valve
//Returns 0 if the valve is operating normally, non-zero otherwise
unsigned short solValve::testDevice() {
    changeState(1);
    thread_sleep_for(500);
    changeState(0);
    return 0;
}