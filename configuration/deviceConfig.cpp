#include "deviceConfig.hpp"
#include "serialInterface.hpp"

//Include the data manager
#include "dataManager.hpp"


//Configure devices over the serial port
//Pass in the key parameters as a c++ string to create the device
uint8_t configDevicesSerial(std::string const& devConfig) {

    //Create variables to hold the extracted values
    uint16_t devID;
    uint16_t devPin1;
    signed short devPin2;
    std::string devType;

    // sendString((char *)devConfig.c_str());

    vector<string> result;

    stringstream s_stream(devConfig); //create string stream from the string

    while(s_stream.good()) {
        using namespace std;
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        result.push_back(substr);
    }

    // for(int i = 0; i<result.size(); i++) {    //print all splitted strings
    //     sendString(result.at(i));
    //     sendString("\n\n");
    // }
   
    // sendString("\n\n");

    devID = std::stoi(result.at(1));

    devPin1 = std::stoi(result.at(2));

    //sendString((char*)to_string(result.size()).c_str());

    if (result.size()>3) {
        devPin2 = std::stoi(result.at(3));
    } else {
        devPin2 = -1;
    }

    //Find the device type string and create the appropiate object
    if (devConfig.find("PERPUMP") != string::npos) {
        //Create perPump object
        _dataManager.setAddDevice(PERPUMP, devPin1, devID); 

        sendString("Created a peristaltic pump with the following configuration:");

    } else if (devConfig.find("SOLVALVE") != string::npos) {
        //Create solValve object
        _dataManager.setAddDevice(SOLVALVE, devPin1, devID); 

        sendString("Created a soleniod valve with the following configuration:");

    } else if (devConfig.find("SIXVALVE") != string::npos) {
        //Create sixValve object
        _dataManager.setAddDevice(SIXVALVE, devPin1, devPin2, devID); 

        sendString("Created a six-port valve with the following configuration:");

    } else if (devConfig.find("SWITCHVALVE") != string::npos) {
        //Check if the switchvalve is working in one or two pin mode
        if (devPin2 == -1) {
            //Create switchValve object with one pin
            _dataManager.setAddDevice(SWITCHVALVE, devPin1, devID); 
        } else {
            //Create switchValve object with two pins
            _dataManager.setAddDevice(SWITCHVALVE, devPin1, devPin2, devID); 
        }
        sendString("Created a switch valve with the following configuration:");
    } else {

        //An error has occurred, signal failure to configure
        return 1;
    }

    sendString("\nDevice ID: ");
    sendString(result.at(1));
    sendString("\nDevice Pin 1: ");
    sendString(result.at(2));


    if (result.size()>3) {
        sendString("\nDevice Pin 2: ");
        sendString(result.at(3));
    } 

    sendString("\n");
                
    //No errors, signal success
    return 0;
}

