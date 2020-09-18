//Declare the getTypes function - This will get the types.json file when running in production, or some static text when running in development
//No parameters need to be passed
//Returns an array with a jsonString code and message which can be accessed in return .code and .msg .json
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The types.json file could not be loaded
function getTypes() {
    //Get the types.json file, then return the contents as a string

    let res = "undefined";

    // Set the global configs to synchronous 
    $.ajaxSetup({
        async: false
    });

    //Get the devices.json file from the server
    $.getJSON("/gettypes", function (response) {
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
        msg: "The types.json file could not be loaded",
        json: "undefined",
    };
}
