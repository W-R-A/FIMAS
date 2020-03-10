#ifndef FIMAS_BASEDEVICE
#define FIMAS_BASEDEVICE

//Include mbed header file
#include "mbed.h"

/*
 * Base device class containng key methods that all FIMAS devices use.
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

    //Public API methods
public:
    //pin1 and pin2 specify the pin(s) that the device is connected to.
    //deviceID uniquely identifies the device
    baseDevice(PinName pin1, PinName pin2, unsigned short deviceID);

    //pin specifies the pin that the device is connected to.
    //deviceID uniquely identifies the device
    baseDevice(PinName pin, unsigned short deviceID);

    //Destructor
    ~baseDevice();

    //Get the ID of the device
    unsigned short getID(void);

    //Change the state of the device, in a interrupt-safe way
    void changeState(int newState);
};

#endif