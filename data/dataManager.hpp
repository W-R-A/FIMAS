#ifndef FIMAS_DATA
#define FIMAS_DATA

//Include the mbed header file
#include "mbed.h"

//Include the string header file
#include <string>

//Include the hardware header file to gain awareness of the hardware connected
#include "hardware.hpp"


//Declare an emmurated type to repreesnt the state of the system
typedef enum {
    STATE_IDLE = 1, 
    STATE_RUNNING = 2, 
    STATE_ERROR = 3, 
    STATE_ESTOP = 4
} sysState;


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
    //A string containing the currently configured devices is returned
    std::string getDevicesString(void);

    //Get the current stste of the system
    //No paramters need to be passed
    //The state of the system is returned in enummerated format
    sysState getSystemState(void);

    //Get the current stste of the system in a string format
    //No paramters need to be passed
    //The state of the system is returned in enummerated format
    std::string getSystemStateString(void);

    //Set the state of the system
    //No paramters need to be passed
    //The state of the system is returned in enummerated format
    void setSystemState(sysState newState);

//Private Properties    
private:
    //Restrict assess to one thread at a time
    Mutex accessMutex;
  
    //Create a vector to hold the devices
    vector<baseDevice*> devices = {};

    //Create a status register
    sysState systemState;

};

//Create an instance so that all functions can access the manager
extern dataManager _dataManager;

#endif