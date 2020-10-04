#include "hardware.hpp"

//Define an array to hold the pins used for the digital outputs
const array<PinName, 8> digitalOutputs = {PF_13, PE_9, PE_11, PF_14, PE_13, PF_15, PG_14, PG_9};
//testing  with leds
//const array<PinName, 8> digitalOutputs = {PF_13, LED1, PE_11, LED2, PE_13, PF_15, PG_14, PG_9};

//Define an array to hold the pins used for the digital inputs
const array<PinName, 4> digitalInputs = {PA_7, PD_14, PD_15, PF_12};