#ifndef FIMAS_DATA
#define FIMAS_DATA

//Include the mbed header file
#include "mbed.h"

//Include the string header file
#include <string>

//Include the hardware header file to gain awareness of the hardware connected
#include "hardware.hpp"

//Include the serial interface to aid debugging
#include "serialInterface.hpp"


//Declare an emmurated type to repreesnt the state of the system
typedef enum {
    STATE_IDLE = 1, 
    STATE_RUNNING_START = 2, 
    STATE_RUNNING = 3,
    STATE_ERROR = 4, 
    STATE_ESTOP = 5
} sysState;


//Define a structure to hold the timing parameters for each device for each step
typedef struct {
    uint16_t devID;
    uint16_t startTime;
    uint16_t stopTime;
    uint16_t devState;
} deviceTimes;


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
    //Nothing is returned
    void setClearDevices(void);

    //Add a device to the system
    //The key device information should be passed as arguments 
    //Device Type, pin indexes and the device ID
    //Nothing is returned
    void setAddDevice(devices_t type, uint8_t pinIndex, uint16_t deviceID);
    void setAddDevice(devices_t type, uint8_t pin1index, uint8_t pin2index, uint16_t deviceID);

    //Get the number of devices in the device vector
    //No parameters need to be passed
    //The number of devices is returned
    uint32_t getNoDevices(void);

    //Get the currently configured devices on the system as a formatted string
    //No parameters need to be passed
    //A string containing the currently configured devices is returned
    std::string getDevicesString(void);

    //Test the devices configured on the system
    //Takes no inputs
    //Returns a string with the results of testing each device, ID and pass/fail testing
    std::string getTestDevices(void);

    //Test a device configured on the system
    //Takes the ID of the device to test
    //Returns a string with the results of the test
    std::string getTestDevice(uint16_t deviceID);

    //Reset the devices on the system
    //Takes no inputs
    //Nothing is returned
    void setResetRoutineDevices(void);

    //Set the state of a device 
    //Takes the ID and desired state of the device
    //Nothing is returned
    void setDeviceState(uint16_t deviceID, uint8_t state);

    //Clear all of the routine information from the system. Clear the routine vector
    //No paramerters need to be passed
    //Nothing is returned
    void setClearRoutine(void);

    //Set the routine ID
    //Pass the new routineID
    //Nothing is returned
    void setRoutineID(uint16_t newRoutineID);

    //Get the routine ID
    //No paramerters need to be passed
    //The routine ID is returned
    uint16_t getRoutineID(void);

    //Add timing information to the routine vector
    //The timing parameters should be passed in the deviceTimes data structure
    //Nothing is returned
    void setAddRoutineTiming(deviceTimes newTime);

    //Get the currently configured routine on the system as a formatted string
    //No parameters need to be passed
    //A string containing the currently configured routine is returned
    std::string getRoutineString(void);

    //Get the duration of a routine
    //No parameters need to be passed
    //Returns the duration of the loaded routine in seconds
    uint16_t getRoutineDuration(void);

    //Get the size of the routine in the number of timing blocks configured
    //No parameters need to be passed
    //Returns the number of timing blocks on the system
    uint16_t getRoutineSize(void);

    //Get a timing block of the routine 
    //Specify the timing block desired
    //Returns the timing block
    deviceTimes getRoutineTimingBlock(uint16_t block);

    //Get the current stste of the system
    //No paramters need to be passed
    //The state of the system is returned in enummerated format
    sysState getSystemState(void);

    //Get the current stste of the system in a string format
    //No paramters need to be passed
    //The state of the system is returned in enummerated format
    std::string getSystemStateString(void);

    //Set the state of the system
    //The new state of the system needs to be passed
    //Nothing is returned
    void setSystemState(sysState newState);

//Private Properties / methods  
private:
    //Properties

    //Restrict assess to one thread at a time
    Mutex accessMutex;
  
    //Create a vector to hold the devices
    vector<baseDevice*> devices = {};

    //Create a vector to hold the routine
    vector<deviceTimes> routine;

    //Create a variable to hold the routineID
    uint16_t routineID;

    //Create a variable to hold the duration of the routine in seconds
    uint16_t routineDuration;

    //Create a status register
    sysState systemState;


    //Methods

    //Calculate the duration of a routine
    //No parameters need to be passed
    //Returns the duration of the loaded routine in seconds
    uint16_t calcRoutineDuration(void);

    //Get the internal data mutex, block until available
    //Nothing is passed, nothing is returned
    void getMutex(void);

    //Release the internal data mutex, block until available
    //Nothing is passed, nothing is returned
    void releaseMutex(void);

};

//Create an instance so that all functions can access the manager
extern dataManager _dataManager;

#endif