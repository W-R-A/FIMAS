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

    //Resevere capactity in vector for devices, to minimise dynamic memory allocation later
    this->devices.reserve(maxDevices);

    //Once finshed, unlock data access
    this->accessMutex.unlock();
}


//Clear all of the devices from the system. Clear the devices vector
//No paramerters need to be passed
//Returns 0 on success, non-zero on failure
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
