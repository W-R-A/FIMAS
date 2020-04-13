#include "routineConfig.hpp"

uint8_t configRoutine(const char *configJSON, uint16_t routineID) {
    //Setup routines accroding to JSON description
    //Create a JSON parser object
    MbedJSONValue jsonParser;

    //Parse the JSON string and store the result in jsonParser
    parse(jsonParser, ROUTINE1);

    //check for name/ID of routine
    //check for timings array
    //loop through array, extracting timing data

    for (uint8_t i = 0; jsonParser[i].hasMember("routineID"); i++) {
        if (jsonParser[i].hasMember("routineID")) {

            //Loop through the JSON, extracting routine configuration info
            for (uint8_t i = 0; jsonParser[i].hasMember("name"); i++) {
                //Create a variable to hold the extracted values
                deviceTimes time;

                //Caution - always check if the object contains the requested value before attempting to access it, otherwise a hardfault occurs from trying to access invalid memory
                if (jsonParser[i]["timings"].hasMember("devID")) {
                    //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                    time.devID = std::stoi(jsonParser[i]["timings"]["devID"].get<std::string>());

                    if (jsonParser[i]["timings"].hasMember("timeStart")) {
                        //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                        time.startTime = std::stoi(jsonParser[i]["timings"]["timeStart"].get<std::string>());

                        if (jsonParser[i]["timings"].hasMember("timeStop")) {
                            //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                            time.stopTime = std::stoi(jsonParser[i]["timings"]["timeStop"].get<std::string>());

                            if (jsonParser[i]["timings"].hasMember("devState")) {
                                //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                                time.devState = std::stoi(jsonParser[i]["timings"]["devState"].get<std::string>());

                            } else {
                                //Debugging, send the client information over serial
                                serialQueue.call(printf, "Error reading the device state, device ID: %d, start time: %d, stop time: %d\n", time.devID, time.startTime, time.stopTime);
                            }
                        } else {
                            //Debugging, send the client information over serial
                            serialQueue.call(printf, "Error reading the stop time, device ID: %d, start time: %d\n", time.devID, time.startTime);
                        }
                    } else {
                        //Debugging, send the client information over serial
                        serialQueue.call(printf, "Error reading the start time, device ID: %d\n", time.devID);
                    }
                } else {
                    //Debugging, send the client information over serial
                    serialQueue.call(printf, "Error reading device ID\n");
                }
            }
        }
    }
}