/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <string>


//Define DigitalOutputs for the utilised devices
DigitalOut washPump(D7);
DigitalOut samplePump(D6);
DigitalOut switchValve(D5);
DigitalOut solenoidValve(D4);


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
#define STEPS 1
step routine[STEPS] = {routine[0].StepTimes[0] = {WASHPUMP, 0, 20}, routine[0].StepTimes[1] = {SAMPLEPUMP, 5, 25}, routine[0].StepTimes[2] = {SWITCHVALVE, 10, 20}, routine[0].StepTimes[3] = {SOLENOIDVALVE, 15, 30}};


//Turn off device
void turnOff(enum DEVICE device) {
    switch (device) {
        case WASHPUMP : {
            //Turn off the wash pump
            washPump = 0;
            break;
        }

        case SAMPLEPUMP : {
            //Turn off the sample pump
            samplePump = 0;
            break;
        } 

        case SWITCHVALVE : {
            //Turn off the switch valve - Position A
            switchValve = 0;
            break;
        }

        case SOLENOIDVALVE : {
            //Turn off the solenoid valve
            solenoidValve = 0;
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
            //Turn on the wash pump
            washPump = 1;
            break;
        }

        case SAMPLEPUMP : {
            //Turn on the sample pump
            samplePump = 1;
            break;
        } 

        case SWITCHVALVE : {
            //Turn on the switch valve - Position B
            switchValve = 1;
            break;
        }

        case SOLENOIDVALVE : {
            //Turn on the solenoid valve
            solenoidValve = 1;
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

    turnOn(WASHPUMP);
    turnOn(SAMPLEPUMP);
    turnOn(SWITCHVALVE);
    turnOn(SOLENOIDVALVE);

    thread_sleep_for(1000);

    turnOff(WASHPUMP);
    turnOff(SAMPLEPUMP);
    turnOff(SWITCHVALVE);
    turnOff(SOLENOIDVALVE);

    thread_sleep_for(1000);

    while (true) {
        checkTiming();
        thread_sleep_for(1000);
    }
}
