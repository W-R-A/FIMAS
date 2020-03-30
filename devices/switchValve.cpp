#include "switchValve.hpp"

////pin specifies the pin that the switching valve step input is connected to
//deviceID uniquely identifies the device
//Constructor is inhertited from baseDevice
switchValve::switchValve(PinName pin, unsigned short deviceID) : baseDevice(pin, deviceID) {}

//pin1 specifies the pin that the switching valve step input is connected to
//pin2 specifies the pin that the switching valve home input is connected to
//deviceID uniquely identifies the device
//Constructor is inhertited from baseDevice
switchValve::switchValve(PinName pin1, PinName pin2, unsigned short deviceID) : baseDevice(pin1, pin2, deviceID) {}

//create the signal pulses needed to change the state of the switching valve
//pin determines the pin to generate the pulses on
//noPulses determines the number of pulses generated
//According to the data sheet, each pulse must be at least 30ms in duration, so a delay of 50ms is used
void switchValve::pulse(unsigned short pin, unsigned short noPulses)
{
    for (int i = 0; i < noPulses; i++) {
        if (pin == 1) {
            this->controlPin1->write(1);
            thread_sleep_for(500);
            this->controlPin1->write(0);
        }
        else {
            this->controlPin2->write(1);
            thread_sleep_for(500);
            this->controlPin2->write(0);
        }
    }
}

//Change the state of the switching valve
//The valve can be in one of ten states and can operated in two modes
//Hence newstate is the desired state of the valve
unsigned short switchValve::changeState(unsigned short newState)
{
    //Check if operating in 1 or 2 pin mode
    //If in single pin mode - need to cycle through all configurations to get to the derired state
    if (this->noPins == 1) {
        //Bounds Check
        if (newState > 9) {
            printError("State out of bounds");
        }
        else {
            //Define how many pulses are needed to move to the next state
            unsigned short pulses = 0;
            //If the current state of greater than th desired state, get back to position zero before moving to the desired state
            if (this->state > newState) {
                pulses = 9 - this->state;
                pulses = pulses + newState;
            }
            else {
                pulses = newState;
            }

            //Change to desired state
            pulse(1, pulses);

            updateState(newState);
        }
    }
    //If in 2 pin mode, reset to home before cycling through to the desired state
    else {
        //Bounds Check
        if (newState > 9) {
            printError("State out of bounds");
        }
        else {
            //Reset position
            pulse(2, newState);

            //Change to desired state
            pulse(1, newState);

            updateState(newState);
        }
    }
    return this->state;
}