#include "perPump.hpp"

//pin specifies the pin that the Peristaltic Pump is connected to
//deviceID uniquely identifies the device
//Constructor is inherited from baseDevice
perPump::perPump(PinName pin, uint8_t pinindex, unsigned short deviceID) : baseDevice(pin, pinindex, deviceID) {

    //The name of the device 
    this->devType = "Peristaltic Pump";
}

//Change the state of the Peristaltic Pump
//Only two states are valid for the pump, on and off
//Hence newstate is 0 for off and any non-zero value for on
unsigned short perPump::changeState(unsigned short newState) {
    //If the newstate is non-zero, and the pump is not already running, turn the pump on
    if (newState) {
        if (this->state == 1) {
            return this->state;
        } else {
            this->controlPin1->write(1);
            updateState(1);
            return this->state;
        }
    }
    //If the newstate is zero, and the pump is running, turn the pump off
    else {
        if (this->state == 0) {
            return this->state;
        } else {
            this->controlPin1->write(0);
            updateState(0);
            return this->state;
        }
    }
}

//Tests the operation of the pump
//Returns 0 if the pump is operating normally, non-zero otherwise
unsigned short perPump::testDevice(void) {
    changeState(1);
    thread_sleep_for(500);
    changeState(0);
    return 0;
}