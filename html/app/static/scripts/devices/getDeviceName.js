//Declare the get device name function - This will return the device name as a string given the device id.
//Need to pass the device ID, as a string and an array of the devices on the system
//Returns an array with a code, message and device name which can be accessed in return .name, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given device ID does not exist in the devices.json file 
//2 - There is no name associated with the deviceID
function getDeviceName(deviceID, devices) {
    //Load devices file
    //Check if ID exists
    //Return name of the device

    //Parse the JSON
    var response = $.parseJSON(devices.json);

    //Loop through the response and look for the requested deviceID
    for (i in response) {
        //Check if the current device has the ID requested
        if (parseInt(deviceID) == parseInt(response[i].devID)) {
            //Check if the device name exists
            if (typeof (response[i].devName) != "undefined") {
                //Return success with the device name
                return {
                    code: 0,
                    msg: "Success!",
                    name: response[i].devName,
                };
            }
            //If there is a device ID with no name, return an error
            return {
                code: 2,
                msg: "There is no name associated with the deviceID",
                name: "undefined",
            };
        }
    }
    //If at the end of the routines file there is no matching deviceID, return an error
    return {
        code: 1,
        msg: "The given device ID does not exist in the devices.json file",
        name: "undefined",
    };
}
