#include "hardware.hpp"

//Turn off a device
void turnOff (enum DEVICE device) {
    switch (device) {
        case WASHPUMP : {
            //Turn off the wash pump
            washPump = 0;
            break;
        }

        case SAMPLEPUMP : {
            //Turn off the sample pump
            samplePump = 0;
            break;
        } 

        case SWITCHVALVE : {
            //Turn off the switch valve - Position A
            switchValve = 0;
            break;
        }

        case SOLENOIDVALVE : {
            //Turn off the solenoid valve
            solenoidValve = 0;
            break;
        }

        default: {
            //Default case, should not happen
            //Error log - unregcognised device passed to turnOff
            break;
        }
    }
}


//Turn on a device
void turnOn (enum DEVICE device) {
    switch (device) {
        case WASHPUMP : {
            //Turn on the wash pump
            washPump = 1;
            break;
        }

        case SAMPLEPUMP : {
            //Turn on the sample pump
            samplePump = 1;
            break;
        } 

        case SWITCHVALVE : {
            //Turn on the switch valve - Position B
            switchValve = 1;
            break;
        }

        case SOLENOIDVALVE : {
            //Turn on the solenoid valve
            solenoidValve = 1;
            break;
        }

        default: {
            //Default case, should not happen
            //Error log - unregcognised device passed to turnOn
            break;
        }
    }
}


//Device timings - This is called once a second and turns devicies on or off based on the timing parameters
void checkTiming (void) {

    //Temp, bind to rtc for accuracy
    static int timeElapsed;

    //Loop through structures, read the timing data and take action if appropiate
    for (int i = 0; i < STEPS; i++) {
        for (int j = 0; j < NUMBER_DEVICES; j++) {

            //Is it time to turn a device on
            if (timeElapsed == routine[i].StepTimes[j].timeOn) {
                //Turn on the device
                turnOn(routine[i].StepTimes[j].device);
            }

            //Is it time to turn a device off
            else if (timeElapsed == routine[i].StepTimes[j].timeOff) {
                //Turn off the device
                turnOff(routine[i].StepTimes[j].device);
            }
        }
    }
    //Increment timeElapsed
    timeElapsed++;
}

//Perform a Power On Self Test, POST
/**
    @param iter 
*/
void post (uint8_t iter) {
    //Turn the devices on and off iter times
    for (int i = 0; i < iter; i++) {
        turnOn(WASHPUMP);
        turnOn(SAMPLEPUMP);
        turnOn(SWITCHVALVE);
        turnOn(SOLENOIDVALVE);

        thread_sleep_for(500);

        turnOff(WASHPUMP);
        turnOff(SAMPLEPUMP);
        turnOff(SWITCHVALVE);
        turnOff(SOLENOIDVALVE);

        thread_sleep_for(500);
    }
}