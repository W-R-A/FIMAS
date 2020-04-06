/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

/* FIMAS Project
 * Ross Andrewartha, January 2020
 */

#include "MbedJSONValue.h"
#include "Networkbits.hpp"
#include "hardware.hpp"
#include "serialInterface.hpp"
#include <array>
#include <string>

//Device Classes
#include "perPump.hpp"

static const char *JSON_STRING = "[{\"devID\":\"1000\",\"devName\":\"Sample Pump\",\"devType\":\"perPump\",\"devPin1\":\"1\",\"devPin2\":\"-1\"},{\"devID\":\"1001\",\"devName\":\"Control Valve\",\"devType\":\"solValve\",\"devPin1\":\"2\",\"devPin2\":\"-1\"},{\"devID\":\"1002\",\"devName\":\"6-Port Valve\",\"devType\":\"sixValve\",\"devPin1\":\"3\",\"devPin2\":\"4\"}]";

int main() {
    //Setup devices according to JSON description
    //Create a JSON parser object
    MbedJSONValue jsonParser;

    devices[0] = new perPump(digitalOutputs[0], 1000);

    devices[1] = new switchValve(digitalOutputs[1], 1001);

    devices[2] = new sixValve(digitalOutputs[2], digitalOutputs[3], 1002);

    //Start serial thread
    serialThread.start(serialInterface);

    //Start Network Thread
    networkThread.start(network);

    //Wait for button before starting routine
    while (!userButton) {
    };

    for (int i = 0; i < 9; i++) {
        devices[1]->changeState(i);
        thread_sleep_for(1000);
    }

    devices[1]->changeState(5);

    devices[1]->changeState(2);

    // devices[0]->changeState(1);

    // devices[1]->changeState(1);

    // devices[2]->changeState(1);

    // thread_sleep_for(1000);

    // devices[1]->changeState(0);

    // devices[2]->changeState(0);

    // thread_sleep_for(5000);

    // devices[1]->changeState(1);

    // devices[0]->changeState(0);

    // while (true) {
    //     //Wait for button before starting routine
    //     //while(!userButton) {};

    //     devices[0]->changeState(1);

    //     devices[1]->changeState(1);

    //     devices[2]->changeState(1);

    //     thread_sleep_for(1000);

    //     devices[1]->changeState(0);

    //     devices[2]->changeState(0);

    //     thread_sleep_for(5000);

    //     devices[1]->changeState(1);

    //     devices[0]->changeState(0);

    //     thread_sleep_for(500);
    //}
}

//	//Create a JSON parser object
//    MbedJSONValue demo;
//
//	//parse the previous string and fill the object demo
//	parse(demo, JSON_STRING);

//	std::string my_str;
//	int my_int = 1;
//	bool my_bool;
//
//	//Caution - always check if the object contains the requested value before atempting to access it, otherwise a hardfault occurs from trying to access invalid memory
//	if (demo[0].hasMember("devPin1")) {
//		my_str = demo[0]["devPin1"].get<std::string>();
//	}

//
//
//	my_int = std::stoi(my_str);
//

//	serialQueue.call(printf, "Pin Config loaded, %d \n", my_int);
//
//
//	//Caution - always check if the object contains the requested value before atempting to access it, otherwise a hardfault occurs from trying to access invalid memory
//	if (demo[0].hasMember("devType")) {
//		my_str = demo[0]["devType"].get<std::string>();
//	}
//
//
////	perPump* pump;
////
////	if (my_str.find("perPump") != string::npos) {
////		 pump = new perPump(digitalOutputs[my_int], 1000);
////	}
////
////	pump->changeState(1);
//
//	//array<DigitalOut, 4> outputs = {DigitalOut(digitalOutputs[0], 0), DigitalOut(digitalOutputs[1], 1), DigitalOut(digitalOutputs[2], 0), DigitalOut(digitalOutputs[3], 1)};
//

//	//printf("%s", demo.hasMember("devId"));
//
//    //my_str = demo[0]["devId"].get<std::string>();
//    //my_int = demo["my_array"][1].get<int>();
//    //my_bool = demo["my_boolean"].get<bool>();
//
//    //printf("my_str: %s\r\n", my_str.c_str());
//    //printf("my_int: %d\r\n", my_int);
//    //printf("my_bool: %s\r\n", my_bool ? "true" : "false");
//
//
//
//
//	while (true) {
//		//for (int i=0; i<outputs.size(); i++)
//		//outputs[i].write(!outputs[i].read());
//		thread_sleep_for(500);
//	}
//}

//// int main() {

//// 	t1.start(networktest);
//
////     //Run POST, 5 times
////     post(5);

////     //Wait for button before starting routine
////     while(!userButton) {};
//
//
//

////     while (true) {
////         checkTiming();

////         //Speeded up by a factor of 10 for testing
////         //Delay used to set timing
////         thread_sleep_for(100);
////     }
//// }
