#ifndef FIMAS_HARDWARE_H
#define FIMAS_HARDWARE_H

//Include mbed header
#include "mbed.h"

//Include array header
#include <array>

//Include vector header
#include <vector>

//Include the base device class
#include "baseDevice.hpp"

//Include derived device classes
#include "perPump.hpp"
#include "sixValve.hpp"
#include "solValve.hpp"
#include "switchValve.hpp"

typedef enum {
    PERPUMP = 1, 
    SIXVALVE = 2, 
    SOLVALVE = 3, 
    SWITCHVALVE = 4
} devices_t;

//Define an array to hold the pins used for the digital outputs
extern const array<PinName, 8> digitalOutputs;

//Define an array to hold the pins used for the digital inputs
extern const array<PinName, 4> digitalInputs;

//Calculate the number of digital inputs and outpus defined
const short maxDevices = digitalOutputs.size() + digitalInputs.size();

//Declare an array to hold the devices given that each device requires an minimum of one pin, this means that the number of devices is limited by the number of digital output and input pins defined
//Contents will be populated at run-time
//extern vector<baseDevice *> devices;

// //Define enumerated types for the devices used
// enum DEVICE {WASHPUMP, SAMPLEPUMP, SWITCHVALVE, SOLENOIDVALVE};

// //Declare how many devices there are defined above
// #define NUMBER_DEVICES 4

// //Declare DigitalOutputs for the utilised devices
// extern DigitalOut washPump;
// extern DigitalOut samplePump;
// extern DigitalOut switchValve;
// extern DigitalOut solenoidValve;

//Declare input userbutton as trigger
//extern DigitalIn userButton;

// //Serial Communications
// extern Serial pc;



// //Define a structure to hold the timing parameters for all the devices in a step
// typedef struct {
//     deviceTime StepTimes[NUMBER_DEVICES];
// } step;

//Function prototypes

//Perform a Power On Self Test, POST
/**
    @param iter 
*/
// void post (uint8_t iter);

// //Device timings - This is called once a second and turns devices on or off based on the timing parameters
// void checkTiming (void);

// //Turn on a device
// void turnOn (enum DEVICE device);

// //Turn off a device
// void turnOff (enum DEVICE device);

#endif