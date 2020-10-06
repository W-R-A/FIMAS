#include "routineConfig.hpp"


//Configure a routine over the serial port
//Pass in the key parameters as a c++ string to create the routine step
uint8_t configRoutineSerial(std::string const& routineConfig) {

    //Create a variable to hold the extracted values
    deviceTimes time;

    //Create a vector to hold the extracted data from the serial command
    vector<string> result;

    //Create a string stream from the string
    stringstream s_stream(routineConfig); 

    //While there is data to parse, read it
    while(s_stream.good()) {

        //Create a string to hold a data argument
        std::string substr;

        //Get a single argument, delimited by a comma, and store it in the temporary string
        getline(s_stream, substr, ','); 

        //Add the string to the vector
        result.push_back(substr);
    }


    //Check that the correct number of arguments have been supplied
    if (result.size() != 5) {
        //Error, return
        return 1;
    }

    //Extract the routineID
    uint16_t serialRoutineID = std::stoi(result.at(0));

    //If there is no currenly loaded routine, ie it just been cleared or at startup
    if (_dataManager.getRoutineID() == 0) {
        //Set the new routine id based on the transmission
        _dataManager.setRoutineID(serialRoutineID);
        //else, there is a curently loaded routine, check the new step matches it
    } else {
        if (serialRoutineID != _dataManager.getRoutineID()) {
            //Error, no match, failure
            return 1;
        }
    }        

    //Parse the data
    //Device ID
    time.devID = std::stoi(result.at(1));

    //Start time
    time.startTime = std::stoi(result.at(2));

    //Stop time
    time.stopTime = std::stoi(result.at(3));

    //Device state
    time.devState = std::stoi(result.at(4));

    //Add the timing information to the system
    _dataManager.setAddRoutineTiming(time);   

    //No errors, signal success
    return 0;
}
