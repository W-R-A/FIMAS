#ifndef FIMAS_BASEDEVICE
#define FIMAS_BASEDEVICE

//Include mbed header file
#include "mbed.h"

//Include the string header file
#include <string>

/*
 * Base device class containing key methods that all FIMAS devices use.
 * This includes a unique ID as well as the control pins used
 */
class baseDevice {
    //Protected Properties
protected:
    //Declare two digital outputs for the control pins. One or both may be used dependant on the device
    DigitalOut *controlPin1, *controlPin2;

    //Is the device using 1 or 2 control pins.
    unsigned int noPins;

    //The state of the device.
    uint8_t state;

    //The ID of the device, allowing the correct one to be controlled
    unsigned short devID;

    //User friendly type of device, eg switching valve
    std::string devType;

    uint8_t pin1index, pin2index;

    //Public API methods
public:
    //pin1 and pin2 specify the pin(s) that the device is connected to.
    //pin index specifies the user friendly interface for the pin
    //deviceID uniquely identifies the device
    baseDevice(PinName pin1, PinName pin2, uint8_t pin1index, uint8_t pin2index, unsigned short deviceID);

    //pin specifies the pin that the device is connected to
    //pin index specifies the user friendly interface for the pin
    //deviceID uniquely identifies the device
    baseDevice(PinName pin, uint8_t pinindex, unsigned short deviceID);

    //Destructor
    ~baseDevice();

    //Get the ID of the device
    unsigned short getID(void);

    //Get the state of the device
    unsigned short getState(void);

    //Virtual function, to be overriden by child classes
    //Changes the state of the device
    virtual unsigned short changeState(unsigned short newState);

    //Virtual function, to be overriden by child classes
    //Tests the operation of the device
    //Returns 0 if the device is operating normally, non-zero otherwise
    virtual unsigned short testDevice(void);

    //Virtual function, to be overriden by child classes if their default state is not zero
    //Resets the device to its default state
    virtual void resetDevice(void);

    //Virtual function, to be overriden by child classes
    //Prints out the device data, including type, pins used, current state and id
    //Example Output
    //Device Type: Base Device
    //Device ID: xxx
    //Device Pin 1: x
    //Device Pin 2: x
    //Current State: x
    virtual std::string printData(void);

    //Protected methods
protected:
    //Update the state of the internal state variable in an interrupt-safe way
    void updateState(uint8_t updatedState);

    //Print an error message from a device
    //msg if the error string to print
    void printError(const char *msg);
};

#endif