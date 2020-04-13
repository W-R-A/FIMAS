#ifndef FIMAS_ROUTINECONFIG
#define FIMAS_ROUTINECONFIG

//Include the mbed header file
#include "mbed.h"

//Include theJSON Parser header file
#include "MbedJSONValue.h"

//Incldue the serial interface header file
#include "serialInterface.hpp"

//Function Prototypes

//Takes the JSON string of routines and the ID of the desired routine to load
//Returns 0 on sucess, non zero on failure
uint8_t configRoutine(const char *configJSON, uint16_t routineID);

#endif