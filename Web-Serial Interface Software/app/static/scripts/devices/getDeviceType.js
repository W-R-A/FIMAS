//Declare the get device type function - This will return the device type as a string given the device ID.
//Need to pass the device ID, as a string and an array of the devices
//Returns an array with a code, message and device type which can be accessed in return .type, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given device ID does not exist in the devices parameter
//3 - There is no type associated with the deviceID
function getDeviceType(deviceID, devices) {
    //Check if ID exists
    //Return type of the device

    //Parse the JSON
    var response = $.parseJSON(devices.json);

    //Loop through the response and look for the requested deviceID
    for (j in response) {

        //Check if the current device has the ID requested
        if (parseInt(deviceID) == parseInt(response[j].devID)) {

            //Check if the device type exists
            if (typeof (response[j].devType) != "undefined") {

                //Return success with the device type
                return {
                    code: 0,
                    msg: "Success!",
                    type: response[j].devType,
                };
            }
            //If there is a device ID with no type, return an error
            return {
                code: 3,
                msg: "There is no type associated with the deviceID",
                type: "undefined",
            };
        }
    }
    //If at the end of the routines file there is no matching deviceID, return an error
    return {
        code: 1,
        msg: "The given device ID does not exist in the devices.json file",
        type: "undefined",
    };
}

//Declare the get device type function - This will return request and return the device type as a string given the device ID.
//Need to pass the device ID, as a string and an array of the devices
//Returns an array with a code, message and device type which can be accessed in return .type, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given device ID does not exist in the devices parameter
//3 - There is no type associated with the deviceID
function getDeviceTypeRequest(deviceID) {
    //Check if ID exists
    //Return type of the device

    //Parse the JSON
    var response = $.parseJSON(getDevices().json);

    //Loop through the response and look for the requested deviceID
    for (j in response) {

        //Check if the current device has the ID requested
        if (parseInt(deviceID) == parseInt(response[j].devID)) {

            //Check if the device type exists
            if (typeof (response[j].devType) != "undefined") {

                //Return success with the device type
                return {
                    code: 0,
                    msg: "Success!",
                    type: (response[j].devType).toString(),
                };
            }
            //If there is a device ID with no type, return an error
            return {
                code: 3,
                msg: "There is no type associated with the deviceID",
                type: "undefined",
            };
        }
    }
    //If at the end of the routines file there is no matching deviceID, return an error
    return {
        code: 1,
        msg: "The given device ID does not exist in the devices.json file",
        type: "undefined",
    };
}
