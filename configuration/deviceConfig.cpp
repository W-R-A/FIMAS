#include "deviceConfig.hpp"

uint8_t configDevices(const char *configJSON) {
    //Setup devices according to JSON description
    //Create a JSON parser object
    MbedJSONValue jsonParser;

    //Parse the JSON string and store the result in jsonParser
    parse(jsonParser, configJSON);

    //Loop through the JSON, extracting the device configuration for each device ID
    for (uint8_t i = 0; jsonParser[i].hasMember((char *)"devID"); i++) {
        //Create variables to hold the extracted values
        uint16_t devID;
        uint16_t devPin1;
        short devPin2;
        std::string devType;

        //Caution - always check if the object contains the requested value before attempting to access it, otherwise a hardfault occurs from trying to access invalid memory
        if (jsonParser[i].hasMember((char *)"devID")) {
            //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
            devID = std::stoi(jsonParser[i]["devID"].get<std::string>());

            if (jsonParser[i].hasMember((char *)"devPin1")) {
                //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                devPin1 = std::stoi(jsonParser[i]["devPin1"].get<std::string>());

                if (jsonParser[i].hasMember((char *)"devPin2")) {
                    //Have to get the value as a string and then convert it to an integer due to limitations with the JSON parser library
                    devPin2 = std::stoi(jsonParser[i]["devPin2"].get<std::string>());

                    if (jsonParser[i].hasMember((char *)"devType")) {
                        //Get the device type string
                        devType = jsonParser[i]["devType"].get<std::string>();

                        if (devType.find("perPump") != string::npos) {
                            //Create perPump object
                            devices[i] = new perPump(digitalOutputs[devPin1-1], devID);

                        } else if (devType.find("solValve") != string::npos) {
                            //Create solValve object
                            devices[i] = new solValve(digitalOutputs[devPin1-1], devID);

                        } else if (devType.find("sixValve") != string::npos) {
                            //Create sixValve object
                            devices[i] = new sixValve(digitalOutputs[devPin1-1], digitalOutputs[devPin2-1], devID);

                        } else if (devType.find("switchValve") != string::npos) {
                            //Check if the switchvalve is working in one or two pin mode
                            if (devPin2 == -1) {
                                //Create switchValve object with one pin
                                devices[i] = new switchValve(digitalOutputs[devPin1-1], devID);
                            } else {
                                //Create switchValve object with two pins
                                devices[i] = new switchValve(digitalOutputs[devPin1-1], digitalOutputs[devPin2-1], devID);
                            }
                        } else {
                            //Debugging, send the client information over serial
                            serialQueue.call(printf, "Error creating object, could not determine device type, device ID: %d, device pin 1: %d, device pin 2: %d\n", devID, devPin1, devPin2);

                            //An error has occurred, signal failure to configure
                            return 1;
                        }

                    } else {
                        //Debugging, send the client information over serial
                        serialQueue.call(printf, "Error reading device pin 2, device ID: %d, device pin 1: %d\n", devID, devPin1);

                        //An error has occurred, signal failure to configure
                        return 1;
                    }
                } else {
                    //Debugging, send the client information over serial
                    serialQueue.call(printf, "Error reading device pin 1, device ID: %d, device pin 1: %d\n", devID, devPin1);

                    //An error has occurred, signal failure to configure
                    return 1;
                }
            } else {
                //Debugging, send the client information over serial
                serialQueue.call(printf, "Error reading device pin 1, device ID: %d\n", devID);

                //An error has occurred, signal failure to configure
                return 1;
            }
        } else {
            //Debugging, send the client information over serial
            serialQueue.call(printf, "Error reading device ID\n");

            //An error has occurred, signal failure to configure
            return 1;
        }
    }
    //No errors, signal success
    return 0;
}
