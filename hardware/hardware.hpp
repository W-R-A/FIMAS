#ifndef FIMAS_HARDWARE_H
#define FIMAS_HARDWARE_H

#include "mbed.h"

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

//Function prototypes

//Perform a Power On Self Test, POST
/**
    @param iter 
*/
void post (uint8_t iter);

//Device timings - This is called once a second and turns devicies on or off based on the timing parameters
void checkTiming (void);

//Turn on a device
void turnOn (enum DEVICE device);

//Turn off a device
void turnOff (enum DEVICE device);

#endif