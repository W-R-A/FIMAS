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



//Declare the genVisHTML function - This will return the a string containing the rows html to append to the appropriate figure 
//Need to pass the timings array in as a string
//Returns an array with a code, message and the html which can be accessed in return .html, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//0 - There is no timing data available
//2 - There was a problem parsing the JSON string
function genVisHTML(timings) {

    //Parse timings JSON
    //Sort the timings array by start time
    //Create a unique list of the deviceIDs used in the routine buy using getUniqueDevices()
    //Create an array to hold the unique deviceID timing span blocks
    //Get the names of the devices using getDeviceName()
    //Loop through the timings array, generating the span blocks and appending to the specified deviceID row
    //Append closing div tags to each device row
    //Concatenate the html together and return as .html

    if (timings.toString() == "[]") {
        //If there is no timings data, return
        return {
            code: 0,
            msg: "There is no timing data",
            devices: [],
        };
    }

    //Try to parse the JSON, return an error is it cannot be parsed
    try {
        times = JSON.parse(timings);
    } catch (e) {
        //If there was an error parsing the JSON, return an error
        return {
            code: 2,
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

    //Get the device info 
    let devices = getDevices();

    //Check if failed - code non-zero
    if (devices.code) {

        //An error has occurred loading the devices file
        return {
            code: 2,
            msg: "There was an issue loading the devices file",
        };
    }

    //Loop through the unique devices, and create the initial row html
    for (ij in uniqueDevices.devices) {

        //Attempt to get the device name from the deviceID
        let devName = getDeviceName(uniqueDevices.devices[ij], devices);

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
        var deviceType = getDeviceType(times[ik].devID, devices);

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