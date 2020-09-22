//Get user input values
//No parameters need to be passed
//Return key values pairs of the user input data
function getInputs() {

    //Get the device ID
    var devID = $('select[id="devices_dropdown"] option:selected').attr('id');

    //Get the time from the input box
    var timeStart = $("#timeStart").val();
    var timeStop = $("#timeStop").val();

    //Get the device state
    var devState = $('select[id="state"] option:selected').attr('class');

    //Return values
    return {
        devID: devID,
        timeStart: timeStart,
        timeStop: timeStop,
        devState: devState,
    };
}

function checkSingleSanity(newValue, existingValue) {
    //Is the ID the same
    if (values.devID == existingValue.devID) {

        //Are the start time within the existing value 
        if ((values.timeStart > existingValue.timeStart && values.timeStart < existingValue.timeStop)) {
            //Are the stop time within the existing value 
            if ((values.timeStop > existingValue.timeStart && values.timeStop < existingValue.timeStop)) {
                //Timings are within previous range, alert user
                alert("Timings overlap previous inputs, aborting");
                return 0;
            }
            else {
                //No overlap, safe to proceed,
                return 1;
            }

            //Is the state the same
            if (values.devState = existingValue.devState) {
                //If yes, are the start and stop times the same or do they need to be changed

            }
            //If no check timings
            else {


            }
        }
        //Different device, no worries
        else {

        }
    }
    else {
        //Different ID, safe to proceed
        return 1;
    }
}

//Check if the inputs are sane - not conflicting with other inputs
function checkInputsSanity(values) {
    //Loop through all of the previous timing data and raise an error if the new data would conflict with the existing data
    //ie if the states are different for the same time - gaps of undefined time 

    //Conflict detection
    //Start
    //Check if ID is the same
    //Check if the start time is within the previous range
    //Check if the stop time is within the previous range
    //Check if the state is the same
    //if so - conflict - need to resolve

    var timesStart = [];
    var timesStop = [];

    for (let i = 0; i < routines.length; i++) {

        timesStart.push(routines[i].timeStart);
        timesStop.push(routines[i].timeStop);
    }

    //Math.max.apply(null, timesStop)

    console.log(timesStart);
    console.log(timesStop);

    console.log(timesStart.sort());
    console.log(timesStop.sort());

    console.log("\n");



    for (let i = 0; i < routines.length; i++) {
        if (!checkSingleSanity(values, routines[i])) {
            return 0;
        }
    }
    return 1;
}

//Check if the inputs are valid
function checkInputs(values) {

    //Check if a valid device selected
    if (typeof values.devID == "undefined") {
        //Tell the user to select a valid device
        alert("Please select a device");
        //Return and do not execute the rest of the function as there is an invalid input
        return 0;
    }

    //Check the starting time value - should only be a integer between 0 and 1000
    if ((!values.timeStart) || (values.timeStart < 0) || (values.timeStart > 1000)) {
        //Alert the user to select a valid time
        alert("Please enter a starting time between 0 and 1000 seconds");

        //Return and do not execute the rest of the function as there is an invalid input
        return 0;
    }

    //Check the stopping time value - should only be a integer between 0 and 1000
    if ((!values.timeStop) || (values.timeStop < 0) || (values.timeStop > 1000)) {
        //Alert the user to select a valid time
        alert("Please enter a stopping time between 0 and 1000 seconds");

        //Return and do not execute the rest of the function as there is an invalid input
        return 0;
    }

    //Check the start time is before the stop time
    if (values.timeStart > values.timeStop - 1) {
        //Alert the user to select a valid time
        alert("Please ensure that the starting time is less than the stopping time");

        //Return and do not execute the rest of the function as there is an invalid input
        return 0;
    }

    if (typeof values.devState == "undefined") {
        //Tell the user to select a valid device
        alert("Please select a state");
        //Return and do not execute the rest of the function as there is an invalid input
        return 0;
    }

    //Check inputs sanity
    if (checkInputsSanity(values)) {
        return 0;
    }

    return 1;

}

//Generate timing JSON data from user input
$(document).on("click", "button.genTiming", function (event) {

    //Get the value of the user inputs
    values = getInputs();

    //Check that the user input is valid
    if (checkInputs(values)) {

        //Create the JSON object
        var obj = { devID: values.devID, timeStart: values.timeStart, timeStop: values.timeStop, state: values.devState };

        //Convert the JSON object to a string
        //var myJSON = JSON.stringify(obj);

        routines.push(obj);

        //Append this to the page
        //$('<p>' + myJSON + '</p>').appendTo('#timings');

        console.log(JSON.stringify(routines));
    }
});

//Bind the device selection to the following handler - to adjust the state drop down
$(document).on("change", "#devID", function (event) {
    deviceStates()
});


function deviceStates() {
    var devID = $('select[id="devID"] option:selected').attr('value');

    devClass = getDeviceTypeRequest(devID).type;

    //Debugging, display the ID to be requested
    //alert($('select[id="devices_dropdown"] option:selected').attr('class'));

    $('#state').empty();

    switch (devClass) {
        case "perPump":
            $('#state').append('<option selected="true" disabled>Select State</option>');
            $('#state').append('<option class="1">On</option>');
            $('#state').append('<option class="0">Off</option>');
            $('#state').prop('selectedIndex', 0);
            break;

        case "solValve":
            $('#state').append('<option selected="true" disabled>Select State</option>');
            $('#state').append('<option class="1">On</option>');
            $('#state').append('<option class="0">Off</option>');
            $('#state').prop('selectedIndex', 0);
            break;

        case "sixValve":
            $('#state').append('<option selected="true" disabled>Select State</option>');
            $('#state').append('<option class="0">Position A</option>');
            $('#state').append('<option class="1">Position B</option>');
            $('#state').prop('selectedIndex', 0);
            break;

        default:
        // code block
    }
}

//Bind the routine selection to the following handler generate the visualisation
$(document).on("change", "#routines_dropdown", function (event) {

    //Get the ID of the selected routine
    var selRoutineID = $('select[id="routines_dropdown"] option:selected').attr('class');

    //Clear the previous visualisation bars
    $("#visualisation").empty();

    //Get the routines on the system in a JSON format
    //Get the device info 
    let routines = getRoutines();

    //Check if failed - code non-zero
    if (routines.code) {

        //Alert that an error occurred
        alert("There was an issue loading the routines on the system");

        //Log specific error
        console.log(routines.msg);

        //Break out of the function
        return false;
    }

    //Parse the JSON
    response = $.parseJSON(routines.json);

    //Loop through all of the routines in the file
    $.each(response, function (i, routines) {

        //If the routineID is the one that needs to be visualised
        if (selRoutineID == routines.routineID) {

            //Get a list of all devices used
            var visualisationHtml = genVisHTML(getTimings(selRoutineID).json);

            //Check if failed - code non-zero
            if (visualisationHtml.code) {

                //Alert that an error occurred
                alert("Error generating the visualisation");

                //Log specific error
                console.log(visualisationHtml.msg);
            }

            //Print out the routine timing data
            $(visualisationHtml.html).appendTo('#visualisation');
        }
    });
});
