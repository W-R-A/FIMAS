//Delete device button clicked
function deleteDevice() {

    //Display the form
    displayForm()

    //Add a dropdown to select the device to delete
    $('#devConfigContainer').append('<select id="devices_dropdown" name="device" title="Select a device"></select><br><br> ');

    //Populate the device dropdown with the devices on the system
    let attDev = populateDevices("devices_dropdown");

    //Check if failed - code non-zero
    if (attDev.code) {
        //Alert that an error occurred
        alert("Error populating devices");

        //Log specific error
        console.log(attDev.msg);
    }

    //Add a hidden input with the type of operation required
    $('#devConfigContainer').append('<input type="hidden" name="opType" value="delete">');

    //Add the submit button with the appropriate text
    $('#devConfigContainer').append('<button type="button" onclick="hideForm()">Cancel</button> ');

    //Add the submit button with the appropriate text
    $('#devConfigContainer').append('<button type="submit">Delete Device</button>');
}