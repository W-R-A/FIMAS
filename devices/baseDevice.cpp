#include "baseDevice.hpp"

//Constructor
//pin specifies the pin that the device is connected to.
//deviceID uniquely identifies the device
baseDevice::baseDevice(PinName pin, uint8_t pinindex, unsigned short deviceID) {
    //Initialise the control pin used, default output state of low
    this->controlPin1 = new DigitalOut(pin, 0);

    //Set the device ID
    this->devID = deviceID;

    //Set that this is a one pin device
    this->noPins = 1;

    //Initialise the state to be zero
    this->state = 0;

    //The name of the device should be base, overridden by child classes
    this->devType = "Base Device";

    //Set the pin indexe
    this-> pin1index = pinindex;
}

//Constructor
//pin1 and pin2 specify the pin(s) that the device is connected to.
//deviceID uniquely identifies the device
baseDevice::baseDevice(PinName pin1, PinName pin2, uint8_t pin1index, uint8_t pin2index, unsigned short deviceID) {
    //Initialise the control pin used, default output state of low
    this->controlPin1 = new DigitalOut(pin1, 0);

    //Initialise the second control pin used, default output state of low
    this->controlPin2 = new DigitalOut(pin2, 0);

    //Set the device ID
    this->devID = deviceID;

    //Set that this is a two pin device
    this->noPins = 2;

    //Initialise the state to be zero
    this->state = 0;

    //The name of the device should be base, overridden by child classes
    this->devType = "Base Device";

    //Set the pin indexes
    this-> pin1index = pin1index;

    this->pin2index = pin2index;
}

//Destructor
baseDevice::~baseDevice() {
    //Delete control pin one
    delete controlPin1;

    //If two pins used, delete the second control pin
    if (this->noPins == 2) {
        delete controlPin2;
    }
}

//Change the state of the internal state variable in an interrupt-safe way
void baseDevice::updateState(uint8_t updatedState) {
    //Disable interrupts during critical section of a state update
    CriticalSectionLock lock;

    //Update state variable
    state = updatedState;
}

//Get the ID of the device
unsigned short baseDevice::getID(void) {
    return devID;
}

//Virtual function, to be overridden by child classes
unsigned short baseDevice::changeState(unsigned short newState) {
    return this->state;
}

//Virtual function, to be overriden by child classes
//Tests the operation of the device
//Returns 0 if the device is operating normally, non-zero otherwise
unsigned short baseDevice::testDevice(void) {
    //This function should be overridden, therefore return 1 indicating that the device is not operating normally by default
    return 1;
}

//Virtual function, to be overriden by child classes if their default state is not zero
//Resets the device to its default state
void baseDevice::resetDevice(void) {
    //This should be overridden if the default state is not zero
    changeState(0);
}

unsigned short baseDevice::getState(void) {
    //Disable interrupts during critical section of reading the state of the device
    CriticalSectionLock lock;

    return this->state;
}

//Virtual function, to be overriden by child classes
//returns a string contrining the device data, including type, pins used, current state and id
//Example Output
//Device Type: Base Device
//Device ID: xxx
//Device Pin 1: x
//Device Pin 2: x
//Current State: x
std::string baseDevice::printData(void) {
    std::string data;

    data.append("Device Type: ");

    data.append(this-> devType);

    data.append("\nDevice ID: ");

    data.append(to_string(getID()));

    data.append("\nDevice Pin 1: ");

    data.append(to_string(this->pin1index));

    //If two pins used, print the the second control pin data
    if (this->noPins == 2) {
        data.append("\nDevice Pin 2: ");

        data.append(to_string(this->pin2index));
    }

    data.append("\nCurrent state: ");

    data.append(to_string(getState()));

    data.append("\n");

    // //Print out the current routine
    // //Nothing is returned and no parameters need to be passed
    // void printRoutine(void) {
    //     //Loop through the routine vector and print out the timing data
    //     for (uint8_t i = 0; i < routine.size(); i++) {
    //         deviceTimes device = routine.at(i);
    //         serialQueue.call(printf, "Timing block: %u,", i);
    //         serialQueue.call(printf, "deviceID: %u, timeStart: %u, timeStop: %u, state: %u\n", device.devID, device.startTime, device.stopTime, device.devState);
    //     }
    // }
    
    return data;
}

//Print an error message from a device
//msg if the error string to print
void baseDevice::printError(const char *msg) {
    printf("Error occurred: %s", msg);
}