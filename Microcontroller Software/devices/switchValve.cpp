#include "switchValve.hpp"

////pin specifies the pin that the switching valve step input is connected to
//deviceID uniquely identifies the device
//Constructor is inhertited from baseDevice
switchValve::switchValve(PinName pin, uint8_t pinindex, unsigned short deviceID) : baseDevice(pin, pinindex, deviceID) {
    
    //The name of the device 
    this->devType = "Switching Valve";

    //Deactivate pulsing
    this->pulseActive = 0;

     //Start pulse ticker
    pulse_ticker.attach(callback(this, &switchValve::pulse), 0.5f);
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

    //Start pulse ticker
    pulse_ticker.attach(callback(this, &switchValve::pulse), 0.5f);
}

//create the signal pulses needed to change the state of the switching valve
//According to the data sheet, each pulse must be at least 30ms in duration, so a delay of 50ms is used
void switchValve::pulse(void) {

    if (this->pulseActive) {
        if (this->noPulses) {
            if (this->pin == 1) {
                if (this->falling) {
                    this->controlPin1->write(0);
                    this->falling = 0;
                    this->noPulses = this->noPulses - 1;
                } else {
                    this->controlPin1->write(1);
                    this->falling = 1;
                }                    
            }
            else {
                if (this->falling) {
                    this->controlPin2->write(0);
                    this->falling = 0;
                    this->noPulses = this->noPulses - 1;
                } else {
                    this->controlPin2->write(1);
                    this->falling = 1;
                }
            }
        //Finished pulse
        } else {
            this->falling = 0;
            this->pulseActive = 0;  
        }
    }     
}

//Signal the pulse thread to generate the required signals
void switchValve::doPulse(unsigned short pin, unsigned short pulses) {

    //Change to desired pin
    this->pin = pin;

    this->noPulses = pulses;

    this->falling = 0;

    //Block until thread is free
    while (this->pulseActive == 1 ) {}

    //Activate ticker
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
            doPulse(2, 1);

            //Change to desired state
            doPulse(1, newState);

            updateState(newState);
        }
    }
    return this->state;
}


//Tests the operation of the valve
//Returns 0 if the valve is operating normally, non-zero otherwise
unsigned short switchValve::testDevice(void) {
    for (int i = 0; i < 10; i++) {
        changeState(i);
        thread_sleep_for(500);
    }
    
    return 0;
}
