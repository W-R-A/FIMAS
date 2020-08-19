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

//Include the data manager header file
#include "dataManager.hpp"


//Function Prototypes

//Configure a routine to be run
//Takes a string of serial arguments, parses them, and adds them to the timing vector 
//Returns 0 on sucess, non-zero on failure
uint8_t configRoutineSerial(std::string const& routineConfig);

#endif