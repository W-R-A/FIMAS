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


//Define enumerated types for the devices
enum DEVICE {WASHPUMP, SAMPLEPUMP, SWITCHVALVE, SOLENOIDVALVE}; 

//Define a structure to hold the timing parameters
typedef struct {
    enum DEVICE device;
    int timeOn;
    int timeOff;
} deviceTime;

typedef struct {
    deviceTime StepTimes[4];
} step;


step routine[2] = {routine[0].StepTimes[0] = {WASHPUMP, 0, 20}, routine[0].StepTimes[1] = {WASHPUMP, 0, 20}, routine[0].StepTimes[2] = {WASHPUMP, 0, 20}, routine[0].StepTimes[3] = {WASHPUMP, 0, 20}};


// Blinking rate in milliseconds
#define BLINKING_RATE_MS  500

int main()
{
	
    routine[0].StepTimes[0].device = SAMPLEPUMP;
	
    enum DEVICE x = routine[0].StepTimes[0].device;// = WASHPUMP;
	
    
	
	
	
	// Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        led = !led;
        thread_sleep_for(BLINKING_RATE_MS);
    }
}
