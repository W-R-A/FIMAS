/* 
 * Author: William Ross Andrewartha
 */

#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include "mbed.h"
#include <string> 

//Serial Communication Threads
extern Thread serialThread;

//Create eventqueue
extern EventQueue serialQueue;

//Serial interface - Responsible for reading and writing to the serial interface
//No parameters need to be passed and nothing is returned
extern void serialInterface(void);

#endif