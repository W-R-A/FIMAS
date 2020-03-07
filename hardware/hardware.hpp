#ifndef FIMAS_HARDWARE_H
#define FIMAS_HARDWARE_H

#include "mbed.h"

//Define enumerated types for the devices used
enum DEVICE {WASHPUMP, SAMPLEPUMP, SWITCHVALVE, SOLENOIDVALVE}; 

//Declare how many devices there are defined above
#define NUMBER_DEVICES 4

//Declare DigitalOutputs for the utilised devices
extern DigitalOut washPump;
extern DigitalOut samplePump;
extern DigitalOut switchValve;
extern DigitalOut solenoidValve;

//Declare input userbutton as trigger
extern DigitalIn userButton;

//Serial Communications
extern Serial pc;


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