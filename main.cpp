/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <string>


//Define DigitalOutputs for the utilised devices
DigitalOut washPump(PE_14);
DigitalOut samplePump(PE_15);
DigitalOut switchValve(PE_12);
DigitalOut solenoidValve(PE_8);


//Define how many devices there are
#define NUMBER_DEVICES 4

//Define enumerated types for the devices
enum DEVICE {WASHPUMP, SAMPLEPUMP, SWITCHVALVE, SOLENOIDVALVE}; 

//Define a structure to hold the timing parameters
typedef struct {
    enum DEVICE device;
    int timeOn;
    int timeOff;
} deviceTime;

//Define a structure to hold the timing parameters for all the devices in a step
typedef struct {
    deviceTime StepTimes[NUMBER_DEVICES];
} step;


//Define a routine, consisting of 2 steps
#define STEPS 2
step routine[STEPS] = {routine[0].StepTimes[0] = {WASHPUMP, 0, 20}, routine[0].StepTimes[1] = {WASHPUMP, 0, 20}, routine[0].StepTimes[2] = {WASHPUMP, 0, 20}, routine[0].StepTimes[3] = {WASHPUMP, 0, 20}};


//Turn off device
void turnOff(enum DEVICE device) {
    switch (device) {
        case WASHPUMP : {
            //turn off wash pump
            break;
        }

        case SAMPLEPUMP : {
            //turn off sample pump
            break;
        } 

        case SWITCHVALVE : {
            //turn off switch valve
            break;
        }

        case SOLENOIDVALVE : {
            //turn off solenoid valve
            break;
        }

        default: {
            //Default case, should not happen
            //Error log - unregcognised device passed to turnOff
            break;
        }
    }
}


//Turn on device
void turnOn(enum DEVICE device) {
    switch (device) {
        case WASHPUMP : {
            //turn on wash pump
            break;
        }

        case SAMPLEPUMP : {
            //turn on sample pump
            break;
        } 

        case SWITCHVALVE : {
            //turn on switch valve
            break;
        }

        case SOLENOIDVALVE : {
            //turn on solenoid valve
            break;
        }

        default: {
            //Default case, should not happen
            //Error log - unregcognised device passed to turnOn
            break;
        }
    }
}


//Device timings
void checkTiming(void) {

    //Temp, bind to rtc for accuracy
    static int timeElapsed = 0;

    //Loop through structures, read the timing data and take action if appropiate
    for (int i = 0; i < STEPS; i++) {
        for (int j = 0; j < NUMBER_DEVICES; j++) {

            //Is it time to turn a device on
            if (timeElapsed == routine[STEPS].StepTimes[NUMBER_DEVICES].timeOn) {
                //Turn on the device
                turnOn(routine[STEPS].StepTimes[NUMBER_DEVICES].device)
            }

            //Is it time to turn a device off
            else if (timeElapsed == routine[STEPS].StepTimes[NUMBER_DEVICES].timeOff) {
                //Turn off the device
                turnOff(routine[STEPS].StepTimes[NUMBER_DEVICES].device);
            }
        }
    }
    //Increment timeElapsed
    timeElapsed++;
}


int main() {
	
    routine[0].StepTimes[0].device = SAMPLEPUMP;
	
    enum DEVICE x = routine[0].StepTimes[0].device;// = WASHPUMP;
	
    
	
	
	
	// Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        led = !led;
        thread_sleep_for(BLINKING_RATE_MS);
    }
}
