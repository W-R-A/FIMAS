#include "routineConfig.hpp"

//Create a vector to store device times for the routine
std::vector<deviceTimes> routine;

//Configure a routine to be run
//Takes the JSON string of routines and the ID of the desired routine to load
//Returns 0 on sucess, non-zero on failure
uint8_t configRoutine(const char *configJSON, uint16_t routineID) {
    //Setup routines according to JSON description
    //Create a JSON parser object
    MbedJSONValue jsonParser;

    //Parse the JSON string and store the result in jsonParser
    parse(jsonParser, configJSON);

    //check for name/ID of routine
    //check for timings array
    //loop through array, extracting timing data

    //Loop through all of the routines that have an valid ID
    for (uint8_t i = 0; jsonParser[i].hasMember((char *)"routineID"); i++) {

        //Caution - always check if the object contains the requested value before attempting to access it, otherwise a hardfault occurs from trying to access invalid memory
        //Get the current routine ID
        if (jsonParser[i].hasMember((char *)"routineID")) {
            uint16_t currentRoutineID = std::stoi(jsonParser[i]["routineID"].get<std::string>());

            //If the current iteration is the requested routine ID, load the data into the vector
            if (routineID == currentRoutineID) {

                //Check if the timings array is present
                if (jsonParser[i].hasMember((char *)"timings")) {

                    //Loop through the timings array, extracting timing info
                    for (uint16_t j = 0; jsonParser[i]["timings"][j].hasMember((char *)"devID"); j++) {
                        //Create a variable to hold the extracted values
                        deviceTimes time;

                        //Check for the deviceID
                        if (jsonParser[i]["timings"][j].hasMember((char *)"devID")) {
                            //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                            time.devID = std::stoi(jsonParser[i]["timings"][j]["devID"].get<std::string>());

                            //Check for the start time
                            if (jsonParser[i]["timings"][j].hasMember((char *)"timeStart")) {
                                //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                                time.startTime = std::stoi(jsonParser[i]["timings"][j]["timeStart"].get<std::string>());

                                //Check for the stop time
                                if (jsonParser[i]["timings"][j].hasMember((char *)"timeStop")) {
                                    //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                                    time.stopTime = std::stoi(jsonParser[i]["timings"][j]["timeStop"].get<std::string>());

                                    //Check for the device state
                                    if (jsonParser[i]["timings"][j].hasMember((char *)"state")) {
                                        //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                                        time.devState = std::stoi(jsonParser[i]["timings"][j]["state"].get<std::string>());

                                        //Add the timing information to the routines vector
                                        routine.emplace_back(time);
                                    } else {
                                        //Debugging, send the client information over serial
                                        serialQueue.call(printf, "Error reading the device state, device ID: %d, start time: %d, stop time: %d\n", time.devID, time.startTime, time.stopTime);

                                        //An error has occured, signal failure to load the routine
                                        return 1;
                                    }
                                } else {
                                    //Debugging, send the client information over serial
                                    serialQueue.call(printf, "Error reading the stop time, device ID: %d, start time: %d\n", time.devID, time.startTime);

                                    //An error has occured, signal failure to load the routine
                                    return 1;
                                }
                            } else {
                                //Debugging, send the client information over serial
                                serialQueue.call(printf, "Error reading the start time, device ID: %d\n", time.devID);

                                //An error has occured, signal failure to load the routine
                                return 1;
                            }
                        } else {
                            //Debugging, send the client information over serial
                            serialQueue.call(printf, "Error reading device ID\n");

                            //An error has occured, signal failure to load the routine
                            return 1;
                        }
                    }
                    //Routine loaded, signal success
                    return 0;
                } else {
                    //Debugging, send the client information over serial
                    serialQueue.call(printf, "Error reading the timings array, Routine ID: %d\n", currentRoutineID);

                    //An error has occured, signal failure to load the routine
                    return 1;
                }
            }
        } else {
            //Debugging, send the client information over serial
            serialQueue.call(printf, "Error reading routine ID\n");

            //Cannot read routine ID, signal failure
            return 1;
        }
    }
    //Debugging, send the client information over serial
    serialQueue.call(printf, "No routine found matching the requested ID, %d\n", routineID);

    //No routine found with given ID, signal failure
    return 1;
}

//Print out the current routine
//Nothing is returned and no parameters need to be passed
void printRoutine(void) {
    //Loop through the routine vector and print out the timing data
    for (uint8_t i = 0; i < routine.size(); i++) {
        deviceTimes device = routine.at(i);
        serialQueue.call(printf, "Timing block: %u,", i);
        serialQueue.call(printf, "deviceID: %u, timeStart: %u, timeStop: %u, state: %u\n", device.devID, device.startTime, device.stopTime, device.devState);
    }
}