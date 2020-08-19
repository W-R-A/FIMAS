#include "switchValve.hpp"

////pin specifies the pin that the switching valve step input is connected to
//deviceID uniquely identifies the device
//Constructor is inhertited from baseDevice
switchValve::switchValve(PinName pin, uint8_t pinindex, unsigned short deviceID) : baseDevice(pin, pinindex, deviceID) {
    
    //The name of the device 
    this->devType = "Switching Valve";

    //Deactivate pulsing
    this->pulseActive = 0;

    //Start pulse thread
    pulseThread.start(callback(pulse, this));
}

//pin1 specifies the pin that the switching valve step input is connected to
//pin2 specifies the pin that the switching valve home input is connected to
//deviceID uniquely identifies the device
//Constructor is inhertited from baseDevice
switchValve::switchValve(PinName pin1, PinName pin2, uint8_t pin1index, uint8_t pin2index, unsigned short deviceID) : baseDevice(pin1, pin2, pin1index, pin2index, deviceID) {
    
    //The name of the device 
    this->devType = "Switching Valve";

    //Deactivate pulsing
    this->pulseActive = 0;

    //Start pulse thread
    pulseThread.start(callback(pulse, this));
}

//create the signal pulses needed to change the state of the switching valve
//pin determines the pin to generate the pulses on
//noPulses determines the number of pulses generated
//According to the data sheet, each pulse must be at least 30ms in duration, so a delay of 50ms is used
//https://os.mbed.com/users/AVELARDEV/code/LibThreadProcess//file/3b34689ec230/BlinkLed.h/
void switchValve::pulse(void const *argument)
{
    //Convert pointer to class type
    switchValve* self = (switchValve*)argument;

    //Infinite loop 
    while (1) {
        if (self->pulseActive) {
            for (int i = 0; i < self->noPulses; i++) {
                if (self->pin == 1) {
                    self->controlPin1->write(1);
                    ThisThread::sleep_for(500);
                    self->controlPin1->write(0);
                }
                else {
                    self->controlPin2->write(1);
                    ThisThread::sleep_for(500);
                    self->controlPin2->write(0);
                }
            }
        }
        self->pulseActive = 0;
    }
    
}

//Signal the pulse thread to generate the required signals
void switchValve::doPulse(unsigned short pin, unsigned short pulses) {

    //Change to desired state
    this->pin = 1;

    this->noPulses = pulses;

    //Block until thread is free
    while (this->pulseActive == 1 ) {}

    //Activate thread
    this->pulseActive = 1;
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

            doPulse(1, newState);

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
            doPulse(2, newState);

            //Change to desired state
            doPulse(1, newState);

            updateState(newState);
        }
    }
    return this->state;
}
