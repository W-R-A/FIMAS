/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

/* FIMAS Project
 * Ross Andrewartha, January 2020
 */

#include "Networkbits.hpp"
#include "hardware.hpp"
#include "MbedJSONValue.h"
#include <string>

static const char *JSON_STRING = "[{\"devId\":\"1\",\"devName\":\"Sample Pump\",\"devType\":\"Peristaltic Pump\",\"devRelay\":\"Relay 1\",\"devTest\":\"Test Device\"},{\"devId\":\"2\",\"devName\":\"Switching Valve No.1\",\"devType\":\"Switching Valve\",\"devRelay\":\"Relay 2\",\"devTest\":\"Test Device\"}]";

int main() {  

	//Start Network Thread
	networkThread.start(network);
	
	//Create a JSON parser object
    MbedJSONValue demo;

	
	
	//parse the previous string and fill the object demo
	parse(demo, JSON_STRING);

	std::string my_str;
	int my_int;
	bool my_bool;
	
	//Caution - always check if the object contains the requested value before atempting to access it, otherwise a hardfault occurs from trying to access invalid memory
	if (demo[0].hasMember("devId")) {
		my_str = demo[0]["devId"].get<std::string>();
	}	

	//printf("%s", demo.hasMember("devId"));
	
    my_str = demo[0]["devId"].get<std::string>();
    //my_int = demo["my_array"][1].get<int>();
    //my_bool = demo["my_boolean"].get<bool>();
   
    printf("my_str: %s\r\n", my_str.c_str());
    //printf("my_int: %d\r\n", my_int);
    //printf("my_bool: %s\r\n", my_bool ? "true" : "false");
	
	while (true) {}
}

// int main() {

// 	t1.start(networktest);
	
//     //Run POST, 5 times
//     post(5);

//     //Wait for button before starting routine
//     while(!userButton) {};
		
		
		

//     while (true) {
//         checkTiming();

//         //Speeded up by a factor of 10 for testing
//         //Delay used to set timing
//         thread_sleep_for(100);
//     }
// }
