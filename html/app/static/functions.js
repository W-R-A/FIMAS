//Functions.js
//Used within FIMAS to hold functions such as the population of drop-down boxes, and fetching JSON data

//Test JSON data for devices and routines
var tstDevices = "[{\"devID\":\"1000\",\"devName\":\"Sample Pump\",\"devType\":\"perPump\",\"devPin1\":\"1\",\"devPin2\":\"-1\"},{\"devID\":\"1001\",\"devName\":\"Control Valve\",\"devType\":\"solValve\",\"devPin1\":\"2\",\"devPin2\":\"-1\"},{\"devID\":\"1002\",\"devName\":\"6-Port Acid Valve\",\"devType\":\"sixValve\",\"devPin1\":\"3\",\"devPin2\":\"4\"}]";

var tstRoutines = '[{"routineID":"1004","name":"AlCl","timings":[{"devID":"1000","timeStart":"0","timeStop":"4","state":"0"},{"devID":"1000","timeStart":"4","timeStop":"9","state":"1"},{"devID":"1000","timeStart":"9","timeStop":"15","state":"0"},{"devID":"1000","timeStart":"15","timeStop":"24","state":"1"},{"devID":"1000","timeStart":"24","timeStop":"56","state":"0"},{"devID":"1000","timeStart":"56","timeStop":"60","state":"1"},{"devID":"1001","timeStart":"0","timeStop":"4","state":"1"},{"devID":"1001","timeStart":"4","timeStop":"8","state":"0"},{"devID":"1001","timeStart":"8","timeStop":"15","state":"1"},{"devID":"1001","timeStart":"15","timeStop":"29","state":"0"},{"devID":"1001","timeStart":"29","timeStop":"47","state":"1"},{"devID":"1001","timeStart":"47","timeStop":"60","state":"0"},{"devID":"1002","timeStart":"0","timeStop":"3","state":"1"},{"devID":"1002","timeStart":"3","timeStop":"7","state":"0"},{"devID":"1002","timeStart":"7","timeStop":"15","state":"1"},{"devID":"1002","timeStart":"15","timeStop":"28","state":"0"},{"devID":"1002","timeStart":"28","timeStop":"40","state":"1"},{"devID":"1002","timeStart":"40","timeStop":"60","state":"0"}]},{"routineID":"1003","name":"CuSO4","timings":[{"devID":"1000","timeStart":"0","timeStop":"4","state":"1"},{"devID":"1000","timeStart":"4","timeStop":"9","state":"0"},{"devID":"1000","timeStart":"9","timeStop":"15","state":"1"},{"devID":"1001","timeStart":"0","timeStop":"6","state":"0"},{"devID":"1001","timeStart":"6","timeStop":"8","state":"1"},{"devID":"1001","timeStart":"8","timeStop":"15","state":"0"},{"devID":"1002","timeStart":"0","timeStop":"3","state":"1"},{"devID":"1002","timeStart":"3","timeStop":"7","state":"0"},{"devID":"1002","timeStart":"7","timeStop":"15","state":"1"}]}]';


//Declare the getDevices function - This will get the devices.json file when running in production, or some static text when running in development
//No parameters need to be passed
//Returns an array with a jsonString code and message which can be accessed in return .code and .msg .json
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The devices.json file could not be loaded
function getDevices() {

    //Get the devices.json file, then return the contents as a string


    let res = "undefined";

    // Set the global configs to synchronous 
    $.ajaxSetup({
        async: false
    });

    //Production, get the devices.json file from the server
    $.getJSON("/devices.json", function (response) {
        res = response;
    });

    // Set the global configs back to asynchronous 
    $.ajaxSetup({
        async: true
    });

    if (res != "undefined") {
        return {
            code: 0,
            msg: "Success",
            json: JSON.stringify(res),
        };
    }
    return {
        code: 1,
        msg: "The devices.json file could not be loaded",
        json: "undefined",
    };

}



//Declare the getRoutines function - This will get the routines.json file when running in production, or some static text when running in development
//No parameters need to be passed
//Returns an array with a jsonString code and message which can be accessed in return .code and .msg .json
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The routines.json file could not be loaded
function getRoutines() {

    //Get the routines.json file, then return the contents as a string

    let res = "undefined";

    // Set the global configs to synchronous 
    $.ajaxSetup({
        async: false
    });

    //Production, get the devices.json file from the server
    $.getJSON("/routines.json", function (response) {
        res = response;
    });

    // Set the global configs back to asynchronous 
    $.ajaxSetup({
        async: true
    });
    if (res != "undefined") {
        return {
            code: 0,
            msg: "Success",
            json: JSON.stringify(res),
        };
    }
    return {
        code: 1,
        msg: "The devices.json file could not be loaded",
        json: "undefined",
    };

}




//Declare the getTypes function - This will get the types.json file when running in production, or some static text when running in development
//No parameters need to be passed
//Returns an array with a jsonString code and message which can be accessed in return .code and .msg .json
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The types.json file could not be loaded
function getTypes() {

    //Get the devices.json file, then return the contents as a string

    //Testing, return a static string
    return {
        code: 0,
        msg: "The given ID does not exist",
        json: tstTypes,
    };

    //Production, get the devices.json file from the server
    // $.getJSON("/types.json", function (response) {
    //     return {
    //         code: 1,
    //         msg: "The given ID does not exist",
    //         json: response,
    //     };
    // });

}


//Declare the getPins function - This will get the pins.json file when running in production, or some static text when running in development
//No parameters need to be passed
//Returns an array with a jsonString code and message which can be accessed in return .code and .msg .json
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The pins.json file could not be loaded
function getPins() {

    //Get the devices.json file, then return the contents as a string

    //Testing, return a static string
    return {
        code: 0,
        msg: "The given ID does not exist",
        json: tstDevPins,
    };

    //Production, get the devices.json file from the server
    // $.getJSON("/pins.json", function (response) {
    //     return {
    //         code: 1,
    //         msg: "The given ID does not exist",
    //         json: response,
    //     };
    // });

}


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

    //Get the routine info 
    let routines = getRoutines();

    //Check if failed - code non-zero
    if (routines.code) {

        //An error has occurred loading the routines file
        return {
            code: 4,
            msg: "There was an issue loading the routines file",
        };
    }

    //Parse the JSON
    var response = $.parseJSON(routines.json);

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



//Declare the populate devices function - This will populate a specified dropdown based on the devices.json file
//Need to pass the dropdown element ID, as a string
//Returns an array with a code and message which can be accessed in return .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given ID does not exist
//2 - There is more than one element with the given ID in the document
//3 - The given ID does not correspond to a dropdown type 
//4 - There was an issue loading the devices file
function populateDevices(ddID) {

    //Check to ensure a valid ID has been given
    //Check if ID exists
    //Check for multiple elements with the same ID
    //Check if type is dropdown
    //Get devices.json file
    //Populate dropdown

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
    $('#' + ddID).append('<option selected="true" disabled>Select Device</option>');
    $('#' + ddID).prop('selectedIndex', 0);

    //Define some temporary variables to hold the HTML
    var opHTML = '';

    //Get the device info 
    let devices = getDevices();

    //Check if failed - code non-zero
    if (devices.code) {

        //An error has occurred loading the devices file
        return {
            code: 4,
            msg: "There was an issue loading the devices file",
        };
    }

    //Parse the JSON
    var response = $.parseJSON(devices.json);

    //Loop through the response and fill in the dropdown
    $.each(response, function (i, item) {
        //Generate the dropdown html
        opHTML += '<option id=' + item.devID + ' class =' + item.devType + '>' + item.devName + '</option>';
    });

    //Append the html to the dropdown
    $('#' + ddID).append(opHTML);

    //Return success
    return {
        code: 0,
        msg: "Success!",
    };
}




//Declare the populate device table function - This will populate a specified table based on the devices.json file
//Need to pass the table element ID, as a string
//Returns an array with a code and message which can be accessed in return .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given ID does not exist
//2 - There is more than one element with the given ID in the document
//3 - The given ID does not correspond to a table type 
//4 - There was an issue loading the devices file
function populateDeviceTable(tableID) {

    //Check to ensure a valid ID has been given
    //Check if ID exists
    //Check for multiple elements with the same ID
    //Check if type is table
    //Get devices.json file
    //Populate table

    //Check if the element ID given exists
    if ($("#" + tableID).length == 0) {
        //No element with the given ID exists
        return {
            code: 1,
            msg: "The given ID does not exist",
        };
    }

    //Check if there are multiple elements with the same ID
    if ($("#" + tableID).length > 1) {
        //There are multiple elements with the same ID
        return {
            code: 2,
            msg: "There is more than one element with the given ID in the document",
        };
    }

    //Check if there the element ID references a table
    if (!($("#" + tableID).is("table"))) {
        //There given ID does not reference a table
        return {
            code: 3,
            msg: "The given ID does not correspond to a table type",
        };
    }

    //Ensure that the table is empty
    $('#' + tableID).empty();


    //Define a variable to hold the table html and initialise it with the table headings
    let trHTML = '<tr><th>Device Name</th><th>Device Type</th><th>Primary Interface</th><th>Secondary Interface</th><th>Test Device</th></tr>';

    //Get the device info 
    let devices = getDevices();

    //Check if failed - code non-zero
    if (devices.code) {

        //An error has occurred loading the devices file
        return {
            code: 4,
            msg: "There was an issue loading the devices file",
        };
    }

    //Parse the JSON
    var response = $.parseJSON(devices.json);

    //Loop through the response and fill in the table
    $.each(response, function (i, item) {
        //Generate the table HTML from the received JSON file
        trHTML += '<tr><td>' + item.devName + '</td><td>' + item.devType + '</td><td>' + item.devPin1 + '</td><td>' + item.devPin2 + '</td><td><button class="btnTest" id ="' + item.devID + '">Test Device</button></td></tr>';

        //Replace -1 pins to not used
        trHTML = trHTML.replace("-1", "Not Used");

        //Replace the abbreviated device names with the full ones          
        trHTML = trHTML.replace("perPump", "Peristaltic Pump");
        trHTML = trHTML.replace("solValve", "Solenoid Valve");
        trHTML = trHTML.replace("sixValve", "6-Port Valve");
        trHTML = trHTML.replace("switchValve", "Switching Valve");

    });

    //Append the html to the table
    $('#' + tableID).append(trHTML);

    //Return success
    return {
        code: 0,
        msg: "Success!",
    };
}




//Declare the populate types function - This will populate a specified dropdown based on the types.json file
//Need to pass the dropdown element ID, as a string
//Returns an array with a code and message which can be accessed in return .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given ID does not exist
//2 - There is more than one element with the given ID in the document
//3 - The given ID does not correspond to a dropdown type 
//4 - There is an issue loading the types file
function populateTypes(ddID) {
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
    $('#' + ddID).append('<option selected="true" disabled>Select Type of Device</option>');
    $('#' + ddID).prop('selectedIndex', 0);

    //Define some temporary variables to hold the HTML
    var opHTML = '';

    //Get the device info 
    let types = getTypes();

    //Check if failed - code non-zero
    if (types.code) {

        //An error has occurred loading the types file
        return {
            code: 4,
            msg: "There was an issue loading the types file",
        };
    }

    //Parse the JSON
    var response = $.parseJSON(types.json);

    //Loop through the response and fill in the dropdown
    $.each(response, function (i, item) {
        //Generate the dropdown html
        opHTML += '<option class=' + item.devType + '>' + item.friendlyName + '</option>';
    });


    //Append the html to the dropdown
    $('#' + ddID).append(opHTML);

    //Return success
    return {
        code: 0,
        msg: "Success!",
    };
}


//Declare the populate pins function - This will populate a specified dropdown based on the pins.json file
//Need to pass the dropdown element ID, as a string
//Returns an array with a code and message which can be accessed in return .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given ID does not exist
//2 - There is more than one element with the given ID in the document
//3 - The given ID does not correspond to a dropdown type 
//4 - There was an issue loading the pins file
function populatePins(ddID) {

    //Check to ensure a valid ID has been given
    //Check if ID exists
    //Check for multiple elements with the same ID
    //Check if type is dropdown
    //Get pins.json file
    //Populate dropdown

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
    $('#' + ddID).append('<option selected="true" disabled>Select Interface </option>');
    $('#' + ddID).prop('selectedIndex', 0);

    //Define some temporary variables to hold the HTML
    var opHTML = '';

    //Get the device info 
    let pins = getPins();

    //Check if failed - code non-zero
    if (pins.code) {

        //An error has occurred loading the pins file
        return {
            code: 4,
            msg: "There was an issue loading the pins file",
        };
    }

    //Parse the JSON
    var response = $.parseJSON(pins.json);

    //Loop through the response and fill in the dropdown
    $.each(response, function (i, item) {
        //Generate the dropdown html
        if (ddID == "primary_dropdown") {
            if ((item.type == "output")) {
                opHTML += '<option id=' + item.pin + ' class =' + item.type + '> Output ' + item.pin + '</option>';
            }
        }
        else {
            if ((item.type == "output")) {
                opHTML += '<option id=' + item.pin + ' class =' + item.type + '> Output ' + item.pin + '</option>';
            } else {
                opHTML += '<option id=' + item.pin + ' class =' + item.type + '> Input ' + item.pin + '</option>';
            }
        }
    });

    //Add a unused option to the secondary interface dropdown
    if (ddID == "secondary_dropdown") {
        opHTML += '<option id="-1" >Not Used</option>';
    }

    //Append the html to the dropdown
    $('#' + ddID).append(opHTML);

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
    var response = $.parseJSON(tstDevices)

    //Get the devices on the system in a JSON format
    // $.getJSON("/devices.json", function (response) {

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


//Declare the get device type function - This will return the device type as a string given the device ID.
//Need to pass the device ID, as a string
//Returns an array with a code, message and device type which can be accessed in return .type, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given device ID does not exist in the devices.json file 
//2 - There is an issue loading the devices.json file
//3 - There is no type associated with the deviceID
function getDeviceType(deviceID) {

    //Load devices file
    //Check if ID exists
    //Return type of the device

    //Testing - use static json
    var response = $.parseJSON(tstDevices);

    //Get the devices on the system in a JSON format
    // $.getJSON("/devices.json", function (response) {

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
    for (k in times) {
        //If the stop time for the current step is greater than any previous stop time
        if (parseInt(times[k].timeStop) >= duration) {

            //Update the last time value with the new greatest value
            duration = parseInt(times[k].timeStop);
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



//Declare the get pretty state function - This will return a string containing the pretty state given a state and device type
//Need to pass the state and device type
//Returns an array with a code, message and prettyState which can be accessed in return .pState, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The state and deviceType do not match
function getPrettyState(state, devID) {

    //Lookup state and device type and return as pretty state as a string
    //If type and state do not match, throw an error

    //Convert state to an integer
    state = parseInt(state);

    //Declare a variable to hold the pretty state of the device
    var prettyState = "undefined";

    //Switch based on the device type
    switch (devID) {

        //If the device is a peristaltic pump, two states, on and off
        //Any other states should throw and an error
        case "perPump": {
            switch (state) {
                case 0:
                    prettyState = "Off";
                    break;
                case 1:
                    prettyState = "On";
                    break;
                default:
                    break;
            }
            //Break out of the case
            break;
        }

        //If the device is a solenoid valve, two states, on and off
        //Any other states should throw and an error
        case "solValve": {
            switch (state) {
                case 0:
                    prettyState = "Off";
                    break;
                case 1:
                    prettyState = "On";
                    break;
                default:
                    break;
            }
            //Break out of the case
            break;
        }

        //If the device is a six-port valve, two states, A and B
        //Any other states should throw and an error
        case "sixValve": {
            switch (state) {
                case 0:
                    prettyState = "A";
                    break;
                case 1:
                    prettyState = "B";
                    break;
                default:
                    break;
            }
            //Break out of the case
            break;
        }
        default:
            //Break
            break;

    }

    //If the prettyState is valid, not -1, return it, else return an error
    if (prettyState != "undefined") {
        //Return the prettyState
        return {
            code: 0,
            msg: "Success",
            pState: prettyState,
        };
    }

    //The state and deviceType do not match, return an error
    return {
        code: 1,
        msg: "The state and deviceType do not match",
        pState: "undefined",
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
    times.sort(sortByProperty("timeStart"));

    //Get a list of all devices used
    var uniqueDevices = getUniqueDevices(timings);

    //Check if failed - code non-zero
    if (uniqueDevices.code) {

        //Alert that an error occurred
        alert("Error getting the list of devices used");

        //Log specific error
        console.log(duration.msg);
    }

    //Create an array to store the html row data
    var htmlRows = [];

    //Loop through the unique devices, and create the initial row html
    for (ij in uniqueDevices.devices) {

        //Attempt to get the device name from the deviceID
        let devName = getDeviceName(uniqueDevices.devices[ij]);

        //Check if failed - code non-zero
        if (devName.code) {

            //Alert that an error occurred
            alert("Error getting device name");

            //Log specific error
            console.log(devName.msg);
        }

        //Initialise the row with the name of the device and the class for the chart
        htmlRows[ij] = '<div class="row"> <h6>' + devName.name + '</h6><div class="chart">';
    }

    //Attempt to get the duration of the routine
    var duration = getDuration(timings);

    //Check if failed - code non-zero
    if (duration.code) {

        //Alert that an error occurred
        alert("Error getting the duration of the routine");

        //Log specific error
        console.log(duration.msg);
    }

    //Loop through the timings array and generate the span blocks
    for (ik in times) {

        //Get the type of the device
        var deviceType = getDeviceType(times[ik].devID);

        //Check if failed - code non-zero
        if (deviceType.code) {

            //Alert that an error occurred
            alert("Error getting the type of the device");

            //Log specific error
            console.log(deviceType.msg);
        }

        //Get the pretty name of the current state
        var pName = getPrettyState(times[ik].state, deviceType.type);

        //Check if failed - code non-zero
        if (pName.code) {

            //Alert that an error occurred
            alert("Error getting the pretty name of the current state");

            //Log specific error
            console.log(pName.msg);
        }

        //Calculate the width of the block in the figure, in %
        //Calculate the duration of the block
        var stepDur = times[ik].timeStop - times[ik].timeStart;

        //Convert this to the width of the block by multiplying by 100/duration
        var blockWidth = stepDur * (100 / duration.dur);

        //Create visualisation HTML span
        var rowHTML = '<span style="width:' + blockWidth + '%;"class="block state' + pName.pState + '" title="' + times[ik].timeStart + '-' + times[ik].timeStop + ' seconds"><span class="dspState">' + pName.pState + '</span></span>';

        //If the deviceID can be found in the timings array, append the next span block to it
        if (uniqueDevices.devices.indexOf(parseInt(times[ik].devID)) != -1) {

            //Get the index of the deviceID row specified in the timings block
            let index = uniqueDevices.devices.indexOf(parseInt(times[ik].devID));

            //Append the new block to the existing HTML
            htmlRows[index] += rowHTML;
        }
    }

    //Loop through the unique devices, and append the closing div tags
    for (ji in uniqueDevices.devices) {

        //Append the closing div tags to each of the rows
        htmlRows[ji] += '</div></div>';
    }

    //Join the rows together into 1 string to return
    visHtml = htmlRows.join("");

    //Return the duration of the routine
    return {
        code: 0,
        msg: "Success",
        html: visHtml,
    };

}