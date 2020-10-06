#include "hardware.hpp"

//Define an array to hold the pins used for the digital outputs
//Update the pin names here and if the number of pins has changed, update the number of pins used here as well as in hardware.hpp
const array<PinName, 8> digitalOutputs = {PF_13, PE_9, PE_11, PF_14, PE_13, PF_15, PG_14, PG_9};

//Define an array to hold the pins used for the digital inputs
//Update the pin names here and if the number of pins has changed, update the number of pins used here as well as in hardware.hpp
const array<PinName, 4> digitalInputs = {PA_7, PD_14, PD_15, PF_12};