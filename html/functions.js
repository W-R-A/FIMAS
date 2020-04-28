//Functions.js
//Used within FIMAS to hold functions such as the population of drop-down boxes, and fetching JSON data

//Test JSON data for devices and routines
var tstDevices = "[{\"devID\":\"1000\",\"devName\":\"Sample Pump\",\"devType\":\"perPump\",\"devPin1\":\"1\",\"devPin2\":\"-1\"},{\"devID\":\"1001\",\"devName\":\"Control Valve\",\"devType\":\"solValve\",\"devPin1\":\"2\",\"devPin2\":\"-1\"},{\"devID\":\"1002\",\"devName\":\"6-Port Valve\",\"devType\":\"sixValve\",\"devPin1\":\"3\",\"devPin2\":\"4\"}]";

var tstRoutines = '[{"routineID":"1004","name":"AlCl","timings":[{"devID":"1000","timeStart":"0","timeStop":"4","state":"0"},{"devID":"1000","timeStart":"4","timeStop":"17","state":"1"},{"devID":"1000","timeStart":"9","timeStop":"15","state":"0"},{"devID":"1001","timeStart":"0","timeStop":"4","state":"1"},{"devID":"1001","timeStart":"4","timeStop":"8","state":"0"},{"devID":"1001","timeStart":"8","timeStop":"15","state":"0"},{"devID":"1002","timeStart":"0","timeStop":"3","state":"1"},{"devID":"1002","timeStart":"3","timeStop":"7","state":"0"},{"devID":"1002","timeStart":"7","timeStop":"15","state":"1"}]},{"routineID":"1003","name":"CuSO4","timings":[{"devID":"1000","timeStart":"0","timeStop":"4","state":"1"},{"devID":"1000","timeStart":"4","timeStop":"9","state":"0"},{"devID":"1000","timeStart":"9","timeStop":"15","state":"1"},{"devID":"1001","timeStart":"0","timeStop":"6","state":"0"},{"devID":"1001","timeStart":"6","timeStop":"8","state":"1"},{"devID":"1001","timeStart":"8","timeStop":"15","state":"0"},{"devID":"1002","timeStart":"0","timeStop":"3","state":"1"},{"devID":"1002","timeStart":"3","timeStop":"7","state":"0"},{"devID":"1002","timeStart":"7","timeStop":"15","state":"1"}]}]';






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

    //Loop through the response and fill in the table and dropdown
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