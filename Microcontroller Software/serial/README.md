# Serial Command Guide #

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
        <td>Device Type,<br> Device ID,<br> Primary Interface,<br>Secondary Interface (optional)</td>
        <td>OK<br>FAILURE</td>
        <td>CONFIGDEVICE PERPUMP,1000,1<br><br>CONFIGDEVICE SWITCHVALVE,1001,2,4</td>
    </tr>
    <tr>
        <td>CONFIGROUTINESTEP</td>
        <td>Configures a routine step for use with the system</td>
        <td>Routine ID,<br> Device ID,<br> Start Time,<br> Stop Time,<br>State</td>
        <td>OK<br>FAILURE</td>
        <td>CONFIGROUTINESTEP 2060,1001,0,4,1<br><br>CONFIGROUTINESTEP 2060,1000,7,9,0</td>
    </tr>
    <tr>
        <td>VIEWDEVICES</td>
        <td>View all currently configured devices</td>
        <td>None</td>
        <td>Printout of all of the devices on the system</td>
        <td>VIEWDEVICES</td>
    </tr>
    <tr>
        <td>VIEWROUTINE</td>
        <td>View the current routine</td>
        <td>None</td>
        <td>Printout of all of the routine information on the system</td>
        <td>VIEWROUTINE</td>
    </tr>
    <tr>
        <td>RUN</td>
        <td>Run the loaded routine</td>
        <td>None</td>
        <td>OK</td>
        <td>RUN</td>
    </tr>
    <tr>
        <td>STATUS</td>
        <td>Get the status of the controller</td>
        <td>None</td>
        <td>IDLE<br>RUNNING<br>ERROR<br>ESTOP</td>
        <td>STATUS</td>
    </tr>
    <tr>
        <td>ESTOP</td>
        <td>Emergency Stop</td>
        <td>None</td>
        <td>OK </td>
        <td>ESTOP</td>
    </tr>
    <tr>
        <td>TESTDEVICES</td>
        <td>Test all of the configured devices</td>
        <td>None</td>
        <td>OK<br>PASS<br>FAIL</td>
        <td>TESTDEVICES</td>
    </tr>
    <tr>
        <td>TESTDEVICE</td>
        <td>Tests a device on the system</td>
        <td>Device ID</td>
        <td>OK<br>PASS<br>FAIL</td>
        <td>TESTDEVICE 1001</td>
    </tr>
</table>