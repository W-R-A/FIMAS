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


Thread t1;

int main() {

	t1.start(networktest);
	
    //Run POST, 5 times
    post(5);

    //Wait for button before starting routine
    while(!userButton) {};

    while (true) {
        checkTiming();

        //Speeded up by a factor of 10 for testing
        //Delay used to set timing
        thread_sleep_for(100);
    }
}
