#ifndef FIMAS_ROUTINECONFIG
#define FIMAS_ROUTINECONFIG

//Include the mbed header file
#include "mbed.h"


//Include the string header
#include <string>

//Include headers to parse strings
#include <vector>

//Include sstream to work with parsing serial data
#include <sstream>

//Include the set header file
#include <set>

//Include the data manager header file
#include "dataManager.hpp"


//Function Prototypes

//Configure a routine to be run
//Takes the JSON string of routines and the ID of the desired routine to load
//Returns 0 on sucess, non-zero on failure
uint8_t configRoutine(const char *configJSON, uint16_t routineID);

uint8_t configRoutineSerial(std::string const& routineConfig);

//Test the devices used in a routine
//The routine must have been loaded using configRoutine
//Takes no inputs
//Returns 0 on sucess, non-zero on failure to pass a device test, with the value being the number of devices to fail testing
uint8_t testRoutineDevices(void);

//Clear all routine data
//Nothing is returned and no parameters need to be passed
void clearRoutine(void);

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