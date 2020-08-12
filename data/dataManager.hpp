#ifndef FIMAS_DATA
#define FIMAS_DATA

//Include the mbed header file
#include "mbed.h"

//Include the string header file
#include <string>

//Include the hardware header file to gain awareness of the hardware connected
#include "hardware.hpp"

//Class to manage data and configuration between threads
class dataManager {

//Public API methods   
public:
    //Constructor
    dataManager();

    //Destructor
    ~dataManager();

    //Clear all of the devices from the system. Clear the devices vector
    //No paramerters need to be passed
    //Returns 0 on success, non-zero on failure
    void setClearDevices(void);

    //Add a device to the system
    //The key device information should be passed as arguments 
    //Device Type, pin indexes and the device ID
    //Nothing is returned
    void setAddDevice(devices_t type, uint8_t pinIndex, unsigned short deviceID);
    void setAddDevice(devices_t type, uint8_t pin1index, uint8_t pin2index, unsigned short deviceID);

    //Get the number of devices in the device vector
    //No parameters need to be passed
    //The number of devices is returned
    uint32_t getNoDevices(void);

    //Get the currently configured devices on the system as a formatted string
    //No parameters need to be passed
    //A string containig the currently configured devices is returned
    std::string getDevicesString(void);

//Private Properties    
private:
    //Restrict assess to one thread at a time
    Mutex accessMutex;
  
    //Create a vector to hold the devices
    vector<baseDevice*> devices = {};

};

//Create an instance so that all functions can access the manager
extern dataManager _dataManager;

#endif