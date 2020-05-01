//Functions.js
//Used within FIMAS to hold functions such as the population of drop-down boxes, and fetching JSON data

//Test JSON data for devices and routines
var tstDevices = "[{\"devID\":\"1000\",\"devName\":\"Sample Pump\",\"devType\":\"perPump\",\"devPin1\":\"1\",\"devPin2\":\"-1\"},{\"devID\":\"1001\",\"devName\":\"Control Valve\",\"devType\":\"solValve\",\"devPin1\":\"2\",\"devPin2\":\"-1\"},{\"devID\":\"1002\",\"devName\":\"6-Port Valve\",\"devType\":\"sixValve\",\"devPin1\":\"3\",\"devPin2\":\"4\"}]";

var tstRoutines = '[{"routineID":"1004","name":"AlCl","timings":[{"devID":"1000","timeStart":"0","timeStop":"4","state":"0"},{"devID":"1000","timeStart":"4","timeStop":"9","state":"1"},{"devID":"1000","timeStart":"9","timeStop":"15","state":"0"},{"devID":"1001","timeStart":"0","timeStop":"4","state":"1"},{"devID":"1001","timeStart":"4","timeStop":"8","state":"0"},{"devID":"1001","timeStart":"8","timeStop":"15","state":"0"},{"devID":"1002","timeStart":"0","timeStop":"3","state":"1"},{"devID":"1002","timeStart":"3","timeStop":"7","state":"0"},{"devID":"1002","timeStart":"7","timeStop":"15","state":"1"}]},{"routineID":"1003","name":"CuSO4","timings":[{"devID":"1000","timeStart":"0","timeStop":"4","state":"1"},{"devID":"1000","timeStart":"4","timeStop":"9","state":"0"},{"devID":"1000","timeStart":"9","timeStop":"15","state":"1"},{"devID":"1001","timeStart":"0","timeStop":"6","state":"0"},{"devID":"1001","timeStart":"6","timeStop":"8","state":"1"},{"devID":"1001","timeStart":"8","timeStop":"15","state":"0"},{"devID":"1002","timeStart":"0","timeStop":"3","state":"1"},{"devID":"1002","timeStart":"3","timeStop":"7","state":"0"},{"devID":"1002","timeStart":"7","timeStop":"15","state":"1"}]}]';






//Declare the populate routines function - This will populate a specified dropdown based on the routines.json file
//Need to pass the dropdown element ID, as a string
//Returns an array with a code and message which can be accessed in return .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given ID does not exist
//2 - There is more than one element with the given ID in the document
//3 - The given ID does not correspond to a dropdown type 
//4 - There is an issue loading the routines file
function populateRoutines(ddID) {
    //Check to ensure a valid ID has been given
    //Check if ID exists
    //Check for multiple elements with the same ID
    //Check if type is dropdown

    //Check if the element ID given exists
    if ($("#" + ddID).length == 0) {
        //No element with the given ID exists
        return {
            code: 1,
            msg: "The given ID does not exist",
        };
    }

    //Check if there are multiple elements with the same ID
    if ($("#" + ddID).length > 1) {
        //There are multiple elements with the same ID
        return {
            code: 2,
            msg: "There is more than one element with the given ID in the document",
        };
    }

    //Check if there the element ID references a dropdown
    if (!($("#" + ddID).is("select"))) {
        //There given ID does not reference a dropdown
        return {
            code: 3,
            msg: "The given ID does not correspond to a dropdown type",
        };
    }

    //Ensure that the dropdown is empty
    $('#' + ddID).empty();

    //Set default option as select device, and make it disabled
    $('#' + ddID).append('<option selected="true" disabled>Select Routine</option>');
    $('#' + ddID).prop('selectedIndex', 0);

    //Define some temporary variables to hold the HTML
    var opHTML = '';

    //Testing - use static json
    response = $.parseJSON(tstRoutines)

    //Get the devices on the system in a JSON format
    // $.getJSON("/routines.json", function (response) {

    //Loop through the response and fill in the dropdown
    $.each(response, function (i, item) {
        //Generate the dropdown html
        opHTML += '<option class=' + item.routineID + '>' + item.name + '</option>';
    });


    //Append the html to the dropdown
    $('#' + ddID).append(opHTML);
    // });

    //Return success
    return {
        code: 0,
        msg: "Success!",
    };
}





//Declare the get device name function - This will return the device name as a string given the device id.
//Need to pass the device ID, as a string
//Returns an array with a code, message and device name which can be accessed in return .name, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given device ID does not exist in the devices.json file 
//2 - There is an issue loading the devices.json file
//3 - There is no name associated with the deviceID
function getDeviceName(deviceID) {
    //Load devices file
    //Check if ID exists
    //Return name of the device

    //Testing - use static json
    response = $.parseJSON(tstDevices)

    //Get the devices on the system in a JSON format
    // $.getJSON("/routines.json", function (response) {

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
                code: 3,
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

    // });
}






//Declare the get duration function - This will return the duration of the routine given the timings array
//Need to pass the timings array in as a string
//Returns an array with a code, message and duration which can be accessed in return .dur, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - There was a problem parsing the JSON string
//2 - There was an issue extracting the timings data from the JSON string
function getDuration(timings) {
    //Parse JSON string containing the timings array
    //Loop through the array looking for the largest value of timeStop
    //Return the longest found timeStop as duration

    //Try to parse the JSON, return an error is it cannot be parsed
    try {
        times = JSON.parse(timings);
    } catch (e) {
        //If there was an error parsing the JSON, return an error
        return {
            code: 1,
            msg: "There was a problem parsing the JSON string",
            dur: 0,
        };
    }

    //Declare a variable for the duration
    var duration = -1;

    //Loop through the timings array and look for the largest value of timeStop
    for (i in times) {
        //If the stop time for the current step is greater than any previous stop time
        if (parseInt(times[i].timeStop) >= duration) {

            //Update the last time value with the new greatest value
            duration = parseInt(times[i].timeStop);
        }
    }

    //If the duration is valid, greater than 0, return in, else return an error
    if (duration > 0) {
        //Return the duration of the routine
        return {
            code: 0,
            msg: "Success",
            dur: duration,
        };
    }

    //There was an issue extracting the timings data from the JSON string, return an error
    return {
        code: 2,
        msg: "There was an issue extracting the timings data from the JSON string",
        dur: 0,
    };
}






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
    for (i in times) {
        //Extract all of the deviceID's to the devices array
        devices.push(parseInt(times[i].devID));
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
    }
}



//Declare the genVisHTML function - This will return the a string containing the rows html to append to the appropriate figure 
//Need to pass the timings array in as a string
//Returns an array with a code, message and the html which can be accessed in return .html, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - There was a problem parsing the JSON string
function genVisHTML(timings) {

    //Parse timings JSON
    //Sort the timings array by start time
    //Create a unique list of the deviceIDs used in the routine buy using getUniqueDevices()
    //Create an array to hold the unique deviceID timing span blocks
    //Get the names of the devices using getDeviceName()
    //Loop through the timings array, generating the span blocks and appending to the specified deviceID row
    //Append closing div tags to each device row
    //Concatenate the html together and return as .html

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

    //Sort the timings by start time
    times.sortByProperty(sortByProperty("timeStart"));

    //Get a list of all devices used
    var uniqueDevices = getUniqueDevices(timings);

    //Check if failed - code non-zero
    if (uniqueDevices.code) {
        //Alert that an error occurred
        alert("Error getting the list of devices used");

        //Log specific error
        console.log(duration.msg);

        //Break
        break;
    }

    //Create an array to store the html row data
    var htmlRows = [];

    //Loop through the unique devices, and create the initial row html
    for (i in uniqueDevices.devices) {
        //Attempt to get the device name from the deviceID
        let devName = getDeviceName(uniqueDevices.devices[i]);

        //Check if failed - code non-zero
        if (devName.code) {
            //Alert that an error occurred
            alert("Error getting device name");

            //Log specific error
            console.log(devName.msg);

            //Break
            break;
        }

        //Initialise the row with the name of the device and the class for the chart
        htmlRows[i] = '<div class="row"> <h6>' + devName.name + '</h6><div class="chart">';
    }




    //Loop through the timings array and look for the largest value of timeStop
    for (i in times) {
        //If the stop time for the current step is greater than any previous stop time
        if (parseInt(times[i].timeStop) >= duration) {

            //Update the last time value with the new greatest value
            duration = parseInt(times[i].timeStop);
        }
    }

    //If the duration is valid, greater than 0, return in, else return an error
    if (duration > 0) {
        //Return the duration of the routine
        return {
            code: 0,
            msg: "Success",
            dur: duration,
        };
    }

    //There was an issue extracting the timings data from the JSON string, return an error
    return {
        code: 2,
        msg: "There was an issue extracting the timings data from the JSON string",
        dur: 0,
    };
}