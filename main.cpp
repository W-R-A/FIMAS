/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

/* FIMAS Project
 * Ross Andrewartha, January 2020
 */

#include "Networkbits.hpp"
#include "deviceConfig.hpp"
#include "hardware.hpp"
#include "routineConfig.hpp"
#include "serialInterface.hpp"

int main() {

    //Start serial thread
    serialThread.start(serialInterface);

    //Start Network Thread
    networkThread.start(network);

    //Send Welcome message over serial
    serialQueue.call(printf, "Welcome, Serial Port Opened\n");

    //Configure devices in the system
    configDevices(CONFIGURATION);

    //Wait for button before starting routine
    while (!userButton) {
    };
}
