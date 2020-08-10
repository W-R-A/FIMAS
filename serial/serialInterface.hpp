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
#define SERIAL_COMMAND_GUIDE "Serial command guide\n\nCLEARDEVICES - Clear configuration data \nCLEARROUTINE - Clear configuration data \nCONFIGDEVICES - Configures devices for use with the system \nCONFIGROUTINE - Configures a routine for use with the system \nRUN - Run loaded routine \nSTATUS - Get device status \nESTOP - Emergency Stop \n\n"



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

//Tail of string
//inspired by https://stackoverflow.com/questions/7597260/how-to-get-the-tail-of-a-stdstring
//Usage std::string t = tail(source, 6); to get all of the string from char 6 to the end of the string
std::string endString(std::string const& source, size_t const length);

#endif