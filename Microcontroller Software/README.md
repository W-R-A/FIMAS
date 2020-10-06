## Microcontroller ##
### Overview ###
Any microcontroller that can run the full version of mbed os can be used with the project, although it has only been tested with the STM32 F429ZI - 144 Nucleo Board. The board recieves commands through the serial interface and interfaces with lab devices through relays or other interfaces. 

### Device Classes ###
The object-orientated nature of C++ has been used to create a base class for all of the devices that are to be controlled. Each device has its own class which inherites from the base class. The device-specific classes implement the specific control signals and monitoring required to operate the device, while all device classes  have a consistant interface allowing for simple control from the rest of the system. 

### Serial Interface ###


### Real-time Routines ###

### Thread Safe Data Sharing ###


### Serial Command Guide ###

<table>
    <tr>
        <th>Command</th>
        <th>Action</th>
        <th>Arguments</th>
        <th>Response</th>
        <th>Example</th>
    </tr>
    <tr>
        <td>CLEARDEVICES</td>
        <td>Clear all device configuration</td>
        <td>None</td>
        <td>OK<br>FAILURE</td>
        <td>CLEARDEVICES</td>
    </tr>
    <tr>
        <td>CLEARROUTINE</td>
        <td>Clear all routine configuration data</td>
        <td>None</td>
        <td>OK<br>FAILURE</td>
        <td>CLEARROUTINE</td>
    </tr>
    <tr>
        <td>CONFIGDEVICE</td>
        <td>Configures a device for use with the system</td>
        <td>Parameters delimited by a comma</td>
        <td>OK<br>FAILURE</td>
        <td>Add an example</td>
    </tr>
    <tr>
        <td>CONFIGROUTINESTEP</td>
        <td>Configures a routine step for use with the system</td>
        <td>CSV string of routine step info</td>
        <td>OK<br>FAILURE</td>
        <td>Add an example</td>
    </tr>
    <tr>
        <td>VIEWDEVICES</td>
        <td>View all currently configured devices</td>
        <td>None</td>
        <td>Prints all the devices configured with the system</td>
        <td>Add an example</td>
    </tr>
    <tr>
        <td>VIEWROUTINE</td>
        <td>View the current routine</td>
        <td>None</td>
        <td>Prints the currently loaded routine</td>
        <td>Add an example</td>
    </tr>
    <tr>
        <td>RUN</td>
        <td>Run the loaded routine</td>
        <td>None</td>
        <td>OK</td>
        <td>Add an example</td>
    </tr>
    <tr>
        <td>STATUS</td>
        <td>Get the status of the controller</td>
        <td>None</td>
        <td>IDLE<br>RUNNING<br>ERROR<br>ESTOP</td>
        <td>Add an example</td>
    </tr>
    <tr>
        <td>ESTOP</td>
        <td>Emergency Stop</td>
        <td>None</td>
        <td>OK </td>
        <td>Add an example</td>
    </tr>
    <tr>
        <td>TESTDEVICES</td>
        <td>Test all of the configured devices</td>
        <td>None</td>
        <td>OK  FAILURE</td>
        <td>Add an example</td>
    </tr>
    <tr>
        <td>TESTDEVICE</td>
        <td>Tests the device identified by the passed id</td>
        <td>Device id</td>
        <td>OK<br>FAILURE</td>
        <td>Add an example</td>
    </tr>
</table>