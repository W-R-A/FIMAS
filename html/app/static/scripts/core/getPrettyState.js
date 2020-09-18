//Declare the get pretty state function - This will return a string containing the pretty state given a state and device type
//Need to pass the state and device type
//Returns an array with a code, message and prettyState which can be accessed in return .pState, .code and .msg
//Code 0 on success, non-zero on failure
//Code, msg
//0 - Success
//1 - The state and deviceType do not match
function getPrettyState(state, deviceType) {
    //Lookup state and device type and return as pretty state as a string
    //If type and state do not match, throw an error

    //Convert state to an integer
    state = parseInt(state);

    //Declare a variable to hold the pretty state of the device
    var prettyState = "undefined";

    //Switch based on the device type
    switch (deviceType) {

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

        //If the device is a switch valve, ten states, 1 through 9
        case "sixValve": {
            //Simply return the mumerical state
            prettyState = state;
            //Break out of the case
            break;
        }

        //If no state can be found, break
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
