function addDevice(formObject) {

    //Get the form data, validity checked by HTML5 required attribute and range restrictions
    let newDevice = [
        { devName: formObject.devName.value, devType: formObject.devType.value, devPin1: formObject.priInter.value, devPin2: formObject.secInter.value }
    ];

    //Start a database transaction
    let transaction = db.transaction(["devices"], "readwrite");

    //Start an object store request
    let objectStore = transaction.objectStore("devices");

    //Add the device to the database
    let objectStoreRequest = objectStore.add(newDevice[0]);

    //Update board configuration
    updateDeviceConfig();
}

function deleteDevice(formObject) {

    //Get the dropdown data which contains the ID of the device to delete
    let delDevice = formObject.devID.value

    //Start a database transaction
    let transaction = db.transaction(["devices"], "readwrite");

    //Start an object store request
    let objectStore = transaction.objectStore("devices");

    //Add the device to the database
    let objectStoreRequest = objectStore.delete(delDevice);

    //Update board configuration
    updateDeviceConfig();
}

function updateDeviceConfig() {

    //Declare a local variable to hold the JSON as a string
    let devicesJSON = [];

    //Open our object store 
    let objectStore = db.transaction('devices').objectStore('devices');

    //Get a cursor list of all the different data items in the IDB to iterate through
    objectStore.openCursor().onsuccess = function (event) {
        //Get the cursor
        let cursor = event.target.result;

        //If there is still another device, keep running
        if (cursor) {

            //Build the json for the device
            let device = { devID: cursor.value.devID, devName: cursor.value.devName, devType: cursor.value.devType, devPin1: cursor.value.devPin1, devPin2: cursor.value.devPin2 };

            //Push the devices onto the array
            devicesJSON.push(device);

            //Continue to the next item in the cursor
            cursor.continue();

            //If all the devices have been read, send the updated config to the MCU
        } else {
            //Define the URL to hit
            var reqURL = '/updatedevices/' + JSON.stringify(devicesJSON);

            //Send the AJAX request to the defined URL
            $.ajax({
                type: "GET",
                url: reqURL,
                //On success, refresh the page
                success: function (result) {
                    window.reload();
                },
                //On failure, alert the user
                error: function (result) {
                    alert('There was an issue adding the device');
                }
            });
        }
    }

}