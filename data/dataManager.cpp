//Class to manage all data and configuration in a thread-safe manner
//Uses the prnciple of assessors and mutators

//Include the data header file
#include "dataManager.hpp"

//Create an instance so that all functions can access the manager
dataManager _dataManager;

//Constructor
dataManager::dataManager() {

    //Lock access while modifing data
    this->accessMutex.lock();

    //Set the initial system state to idle
    this-> systemState = STATE_IDLE;

    //Resevere capactity in vector for devices, to minimise dynamic memory allocation later
    this->devices.reserve(maxDevices);

    //Once finshed, unlock data access
    this->accessMutex.unlock();
}


//Clear all of the devices from the system. Clear the devices vector
//No paramerters need to be passed
//Nothing is returned
void dataManager::setClearDevices(void){

    //Lock access while modifing data
    this->accessMutex.lock();
    
    //Clear the devices vector
    devices.clear();

    //Once finshed, unlock data access
    this->accessMutex.unlock();
}


//Add a device to the system
//The key device information should be passed as arguments 
//Device Type, Pin(s) used, pin indexes and the device ID
//Nothing is returned
void dataManager::setAddDevice(devices_t type, uint8_t pinIndex, unsigned short deviceID) {
    
    //Lock access while modifing data
    this->accessMutex.lock();

    //Create the appropiate device object based on the type of device
    switch (type) {
        default:
        case PERPUMP:
            devices.push_back(new perPump(digitalOutputs[pinIndex - 1], pinIndex, deviceID)); 
            break;
        case SOLVALVE:
            devices.push_back(new solValve(digitalOutputs[pinIndex - 1], pinIndex, deviceID)); 
            break;
        case SWITCHVALVE:
            devices.push_back(new switchValve(digitalOutputs[pinIndex - 1], pinIndex, deviceID)); 
            break;
    }

    //Once finshed, unlock data access
    this->accessMutex.unlock();
}


//Add a device to the system
//The key device information should be passed as arguments 
//Device Type, Pin(s) used, pin indexes and the device ID
//Nothing is returned
void dataManager::setAddDevice(devices_t type, uint8_t pin1index, uint8_t pin2index, unsigned short deviceID) {

    //Lock access while modifing data
    this->accessMutex.lock();

    //Create the appropiate device object based on the type of device
    switch (type) {
        default:
        case SIXVALVE:
            devices.push_back(new sixValve(digitalOutputs[pin1index - 1], digitalOutputs[pin2index - 1], pin1index, pin2index, deviceID));
            break;
        case SWITCHVALVE:
            devices.push_back(new switchValve(digitalOutputs[pin1index - 1], digitalOutputs[pin2index - 1], pin1index, pin2index, deviceID));
            break;
    }

    //Once finshed, unlock data access
    this->accessMutex.unlock();
}


//Get the number of devices in the device vector
//No parameters need to be passed
//The number of devices is returned
uint32_t dataManager::getNoDevices(void) {
    return devices.size();
}


//Get the currently configured devices on the system as a formatted string
//No parameters need to be passed
//A string containing the currently configured devices is returned
std::string dataManager::getDevicesString(void) {

    //Lock access while reading data
    this->accessMutex.lock();

    //Create a string to hold the device data
    std::string devicesString;

    //Get the number of devices configured to display as a summary of the devices
    devicesString.append(to_string(devices.size()));
    devicesString.append(" device(s) are configured on the system\n");

    //Loop through the devices vector
    for(int i = 0; i<devices.size(); i++) {    

        //Append the details of every device in the vector
        devicesString.append(devices.at(i)->printData());

        //Add a newline between devices
        devicesString.append("\n");
    }
    
    //Add a newline at the end of the string
    devicesString.append("\n");

    //Once finshed, unlock data access
    this->accessMutex.unlock();

    //Return the complete string
    return devicesString;
}


//Test the devices configured on the system
//Takes no inputs
//Returns 0 on sucess, non-zero on failure to pass a device test, with the value being the number of devices to fail testing
std::string dataManager::getTestDevices(void) {
    
    //Lock access while testing devices
    this->accessMutex.lock();

    //Create a string to hold the result of device testing
    std::string devFails;
    
    //Get the number of devices configured to display as a summary of the devices
    devFails.append(to_string(devices.size()));
    devFails.append(" device(s) are configured on the system\n");

    //Loop through the devices vector, testing each device in turn
    for(int i = 0; i<devices.size(); i++) {    

        //Get device ID
        devFails.append("Device ID: ");

        //Append the details of every device in the vector
        devFails.append(to_string(devices.at(i)->getID()));

        //Add a newline between devices
        devFails.append("\n");

        if (devices.at(i)->testDevice()) {

            //Device has a problem, add to string
            devFails.append("TEST: FAIL\n\n");

        } else {
            //Device has a problem, add to string
            devFails.append("TEST: PASS\n\n");

        }
    }

    //Once finshed, unlock
    this->accessMutex.unlock();

    //Return the string
    return devFails;
}


//Reset the devices on the system
//Takes no inputs
//Nothing is returned
void dataManager::setResetRoutineDevices(void) {

    //Lock access while testing devices
    this->accessMutex.lock();

    //Loop through the devices vector, testing each device in turn
    for(int i = 0; i<devices.size(); i++) {    

        //Reset every device in the vector
        devices.at(i)->resetDevice();
    }

    //Once finshed, unlock
    this->accessMutex.unlock();
}


//Set the state of a device 
//Takes the ID and desired state of the device
//Nothing is returned
void dataManager::setDeviceState(unsigned short deviceID, uint8_t state) {

    //Loop through the devices array
    for (int i = 0; i < devices.size(); i++) {

        //If the device ID matches the specified ID
        if (deviceID == devices[i]->getID()) {
            
            //Lock access while changing state
            this->accessMutex.lock();

            //Change the state of the device
            devices[i]->changeState(state);
        }
    }

    //Once finshed, unlock
    this->accessMutex.unlock();
}


//Get a timing block of the routine 
//Specify the timing block desired
//Returns the timing block
deviceTimes dataManager::getRoutineTimingBlock(uint16_t block) {
    return routine[block];
}


//Clear all of the routine information from the system. Clear the routine vector
//No paramerters need to be passed
//Nothing is returned
void dataManager::setClearRoutine(void){

    //Lock access while modifing data
    this->accessMutex.lock();
    
    //Clear the devices vector
    routine.clear();

    //Reset routine ID to zero
    this->routineID = 0;

    //Once finshed, unlock data access
    this->accessMutex.unlock();
}


//Set the routine ID
//Pass the new routineID
//Nothing is returned
void dataManager::setRoutineID(uint16_t newRoutineID) {
    
    //Lock access while modifing data
    this->accessMutex.lock();

    //Reset routine ID to zero
    this->routineID = newRoutineID;

    //Once finshed, unlock data access
    this->accessMutex.unlock();
}


//Get the routine ID
//No paramerters need to be passed
//The routine ID is returned
uint16_t dataManager::getRoutineID(void) {
    return this->routineID;
}


//Add timing information to the routine vector
//The timing parameters should be passed in the deviceTimes data structure
//Nothing is returned
void dataManager::setAddRoutineTiming(deviceTimes newTime) {
    
    //Lock access while modifing data
    this->accessMutex.lock();

    //Add the timing information to the routines vector
    routine.push_back(newTime);

    //Update the routine duration
    this->routineDuration = calcRoutineDuration();

    //Once finshed, unlock data access
    this->accessMutex.unlock();
}


//Get the currently configured routine on the system as a formatted string
//No parameters need to be passed
//A string containing the currently configured routine is returned
std::string dataManager::getRoutineString(void) {
    
    //Lock access while reading data
    this->accessMutex.lock();

    //Create a string to hold the routine data
    std::string routineString;

    //Get the routine ID
    routineString.append("Routine ID: ");
    routineString.append(to_string(this->routineID));

    //Print the number of routine timing blocks
    routineString.append("\n");
    routineString.append(to_string(routine.size()));
    routineString.append(" timing block(s) are configured on the system\n");


    //Loop through the routine vector and add the timing data to a string
    for (int i = 0; i < routine.size(); i++) {
        //Get the timing block
        deviceTimes device = routine.at(i);

        //Get the timing block
        routineString.append("Timing block ");
        routineString.append(to_string(i));

        //Get the device ID
        routineString.append("\nDevice ID: ");
        routineString.append(to_string(device.devID));

        //Get the start time
        routineString.append("\nStart Time: ");
        routineString.append(to_string(device.startTime));

        //Get the stop time
        routineString.append("\nStop Time: ");
        routineString.append(to_string(device.stopTime));

        //Get the state
        routineString.append("\nState: ");
        routineString.append(to_string(device.devState));

        //Add newline for clarity
        routineString.append("\n\n");
    }

    //Add newline at the end of the string
    routineString.append("\n");  
    
    //Once finshed, unlock data access
    this->accessMutex.unlock();

    //Return the complete string
    return routineString;
}

//Get the duration of a routine
//No parameters need to be passed
//Returns the duration of the loaded routine in seconds
uint16_t dataManager::getRoutineDuration(void) {
    return this->routineDuration;
}

//Get the size of the routine in the number of timing blocks configured
//No parameters need to be passed
//Returns the number of timing blocks on the system
uint16_t dataManager::getRoutineSize(void) {
    return this->routine.size();
}

//Get the current state of the system
//No paramters need to be passed
//The state of the system is returned in enummerated format
sysState dataManager::getSystemState(void) {
    return systemState;
}


//Get the current state of the system in a string format
//No paramters need to be passed
//The state of the system is returned in enummerated format
std::string dataManager::getSystemStateString(void) {

    //Lock access while reading data
    this->accessMutex.lock();

    switch(systemState) {
        default:
        case STATE_IDLE:
            return "IDLE\n";
            break;
        case STATE_RUNNING:
            return "RUNNING\n";
            break;
        case STATE_RUNNING_START:
            return "RUNNING_START\n";
            break;
        case STATE_ERROR:
            return "ERROR\n";
            break;
        case STATE_ESTOP:
            return "ESTOP\n";
            break;
    }

    //Once finshed, unlock data access
    this->accessMutex.unlock();
}


//Set the state of the system
//No paramters need to be passed
//The state of the system is returned in enummerated format
void dataManager::setSystemState(sysState newState) {
    
    //Lock access while modifing the state
    this->accessMutex.lock();

    //Switch besed on the state to be set
    switch(newState) {
        default:
        case STATE_IDLE:
            systemState = STATE_IDLE;
            break;
        case STATE_RUNNING_START:
            systemState = STATE_RUNNING_START;
            break;
        case STATE_RUNNING:
            systemState = STATE_RUNNING;
            break;
        case STATE_ERROR:
            systemState = STATE_ERROR;
            break;
        case STATE_ESTOP:
            systemState = STATE_ESTOP;
            break;
    }

    //Once finshed, unlock access
    this->accessMutex.unlock();
}


//Calculate the duration of a routine
//No parameters need to be passed
//Returns the duration of the loaded routine in seconds
uint16_t dataManager::calcRoutineDuration(void) {

    //No mutexes are used here as this is a private method and therefore only callable within the class
    //The calling function is expected to have the appropiate protection features in place
    
    uint16_t duration = 0;

    //Loop through the timings array and look for the largest value of timeStop
    for (deviceTimes n : routine) {
        //If the stop time for the current step is greater than any previous stop time
        if (n.stopTime >= duration) {

            //Update the last time value with the new greatest value
            duration = n.stopTime;
        }
    }
    return duration;
}