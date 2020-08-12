#include "sixValve.hpp"

//pin specifies the pin that the solenoid valve is connected to
//deviceID uniquely identifies the device
//Constructor is inhertited from baseDevice
sixValve::sixValve(PinName pin1, PinName pin2, uint8_t pin1index, uint8_t pin2index, unsigned short deviceID) : baseDevice(pin1, pin2, pin1index, pin2index, deviceID)
{
    this->controlPin2->write(0);
    this->controlPin1->write(1);

    //The name of the device 
    this->devType = "Six-Port Valve";
}

//Change the state of the six-port valve
//Only two states are valid for the valve, position A and position B
//Hence newstate is 0 for position A and any non-zero valve for position B
unsigned short sixValve::changeState(unsigned short newState)
{
    //If the newstate is non-zero, and the valve is not already in position B, change the valve to position B
    if (newState) {
        if (this->state == 1) {
            return this->state;
        }
        else {
            this->controlPin1->write(0);
            this->controlPin2->write(1);
            updateState(1);
            return this->state;
        }
    }
    //If the newstate is zero, and the valve is not already in position A, change the valve to position A
    else {
        if (this->state == 0) {
            return this->state;
        }
        else {
            this->controlPin2->write(0);
            this->controlPin1->write(1);
            updateState(0);
            return this->state;
        }
    }
}

//Tests the operation of the valve
//Returns 0 if the valve is operating normally, non-zero otherwise
unsigned short sixValve::testDevice() {
    changeState(1);
    thread_sleep_for(500);
    changeState(0);
    return 0;
}