//Add device button clicked
function addDevice() {

    //Fields needed
    //Name
    //Type
    //Pin 1
    //Pin 2

    //Display the form
    displayForm()

    //Add a label for the name field
    $('#devConfigContainer').append('<label for="devName"><p>Device Name</label></p>');

    //Add a device name input with the type of operation required
    $('#devConfigContainer').append('<input type="text" name="devName" placeholder="Enter a name for the device"> <br><br>');


    //Add a label for the name field
    $('#devConfigContainer').append('<label for="devType"><p>Device Type</label></p>');

    //Add a device type input with the type of operation required
    $('#devConfigContainer').append('<select id="type_dropdown" name="devType" title="Select a type of device"></select> <br><br>');


    //Populate the device dropdown with the devices on the system
    let attTyp = populateTypes("type_dropdown");

    //Check if failed - code non-zero
    if (attTyp.code) {
        //Alert that an error occurred
        alert("Error populating types");

        //Log specific error
        console.log(attTyp.msg);
    }


    //Add a label for the Primary Interface field
    $('#devConfigContainer').append('<label for="priInter"><p>Primary Interface</label></p>');

    //Add an input dropdown for the primary interface
    $('#devConfigContainer').append('<select id="primary_dropdown" name="priInter" title="Select the primary interface"></select> <br><br>');

    //Populate the device dropdown with the devices on the system
    let attInt = populatePins("primary_dropdown");

    //Check if failed - code non-zero
    if (attInt.code) {
        //Alert that an error occurred
        alert("Error populating types");

        //Log specific error
        console.log(attInt.msg);
    }

    //Add a label for the Secondary Interface field
    $('#devConfigContainer').append('<label for="secInter"><p>Secondary Interface</label></p>');

    //Add an input dropdown for the secondary interface
    $('#devConfigContainer').append('<select id="secondary_dropdown" name="secInter" title="Select the secondary interface"></select> <br><br>');

    //Populate the device dropdown with the devices on the system
    let attInt1 = populatePins("secondary_dropdown");

    //Check if failed - code non-zero
    if (attInt1.code) {
        //Alert that an error occurred
        alert("Error populating types");

        //Log specific error
        console.log(attInt1.msg);
    }

    //Add a hidden input with the type of operation required
    $('#devConfigContainer').append('<input type="hidden" name="opType" value="add">');

    //Add the submit button with the appropriate text
    $('#devConfigContainer').append('<button type="button" onclick="hideForm()">Cancel</button> ');

    //Add the submit button with the appropriate text
    $('#devConfigContainer').append('<button type="submit">Add Device</button>');
}