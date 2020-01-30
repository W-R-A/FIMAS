/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut washPump(PE_14);
DigitalOut samplePump(PE_15);
DigitalOut switchValve(PE_12);
DigitalOut solenoidValve(PE_8);

typedef struct {
    int device;
    int timeOn;
    int timeOff;
} deviceControl;

// Blinking rate in milliseconds
#define BLINKING_RATE_MS  500


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        led = !led;
        thread_sleep_for(BLINKING_RATE_MS);
    }
}
