/* 
 * Author: William Ross Andrewartha
 */

#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include "mbed.h"
#include <string> 
#include <cctype>

//Create a serial interface object to PC, this needs to be raw serial to avoid issues with the serial interupt
extern UnbufferedSerial pc;

//Serial Communication Threads
extern Thread serialThread;

//Create eventqueue
extern EventQueue serialQueue;

//Serial interface - Responsible for reading and writing to the serial interface
//No parameters need to be passed and nothing is returned
extern void serialInterface(void);

//Serial interface command guide
#define SERIAL_COMMAND_GUIDE "Serial command guide\n\nREAD NOW\nReads back all records (date, time, temperature, pressure, light)\n\nREAD BUFFER\nReads back all records (date, time, temperature, pressure, light) currently held in the internal memory buffer\n\nSETT T\nFor valid entries, 0.1=<T=<30.0, set the sampling period to <T> seconds and will return a string T UPDATED TO <T> otherwise return an OUT OF RANGE error.\n\nSTATE X\nWhere X is ON or OFF. When X is ON, start sampling; when X is OFF, stop sampling. Echo back a confirmation string or an error (where X is neither ON or OFF)\n\nLOGGING X \nWhere X is ON or OFF, turns on/off diagnostic logging to the serial interface. Echo back a confirmation string or an error (where X is neither ON or OFF)\n\nFLUSH\nForce all data in the FIFO buffer to be written to the SD card\n\nEJECT\nPerform a flush, then unmount the SD card so it can be ejected.\n\n"



//Handle serial input - block and allow the user to enter a command.
//Decode it and call cmdDecode to take the appropiate action
//No paramters need to be passed and nothing is returned
extern void serialInputHandler(void);

//This interrpt fires when a character is recieived over the serial interface
//No paramters need to be passed and nothing is returned
void serialInputInterrupt(void);


//Decode the command sent over serial and take the appropiate action
//Pass the string comtaing the command
//Nothing is returned
extern void cmdDecode(string cmd);

void send_usart(unsigned char d);

void sendString(const char *string);

#endif