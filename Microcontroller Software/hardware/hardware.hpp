#ifndef FIMAS_HARDWARE_H
#define FIMAS_HARDWARE_H

//Include mbed header
#include "mbed.h"

//Include array header
#include <array>

//Include the base device class
#include "baseDevice.hpp"

//Include derived device classes
#include "perPump.hpp"
#include "sixValve.hpp"
#include "solValve.hpp"
#include "switchValve.hpp"

//Serial Interface Configuration

//For debugging over the ST-Link, use USART 3 and pins USART_TX: USBTX and USART_RX: USBRX
//For production use with a raspberry pi as a web interface on a STM32F429ZI Microcontroller, use USART 2 and pins USART_TX: PD_5 and USART_RX: PD_6

//Define the Used USART interface on the microcontroller.
//For the STM32F429ZI Microcontroller:
//USART3 is used to communicate over the USB port on the ST-Link module
//USART2 is used to communicate on pins PD_5 and PD_6
#define USEDUSART USART2

//Define the pin used to transmit USART data
#define USART_TX PD_5

//Define the pin used to receieve USART data
#define USART_RX PD_6

//Create the enumerated types for the devices used
//Add new devices to this list so that they can be used in the data manager
typedef enum {
    PERPUMP = 1, 
    SIXVALVE = 2, 
    SOLVALVE = 3, 
    SWITCHVALVE = 4
} devices_t;

//Define an array to hold the pins used for the digital outputs
//Update the pin names in hardware.cpp and if the number of pins has changed, update the number of pins used here as well
extern const array<PinName, 8> digitalOutputs;

//Define an array to hold the pins used for the digital inputs
//Update the pin names in hardware.cpp and if the number of pins has changed, update the number of pins used here as well
extern const array<PinName, 4> digitalInputs;

//Calculate the number of digital inputs and outpus defined
const short maxDevices = digitalOutputs.size() + digitalInputs.size();

#endif