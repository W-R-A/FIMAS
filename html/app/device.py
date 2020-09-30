from flask import render_template, url_for, flash, redirect, jsonify
from app import app, db
from app.models import Routine, Device, Timing

#serial
import serial
from time import sleep

# Create a serial object with the following properties
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

"""
Define a function to send a command over USART to the MCU, blocking until a valid response is received back 
displayResult determines if the result of the command will be flashed on the screen
Valid responses end in OK or FAIL
Returns a string containing the response or error if no valid response is received
"""


def sendCommand(cmd, displayResult):

    # Add a carriage return to mark the end of the command
    cmd = cmd + "\r"

    # Encode it in UTF-8 so that it can be send over serial
    encCmd = bytes(cmd, 'utf-8')

    # Send the command over serial
    ser.write(encCmd)

    # Block until a response is received
    while (ser.inWaiting() == 0):
        sleep(0.01)

    # Create a variable to hold the response
    data = ""

    # While there is data to be read, read it
    while(ser.inWaiting() > 0):
        data = data + str(ser.read(), 'utf-8')

    # If the command was successful, return the data
    if "OK" in data:
        if (displayResult):
            flash(data)
        return data
    elif "FAIL" in data:
        if (displayResult):
            flash(data)
        return data
    # Else, return a string instead of invalid data
    else:
        if (displayResult):
            flash("An error occurred")
        return "Invalid response received"


@app.route('/testdevices')
def testdevices():
    configDevices()
    sendCommand("TESTDEVICES", True)
    flash("Device Test Successful")
    return redirect(url_for('devices'))

@app.route('/testdevice/<int:deviceID>')
def testdevice(deviceID):
    configDevices()
    sendCommand("TESTDEVICE " + str(deviceID), True)
    flash("Device Test Successful")
    return redirect(url_for('devices'))


def configDevices():

    sendCommand("RESET", False)

    # Database lookup of current devices

    devices = Device.query.all()

    #configuration commands for devices
    for i in range(0, len(devices)):
        if (int(devices[i].interface2) != -1):
            sendCommand("CONFIGDEVICE " + str((devices[i].devType).upper()) + ',' + str(devices[i].id) + ',' + str(devices[i].interface1) + ',' + str(devices[i].interface2), False)
        else:
            sendCommand("CONFIGDEVICE " + str((devices[i].devType).upper()) + ',' + str(devices[i].id) + ',' + str(devices[i].interface1), False)

@app.route('/testroutine/<int:routineID>')
def configRoutines(routineID):
    #Database query of all timings with the requested routine ID

    timings = Timing.query.filter_by(routine_id=routineID).all()

    for i in range(0, len(timings)):
        #configroutinestep routineID,devID,timestart,timeStop,state
        sendCommand("CONFIGROUTINESTEP " + str(timings[i].routine_id) + ',' + str(timings[i].device_id) + ',' + str(timings[i].startTime) + ',' + str(timings[i].stopTime) + ',' + str(timings[i].state), False)
    
    return redirect(url_for('routines'))


@app.route('/estop')
def estop():
    sendCommand("ESTOP", True)
    return render_template('estop.html', title='Emergency Stop')