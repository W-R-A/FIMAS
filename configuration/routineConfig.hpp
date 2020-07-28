#ifndef FIMAS_ROUTINECONFIG
#define FIMAS_ROUTINECONFIG

//Include the mbed header file
#include "mbed.h"

//Include theJSON Parser header file
#include "MbedJSONValue.h"

//Include the serial interface header file
#include "serialInterface.hpp"

//Include the hardware header file
#include "hardware.hpp"

//Include the string header to assist with working with JSON
#include <string>

//Include the vector header to allow to creation of vector arrays
#include <vector>

//Include the set header to allow the creation of sets
#include <set>

//Define a structure to hold the timing parameters for each device for each step
typedef struct {
    uint16_t devID;
    uint16_t startTime;
    uint16_t stopTime;
    uint16_t devState;
} deviceTimes;

//Create a vector to store device times for the routine
extern std::vector<deviceTimes> routine;

//Function Prototypes

//Configure a routine to be run
//Takes the JSON string of routines and the ID of the desired routine to load
//Returns 0 on sucess, non-zero on failure
uint8_t configRoutine(const char *configJSON, uint16_t routineID);

//Test the devices used in a routine
//The routine must have been loaded using configRoutine
//Takes no inputs
//Returns 0 on sucess, non-zero on failure to pass a device test, with the value being the number of devices to fail testing
uint8_t testRoutineDevices(void);

//Print out the current routine
//Nothing is returned and no parameters need to be passed
void printRoutine(void);

//Get the duration of a routine
//Returns the duration of the loaded routine in seconds
//The desired routine should be configured before calling using configRoutine
uint16_t getRoutineDuration(void);

//Run the routine in a blocking fashion on the current thread
//Nothing is returned and no parameters need to be passed
//The desired routine should be configured before calling using configRoutine
void runBlockingRoutine(void);

//reset the devices used in a routine
//The routine must have been loaded using configRoutine
//Takes no inputs
//nothing returned
void resetRoutineDevices(void);

#endif