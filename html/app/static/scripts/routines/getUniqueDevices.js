//Declare the unique ids function - This will return an array of unique deviceIds given the timings array
//Need to pass the timings array in as a string
//Returns an array with a code, message and device id array which can be accessed in return .devices, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - There was a problem parsing the JSON string
function getUniqueDevices(timings) {
    //Parse JSON string containing the timings array
    //Loop through the array looking for unique deviceID's 
    //Return an array of deviceIDs
    //Try to parse the JSON, return an error is it cannot be parsed
    try {
        times = JSON.parse(timings);
    } catch (e) {
        //If there was an error parsing the JSON, return an error
        return {
            code: 1,
            msg: "There was a problem parsing the JSON string",
            devices: [],
        };
    }

    //Declare a array to hold the deviceID's
    let devices = [];

    //Loop through the timings array and extract all of the deviceID's
    for (ii in times) {
        //Extract all of the deviceID's to the devices array
        devices.push(parseInt(times[ii].devID));
    }

    //Get a array of non-duplicate deviceIDs used in the routine
    let uniqueDevices = [...new Set(devices)];

    //Return the devices used in the routine
    return {
        code: 0,
        msg: "Success",
        devices: uniqueDevices,
    };
}
//Declare the sortByProperty function - This will sort a JSON array of objects by property, when called in array.sort();
//From https://medium.com/@asadise/sorting-a-json-array-according-one-property-in-javascript-18b1d22cd9e9
//Accessed 01/05/2020
function sortByProperty(property) {

    //Get the two values to compare, a and b
    return function (a, b) {

        //If the element in a is greater than the element in b
        if (a[property] > b[property]) {

            //Return 1 indicating that a is bigger 
            return 1;
        }


        //If the element in b is greater than the element in a
        else if (a[property] < b[property])
            //Return 1 indicating that b is bigger 
            return -1;

        //Return 0 is the value of the elements is the same
        return 0;
    };
}
