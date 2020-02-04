/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

/* FIMAS Project
 * Ross Andrewartha, January 2020
 */


//Define enumerated types for the devices used
enum DEVICE {WASHPUMP, SAMPLEPUMP, SWITCHVALVE, SOLENOIDVALVE}; 

//Declare how many devices there are defined above
#define NUMBER_DEVICES 4

//Declare DigitalOutputs for the utilised devices
DigitalOut washPump(D7);
DigitalOut samplePump(D6);
DigitalOut switchValve(D5);
DigitalOut solenoidValve(D4);

//Declare input userbutton as trigger
DigitalIn userButton(USER_BUTTON);

//Define a structure to hold the timing parameters for each device for each step
typedef struct {
    enum DEVICE device;
    signed int timeOn;
    signed int timeOff;
} deviceTime;


//Define a structure to hold the timing parameters for all the devices in a step
typedef struct {
    deviceTime StepTimes[NUMBER_DEVICES];
} step;

//Declare how many steps the routine will be
#define STEPS 3

//Define a routine, consisting of STEPS steps
step routine[STEPS] = {
    //Declare timing for step 1
    routine[0].StepTimes[0] = {WASHPUMP, 0, 15}, 
    routine[0].StepTimes[1] = {SAMPLEPUMP, 15, 75}, 
    routine[0].StepTimes[2] = {SWITCHVALVE, 0, 2},
    routine[0].StepTimes[3] = {SOLENOIDVALVE, 0, 15},

    //Declare timing for step 2
    routine[1].StepTimes[0] = {WASHPUMP, 225, 240}, 
    routine[1].StepTimes[1] = {SAMPLEPUMP, 240, 300}, 
    routine[1].StepTimes[2] = {SWITCHVALVE, 225, 227},
    routine[1].StepTimes[3] = {SOLENOIDVALVE, 225, 240},

    //Declare timing for step 3
    routine[2].StepTimes[0] = {WASHPUMP, 450, 465}, 
    routine[2].StepTimes[1] = {SAMPLEPUMP, 465, 525}, 
    routine[2].StepTimes[2] = {SWITCHVALVE, 450, 452},
    routine[2].StepTimes[3] = {SOLENOIDVALVE, 450, 465}
};


//Turn off a device
void turnOff (enum DEVICE device) {
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


//Turn on a device
void turnOn (enum DEVICE device) {
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


//Device timings - This is called once a second and turns devicies on or off based on the timing parameters
void checkTiming (void) {

    //Temp, bind to rtc for accuracy
    static int timeElapsed;

    //Loop through structures, read the timing data and take action if appropiate
    for (int i = 0; i < STEPS; i++) {
        for (int j = 0; j < NUMBER_DEVICES; j++) {

            //Is it time to turn a device on
            if (timeElapsed == routine[i].StepTimes[j].timeOn) {
                //Turn on the device
                turnOn(routine[i].StepTimes[j].device);
            }

            //Is it time to turn a device off
            else if (timeElapsed == routine[i].StepTimes[j].timeOff) {
                //Turn off the device
                turnOff(routine[i].StepTimes[j].device);
            }
        }
    }
    //Increment timeElapsed
    timeElapsed++;
}

//Perform a Power On Self Test, POST
/**
    @param iter 
*/
void post (uint8_t iter) {
    //Turn the devices on and off iter times
    for (int i = 0; i < iter; i++) {
        turnOn(WASHPUMP);
        turnOn(SAMPLEPUMP);
        turnOn(SWITCHVALVE);
        turnOn(SOLENOIDVALVE);

        thread_sleep_for(500);

        turnOff(WASHPUMP);
        turnOff(SAMPLEPUMP);
        turnOff(SWITCHVALVE);
        turnOff(SOLENOIDVALVE);

        thread_sleep_for(500);
    }
}


int main() {

    //Run POST, 10 times
    post(5);

    //Wait for button before starting routine
    while(!userButton) {};

    while (true) {
        checkTiming();

        //Speeded up by a factor of 10 for testing
        //Delay used to set timing
        thread_sleep_for(100);
    }
}
