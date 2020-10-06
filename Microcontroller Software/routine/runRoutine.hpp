#ifndef FIMAS_RUNROUTINE
#define FIMAS_RUNROUTINE

//Include the mbed header file
#include "mbed.h"


//Include the data manager header file
#include "dataManager.hpp"

#include "serialInterface.hpp"

//Create routine management thread
extern Thread routineManagerThread;

//Routine Thread
extern Thread routineThread;

//Create eventqueues
extern EventQueue routineQueue;

//Function reponsible for running the routine eventqueue
void routineThreadFunction(void);

//Manage the running of routines based on the state of the system 
//No parameters need to be passed and nothing is returned
void routineManager(void);

//Run routine
void runRoutine(void);

#endif