/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

/* FIMAS Project
 * Ross Andrewartha, January 2020
 */

//#include "Networkbits.hpp"
#include "deviceConfig.hpp"
#include "hardware.hpp"
#include "routineConfig.hpp"
#include "serialInterface.hpp"
#include "routineRun.hpp"



int main() {

    //Start routine thread
    routineThread.start(routineThreadFunction);

    //Start serial thread
    serialThread.start(serialInterface);

    //Send Welcome message over serial
    serialQueue.call(sendCString, "Welcome, Serial Port Opened\n");

}
