#include "hardware.hpp"

/* //Declare DigitalOutputs for the utilised devices
DigitalOut washPump(D7);
DigitalOut samplePump(D6);
DigitalOut switchValve(D5);
DigitalOut solenoidValve(D4); */

//Declare input userbutton as trigger
//DigitalIn userButton(USER_BUTTON);

// //Debugging output, use faster baud rate to remain responsive
// Serial pc(USBTX, USBRX, 115200);


//Define an array to hold the pins used for the digital outputs
const array<PinName, 8> digitalOutputs = {PF_13, PE_9, PE_11, PF_14, PE_13, PF_15, PG_14, PG_9};
//testing  with leds
//const array<PinName, 8> digitalOutputs = {PF_13, LED1, PE_11, LED2, PE_13, PF_15, PG_14, PG_9};

//Define an array to hold the pins used for the digital inputs
const array<PinName, 4> digitalInputs = {PA_7, PD_14, PD_15, PF_12};

//Create an array of baseDevice which will be populated at run-time by calling configDevices()
//vector<baseDevice*> devices = {};	
	

/* //Declare how many steps the routine will be
#define STEPS 3

//Define a routine, consisting of STEPS steps
step routine[STEPS] = {
    //Declare timing for step 1
    routine[0].StepTimes[0] = {WASHPUMP, 0, 15}, 
    routine[0].StepTimes[1] = {SAMPLEPUMP, 15, 75}, 
    routine[0].StepTimes[2] = {SWITCHVALVE, 0, 2},
    routine[0].StepTimes[3] = {SOLENOIDVALVE, 0, 15},

    //Declare timing for step 2
    routine[1].StepTimes[0] = {WASHPUMP, 225, 240}, 
    routine[1].StepTimes[1] = {SAMPLEPUMP, 240, 300}, 
    routine[1].StepTimes[2] = {SWITCHVALVE, 225, 227},
    routine[1].StepTimes[3] = {SOLENOIDVALVE, 225, 240},

    //Declare timing for step 3
    routine[2].StepTimes[0] = {WASHPUMP, 450, 465}, 
    routine[2].StepTimes[1] = {SAMPLEPUMP, 465, 525}, 
    routine[2].StepTimes[2] = {SWITCHVALVE, 450, 452},
    routine[2].StepTimes[3] = {SOLENOIDVALVE, 450, 465}
};


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
            //Error log - unrecognised device passed to turnOff
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
            //Error log - unrecognised device passed to turnOn
            break;
        }
    }
}


//Device timings - This is called once a second and turns devices on or off based on the timing parameters
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
}*/

//Perform a Power On Self Test, POST
/**
    @param iter 
*/
// void post (uint8_t iter) {
//     //Turn the devices on and off iter times
//     for (int i = 0; i < iter; i++) {
//         turnOn(WASHPUMP);
//         turnOn(SAMPLEPUMP);
//         turnOn(SWITCHVALVE);
//         turnOn(SOLENOIDVALVE);

//         thread_sleep_for(500);

//         turnOff(WASHPUMP);
//         turnOff(SAMPLEPUMP);
//         turnOff(SWITCHVALVE);
//         turnOff(SOLENOIDVALVE);

//         thread_sleep_for(500);
//     }
// } 