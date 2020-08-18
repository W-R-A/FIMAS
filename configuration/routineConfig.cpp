#include "routineConfig.hpp"

//Create a vector to store device times for the routine
std::vector<deviceTimes> routine;

//Create a variable to hold the routineID
uint32_t routineID;

//Configure a routine to be run
//Takes the JSON string of routines and the ID of the desired routine to load
//Returns 0 on success, non-zero on failure
uint8_t configRoutine(const char *configJSON, uint16_t routineID) {
    // //Clear the routine vector of any previous timing information
    // routine.clear();

    // //Setup routines according to JSON description
    // //Create a JSON parser object
    // MbedJSONValue jsonParser;

    // //Parse the JSON string and store the result in jsonParser
    // parse(jsonParser, configJSON);

    // //check for name/ID of routine
    // //check for timings array
    // //loop through array, extracting timing data

    // //Loop through all of the routines that have an valid ID
    // for (uint8_t i = 0; jsonParser[i].hasMember((char *)"routineID"); i++) {

    //     //Caution - always check if the object contains the requested value before attempting to access it, otherwise a hardfault occurs from trying to access invalid memory
    //     //Get the current routine ID
    //     if (jsonParser[i].hasMember((char *)"routineID")) {
    //         uint16_t currentRoutineID = std::stoi(jsonParser[i]["routineID"].get<std::string>());

    //         //If the current iteration is the requested routine ID, load the data into the vector
    //         if (routineID == currentRoutineID) {

    //             //Check if the timings array is present
    //             if (jsonParser[i].hasMember((char *)"timings")) {

    //                 //Loop through the timings array, extracting timing info
    //                 for (uint16_t j = 0; jsonParser[i]["timings"][j].hasMember((char *)"devID"); j++) {
    //                     //Create a variable to hold the extracted values
    //                     deviceTimes time;

    //                     //Check for the deviceID
    //                     if (jsonParser[i]["timings"][j].hasMember((char *)"devID")) {
    //                         //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
    //                         time.devID = std::stoi(jsonParser[i]["timings"][j]["devID"].get<std::string>());

    //                         //Check for the start time
    //                         if (jsonParser[i]["timings"][j].hasMember((char *)"timeStart")) {
    //                             //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
    //                             time.startTime = std::stoi(jsonParser[i]["timings"][j]["timeStart"].get<std::string>());

    //                             //Check for the stop time
    //                             if (jsonParser[i]["timings"][j].hasMember((char *)"timeStop")) {
    //                                 //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
    //                                 time.stopTime = std::stoi(jsonParser[i]["timings"][j]["timeStop"].get<std::string>());

    //                                 //Check for the device state
    //                                 if (jsonParser[i]["timings"][j].hasMember((char *)"state")) {
    //                                     //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
    //                                     time.devState = std::stoi(jsonParser[i]["timings"][j]["state"].get<std::string>());

    //                                     //Add the timing information to the routines vector
    //                                     routine.emplace_back(time);
    //                                 } else {
    //                                     //Debugging, send the client information over serial
    //                                     serialQueue.call(printf, "Error reading the device state, device ID: %d, start time: %d, stop time: %d\n", time.devID, time.startTime, time.stopTime);

    //                                     //An error has occurred, signal failure to load the routine
    //                                     return 1;
    //                                 }
    //                             } else {
    //                                 //Debugging, send the client information over serial
    //                                 serialQueue.call(printf, "Error reading the stop time, device ID: %d, start time: %d\n", time.devID, time.startTime);

    //                                 //An error has occurred, signal failure to load the routine
    //                                 return 1;
    //                             }
    //                         } else {
    //                             //Debugging, send the client information over serial
    //                             serialQueue.call(printf, "Error reading the start time, device ID: %d\n", time.devID);

    //                             //An error has occurred, signal failure to load the routine
    //                             return 1;
    //                         }
    //                     } else {
    //                         //Debugging, send the client information over serial
    //                         serialQueue.call(printf, "Error reading device ID\n");

    //                         //An error has occurred, signal failure to load the routine
    //                         return 1;
    //                     }
    //                 }
    //                 //Routine loaded, signal success
    //                 return 0;
    //             } else {
    //                 //Debugging, send the client information over serial
    //                 serialQueue.call(printf, "Error reading the timings array, Routine ID: %d\n", currentRoutineID);

    //                 //An error has occurred, signal failure to load the routine
    //                 return 1;
    //             }
    //         }
    //     } else {
    //         //Debugging, send the client information over serial
    //         serialQueue.call(printf, "Error reading routine ID\n");

    //         //Cannot read routine ID, signal failure
    //         return 1;
    //     }
    // }
    // //Debugging, send the client information over serial
    // serialQueue.call(printf, "No routine found matching the requested ID, %d\n", routineID);

    //No routine found with given ID, signal failure
    return 1;
}



//Configure a routine over the serial port
//Pass in the key parameters as a c++ string to create the routine step
uint8_t configRoutineSerial(std::string const& routineConfig) {
    
    // //sendString(routineConfig);  

    // //Create a variable to hold the extracted values
    // deviceTimes time;

    // vector<string> result;

    // stringstream s_stream(routineConfig); //create string stream from the string

    // while(s_stream.good()) {
    //     using namespace std;
    //     string substr;
    //     getline(s_stream, substr, ','); //get first string delimited by comma
    //     result.push_back(substr);
    // }

    // //Check that the correct number of arguments have been supplied
    // if (result.size() != 5) {
    //     //Error, return
    //     return 1;
    // }

    // // for(int i = 0; i<result.size(); i++) {    //print all splitted strings
    // //     sendString(result.at(i));
    // //     sendString("\n");
    // // }
    // //
    // //sendString("\n\n");

    // uint32_t serialRoutineID = std::stoi(result.at(0));


    // //If there is no currenly loaded routine, ie it just been cleared or at startup
    // if (routineID == 0) {
    //     //Set the new routine id based on the transmission
    //     routineID = serialRoutineID;
    //     //else, there is a curently loaded routine, check the new step matches it
    // } else {
    //     if (serialRoutineID != routineID) {
    //         //Error, no match, failure
    //         return 1;
    //     }
    // }        

    // //Parse the data

    // //DeviceID
    // time.devID = std::stoi(result.at(1));

    // //Start time
    // time.startTime = std::stoi(result.at(2));

    // //Stop time
    // time.stopTime = std::stoi(result.at(3));

    // //Device state
    // time.devState = std::stoi(result.at(4));

    // //Add the timing information to the routines vector
    // routine.push_back(time);     

    // sendString("\nRoutine ID: ");
    // sendString(result.at(0));
    // sendString("\nDevice ID: ");
    // sendString(result.at(1));
    // sendString("\nStart Time: ");
    // sendString(result.at(2));
    // sendString("\nStop Time: ");
    // sendString(result.at(3));
    // sendString("\nState: ");
    // sendString(result.at(4));

    // sendString("\n\n");
                
    // //No errors, signal success
    return 0;
}



//Print out the current routine
//Nothing is returned and no parameters need to be passed
void printRoutine(void) {
    // sendString("Routine ID: ");

    // sendString(to_string(routineID));
    // sendString("\n");

    // sendString(to_string(routine.size()));

    // sendString(" timing block(s) are configured on the system\n");

    // //Loop through the routine vector and print out the timing data
    // for (int i = 0; i < routine.size(); i++) {
    //     //Get the timing block
    //     deviceTimes device = routine.at(i);

    //     sendString("Timing block ");
    //     sendString(to_string(i));

    //     sendString("\nDevice ID: ");
    //     sendString(to_string(device.devID));

    //     sendString("\nStart Time: ");
    //     sendString(to_string(device.startTime));

    //     sendString("\nStop Time: ");
    //     sendString(to_string(device.stopTime));

    //     sendString("\nState: ");
    //     sendString(to_string(device.devState));

    //     sendString("\n\n");
    // }
    // sendString("\n");
}


//Clear all routine data
//Nothing is returned and no parameters need to be passed
void clearRoutine(void) {
    // //Clear all routine data
    // routine.clear();

    // routineID = 0;
}

//Test the devices used in a routine
//The routine must have been loaded using configRoutine
//Takes no inputs
//Returns 0 on sucess, non-zero on failure to pass a device test, with the value being the number of devices to fail testing
uint8_t testRoutineDevices(void) {
    //Create a variable to hold the numner of devices failing testing, and set its initial value to be zero
    uint8_t devFails = 0;

    // //Create a set to hold the extracted deviceID's
    // std::set<uint16_t> ids;

    // //Loop through the routine vector and extract the deviceID's
    // for (uint8_t i = 0; i < routine.size(); i++) {
    //     //Get the timing information at i
    //     deviceTimes device = routine.at(i);

    //     //Insert it into the set, this will remove duplicates of the device ID
    //     ids.insert(device.devID);
    // }

    // //Get the set iterator
    // set<uint16_t>::iterator it;

    // //Loop through the deviceID's, testing each
    // for (it = ids.begin(); it != ids.end(); ++it) {

    //     //Loop through all of the devices, testing the one which matches the given id
    //     for (int i = 0; i < devices.size(); i++) {

    //         //If the current devies matches the requested device ID, test it
    //         if (*it == devices[i]->getID()) {

    //             //Test the device, if it fails, increment devFails
    //             if (devices[i]->testDevice()) {
    //                 devFails++;
    //             }
    //         }
    //     }
    // }

    //Return the number of device failures, which should be zero
    return devFails;
}

//Get the duration of a routine
//Returns the duration of the loaded routine in seconds
//The desired routine should be configured before calling using configRoutine
uint16_t getRoutineDuration(void) {

    uint16_t duration = 0;

    // //Loop through the timings array and look for the largest value of timeStop
    // for (deviceTimes n : routine) {
    //     //If the stop time for the current step is greater than any previous stop time
    //     if (n.stopTime >= duration) {

    //         //Update the last time value with the new greatest value
    //         duration = n.stopTime;
    //     }
    // }
    return duration;
}

//Run the routine in a blocking fashion on the current thread
//Nothing is returned and no parameters need to be passed
//The desired routine should be configured before calling using configRoutine
void runBlockingRoutine(void) {

    // //Seconds since starting routine
    // uint16_t elapsed = 0;

    // //Get routine duration
    // uint16_t duration = getRoutineDuration();

    // //While the routine has not finished
    // while (elapsed < duration) {
    //     //Loop through routine and change state if required
    //     for (deviceTimes n : routine) {
    //         //If a device needs to change state
    //         if (elapsed == n.startTime) {
    //             //Loop through the devices array
    //             for (int i = 0; i < devices.size(); i++) {
    //                 //If the device ID matches the specified ID
    //                 if (n.devID == devices[i]->getID()) {
    //                     //Change the state of the device
    //                     devices[i]->changeState(n.devState);
    //                 }
    //             }
    //         }
    //     }

    //     //Increment elapsed
    //     elapsed++;

    //     //Delay for a second before starting again
    //     thread_sleep_for(1000);
    // }

    //Reset devies to default state
    resetRoutineDevices();
}

//reset the devices used in a routine
//The routine must have been loaded using configRoutine
//Takes no inputs
//Returns 0 on success, non-zero on failure to pass a device reset, with the value being the number of devices to fail reseting
void resetRoutineDevices(void) {

    // //Create a set to hold the extracted deviceID's
    // std::set<uint16_t> ids;

    // //Loop through the routine vector and extract the deviceID's
    // for (uint8_t i = 0; i < routine.size(); i++) {
    //     //Get the timing information at i
    //     deviceTimes device = routine.at(i);

    //     //Insert it into the set, this will remove duplicates of the device ID
    //     ids.insert(device.devID);
    // }

    // //Get the set iterator
    // set<uint16_t>::iterator it;

    // //Loop through the deviceID's, reseting each
    // for (it = ids.begin(); it != ids.end(); ++it) {

    //     //Loop through all of the devices, reseting the one which matches the given id
    //     for (int i = 0; i < devices.size(); i++) {

    //         //If the current devies matches the requested device ID, reset it
    //         if (*it == devices[i]->getID()) {

    //             //reset the device
    //             devices[i]->resetDevice();
    //         }
    //     }
    // }
}
