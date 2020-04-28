//Functions.js
//Used within FIMAS to hold functions such as the population of drop-down boxes, and fetching JSON data

//Declare the populate routines function - This will populate the routines dropdown based on the routines.json file
//Need to pass the dropdown element ID, preceded by a hash
//Nothing is returned
function populateRoutines(ddID) {

    //Ensure that the dropdown is empty
    $(ddID).empty();

    //Set default option as select device, and make it disabled
    $(ddID).append('<option selected="true" disabled>Select Routine</option>');
    $(ddID).prop('selectedIndex', 0);

    //Define some temporary variables to hold the HTML
    var opHTML = '';

    //Testing the parsing of the json
    var jsonData = "[{\"routineID\":\"1004\",\"name\":\"AlCl\",\"timings\":[{\"devID\":\"1000\",\"timeStart\":\"0\",\"timeStop\":\"4\",\"state\":\"1\"},{\"devID\":\"1000\",\"timeStart\":\"4\",\"timeStop\":\"9\",\"state\":\"0\"},{\"devID\":\"1000\",\"timeStart\":\"9\",\"timeStop\":\"15\",\"state\":\"1\"},{\"devID\":\"1001\",\"timeStart\":\"0\",\"timeStop\":\"6\",\"state\":\"0\"},{\"devID\":\"1001\",\"timeStart\":\"6\",\"timeStop\":\"8\",\"state\":\"1\"},{\"devID\":\"1001\",\"timeStart\":\"8\",\"timeStop\":\"15\",\"state\":\"0\"},{\"devID\":\"1002\",\"timeStart\":\"0\",\"timeStop\":\"3\",\"state\":\"1\"},{\"devID\":\"1002\",\"timeStart\":\"3\",\"timeStop\":\"7\",\"state\":\"0\"},{\"devID\":\"1002\",\"timeStart\":\"7\",\"timeStop\":\"15\",\"state\":\"1\"}]},{\"routineID\":\"1003\",\"name\":\"CuSO4\",\"timings\":[{\"devID\":\"1000\",\"timeStart\":\"0\",\"timeStop\":\"4\",\"state\":\"1\"},{\"devID\":\"1000\",\"timeStart\":\"4\",\"timeStop\":\"9\",\"state\":\"0\"},{\"devID\":\"1000\",\"timeStart\":\"9\",\"timeStop\":\"15\",\"state\":\"1\"},{\"devID\":\"1001\",\"timeStart\":\"0\",\"timeStop\":\"6\",\"state\":\"0\"},{\"devID\":\"1001\",\"timeStart\":\"6\",\"timeStop\":\"8\",\"state\":\"1\"},{\"devID\":\"1001\",\"timeStart\":\"8\",\"timeStop\":\"15\",\"state\":\"0\"},{\"devID\":\"1002\",\"timeStart\":\"0\",\"timeStop\":\"3\",\"state\":\"1\"},{\"devID\":\"1002\",\"timeStart\":\"3\",\"timeStop\":\"7\",\"state\":\"0\"},{\"devID\":\"1002\",\"timeStart\":\"7\",\"timeStop\":\"15\",\"state\":\"1\"}]}]";

    //Testing - use static json
    response = $.parseJSON(jsonData)

    //Get the devices on the system in a JSON format
    //$.getJSON("/routines.json", function (response) {
        //Loop through the response and fill in the table and dropdown
        $.each(response, function (i, item) {
            //Generate the dropdown html
            opHTML += '<option class=' + item.routineID + '>' + item.name + '</option>';
        });

        //Append the html to the dropdown
        $(ddID).append(opHTML);
    //});
}