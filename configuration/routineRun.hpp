#ifndef FIMAS_ROUTINERUN
#define FIMAS_ROUTINERUN

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

#include "routineConfig.hpp"

//Routine Thread
extern Thread routineThread;

//Create eventqueues
extern EventQueue routineQueue;

//Reponsible for running the routine eventqueue
void routineThreadFunction(void);

//Run routine
void runRoutine(void);

#endif