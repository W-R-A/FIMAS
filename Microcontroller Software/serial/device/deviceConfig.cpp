//Include the data header file
#include "deviceConfig.hpp"

//Configure devices over the serial port
//Pass in the key parameters as a c++ string to create the device
//Returns zero on sucess, non zero on failure
uint8_t configDevicesSerial(std::string const& devConfig) {

    //Create variables to hold the extracted values
    uint16_t devID;
    uint16_t devPin1;
    signed short devPin2;

    //Create a vector to hold the extracted data from the serial command
    vector<string> result;

    //Create a string stream from the string
    stringstream s_stream(devConfig); 

    //While there is data to parse, read it
    while(s_stream.good()) {

        //Create a string to hold a data argument
        std::string substr;

        //Get a single argument, delimited by a comma, and store it in the temporary string
        getline(s_stream, substr, ','); 

        //Add the string to the vector
        result.push_back(substr);
    }

    //If there are an invalid number of aruments supplied supplied, return an error
    if ((result.size() < 3) || (result.size() > 4)) {
        return 1;
    }

    //Extract the device ID
    devID = std::stoi(result.at(1));

    //Extract the device pin 1
    devPin1 = std::stoi(result.at(2));

    //If present, extract device pin 2
    if (result.size() == 4) {
        devPin2 = std::stoi(result.at(3));
    } else {
        devPin2 = -1;
    }

    //Find the device type string and create the appropiate object
    if (devConfig.find("PERPUMP") != string::npos) {
        
        //Create perPump object
        _dataManager.setAddDevice(PERPUMP, devPin1, devID); 

    } else if (devConfig.find("SOLVALVE") != string::npos) {
        
        //Create solValve object
        _dataManager.setAddDevice(SOLVALVE, devPin1, devID); 

    } else if (devConfig.find("SIXVALVE") != string::npos) {
        
        //Create sixValve object
        _dataManager.setAddDevice(SIXVALVE, devPin1, devPin2, devID); 

    } else if (devConfig.find("SWITCHVALVE") != string::npos) {
        
        //Check if the switchvalve is working in one or two pin mode
        if (devPin2 == -1) {
            
            //Create switchValve object with one pin
            _dataManager.setAddDevice(SWITCHVALVE, devPin1, devID); 

        } else {
            
            //Create switchValve object with two pins
            _dataManager.setAddDevice(SWITCHVALVE, devPin1, devPin2, devID); 

        }
    } else {

        //An error has occurred, signal failure to configure
        return 1;
    }
                
    //No errors, signal success
    return 0;
}


//Test a device with given ID
//Returns a string with the results of the tests
std::string testDeviceSerial(std::string const& devTest) {

    //Create variables to hold the extracted values
    uint16_t devID;

    //Create a vector to hold the extracted data from the serial command
    vector<string> result;

    //Create a string stream from the string
    stringstream s_stream(devTest); 

    //While there is data to parse, read it
    while(s_stream.good()) {

        //Create a string to hold a data argument
        std::string substr;

        //Get a single argument, delimited by a comma, and store it in the temporary string
        getline(s_stream, substr, ','); 

        //Add the string to the vector
        result.push_back(substr);
    }

    //If there are an invalid number of aruments supplied supplied, return an error
    if (result.size() != 1) {
        return "An error occured testing the device\n";
    }

    //Extract the device ID
    devID = std::stoi(result.at(0));

    return(_dataManager.getTestDevice(devID));
}
