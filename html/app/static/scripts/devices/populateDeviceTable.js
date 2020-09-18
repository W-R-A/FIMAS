//Declare the populate device table function - This will populate a specified table based on the devices.json file
//Need to pass the table element ID, as a string
//Returns an array with a code and message which can be accessed in return .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The given ID does not exist
//2 - There is more than one element with the given ID in the document
//3 - The given ID does not correspond to a table type 
//4 - There was an issue loading the types file
//5 - There was an issue loading the devices file
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
    var typesResponse = $.parseJSON(types.json);    

    //Get the device info 
    let devices = getDevices();

    //Check if failed - code non-zero
    if (devices.code) {

        //An error has occurred loading the devices file
        return {
            code: 5,
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
        $.each(typesResponse, function (j, itemTypes) {
            trHTML = trHTML.replace(itemTypes.devType, itemTypes.friendlyName);
        });
    });

    //Append the html to the table
    $('#' + tableID).append(trHTML);

    //Return success
    return {
        code: 0,
        msg: "Success!",
    };
}
