#include "runRoutine.hpp"

//Create Routine Thread
Thread routineThread(osPriorityRealtime);

//Create eventqueue
EventQueue routineQueue;

//RoutineThreadFunction - Responsible for running the routine EventQueue
void routineThreadFunction(void) {

    //Call the routine operation manager on the routine thread
    routineQueue.call(routineManager);


    //Start event queue on thread
    routineQueue.dispatch();
}

//Manage the running of routines based on the state of the system 
//No parameters need to be passed and nothing is returned
void routineManager(void) {

    //Wait while the system is not in the running state
    if (_dataManager.getSystemState() == STATE_RUNNING) {

        //Run the routine
    }
}