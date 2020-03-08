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

static const char *JSON_STRING = "[{\"devID\":\"1000\",\"devName\":\"Sample Pump\",\"devType\":\"perPump\",\"devPin1\":\"2\",\"devPin2\":\"-1\"},{\"devID\":\"1001\",\"devName\":\"Distribution Valve\",\"devType\":\"swichValve\",\"devPin1\":\"5\",\"devPin2\":\"-1\"},{\"devID\":\"1002\",\"devName\":\"6-Port Valve\",\"devType\":\"sixValve\",\"devPin1\":\"9\",\"devPin2\":\"10\"}]";



PinName outputs[8] = {PF_13, PE_9, PE_11, PF_14, PE_13, PF_15, PG_14, PG_9};

PinName inputs[4] = {PA_7, PD_14, PD_15, PF_12};



int main() {  

	//Start Network Thread
	networkThread.start(network);
	
	//Create a JSON parser object
    MbedJSONValue demo;

	//Test dynamic pin configuration
	DigitalOut* outputs2[2];
	
	
	
	
	//parse the previous string and fill the object demo
	parse(demo, JSON_STRING);

	std::string my_str;
	int my_int = 1;
	bool my_bool;
	
	//Caution - always check if the object contains the requested value before atempting to access it, otherwise a hardfault occurs from trying to access invalid memory
	if (demo[0].hasMember("devPin1")) {
		my_int = demo[0]["devPin1"].get<int>();
	}	

	pc.printf("Pin Config loaded, %d", my_int);
	
	my_int = 1;
	
	outputs2[0] = new DigitalOut(outputs[my_int], 0);
	
	outputs2[0]->write(0);
	
	//printf("%s", demo.hasMember("devId"));
	
    //my_str = demo[0]["devId"].get<std::string>();
    //my_int = demo["my_array"][1].get<int>();
    //my_bool = demo["my_boolean"].get<bool>();
   
    printf("my_str: %s\r\n", my_str.c_str());
    //printf("my_int: %d\r\n", my_int);
    //printf("my_bool: %s\r\n", my_bool ? "true" : "false");
	
	
	
	
	while (true) {
		outputs2[0]->write(!outputs2[0]->read());
		thread_sleep_for(500);
	}
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
