#ifndef FIMAS_ROUTINECONFIG
#define FIMAS_ROUTINECONFIG

//Include the mbed header file
#include "mbed.h"

//Include theJSON Parser header file
#include "MbedJSONValue.h"

//Incldue the serial interface header file
#include "serialInterface.hpp"

//Define a structure to hold the timing parameters for each device for each step
typedef struct {
    uint16_t devID;
    uint16_t startTime;
    uint16_t stopTime;
    uint16_t devState;
} deviceTimes;

//Function Prototypes

//Takes the JSON string of routines and the ID of the desired routine to load
//Returns 0 on sucess, non zero on failure
uint8_t configRoutine(const char *configJSON, uint16_t routineID);

#endif