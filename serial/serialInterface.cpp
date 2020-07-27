/* 
 * Author: William Ross Andrewartha
 */

#include "serialInterface.hpp"
#include "hardware.hpp"

//Serial Communication Thread
Thread serialThread;

//Create eventqueues
EventQueue serialQueue;

//Serial interface - Responsible for reading and writing to the serial interface
//No parameters need to be passed and nothing is returned
void serialInterface(void) {
    //Start event queue on thread
    serialQueue.dispatch();
}