from flask import render_template, url_for, flash, redirect, jsonify
from app import app, db
from app.models import Routine, Device, Timing

@app.route('/testdevices')
def testdevices():
    configDevices()
    print("TESTDEVICES")
    flash("Device Test Successful")
    return redirect(url_for('devices'))

@app.route('/testdevice/<int:deviceID>')
def testdevice(deviceID):
    configDevices()
    print("TESTDEVICE " + str(deviceID))
    flash("Device Test Successful")
    return redirect(url_for('devices'))


def configDevices():

    # Database lookup of current devices

    devices = Device.query.all()

    #configuration commands for devices
    for i in range(0, len(devices)):
        if (int(devices[i].interface2) != -1):
            print("CONFIGDEVICE " + str((devices[i].devType).upper()) + ',' + str(devices[i].id) + ',' + str(devices[i].interface1) + ',' + str(devices[i].interface2))
        else:
            print("CONFIGDEVICE " + str((devices[i].devType).upper()) + ',' + str(devices[i].id) + ',' + str(devices[i].interface1))

@app.route('/testroutine/<int:routineID>')
def configRoutines(routineID):
    #Database query of all timings with the requested routine ID

    timings = Timing.query.filter_by(routine_id=routineID).all()

    for i in range(0, len(timings)):
        #configroutinestep routineID,devID,timestart,timeStop,state
        print("CONFIGROUTINESTEP " + str(routineID) + ',' + str(timings[i].device_id) + ',' + str(timings[i].startTime) + ',' + str(timings[i].stopTime) + ',' + str(timings[i].state))
    
    return redirect(url_for('routines'))


@app.route('/estop')
def estop():
    print("ESTOP")
    return render_template('estop.html', title='Emergency Stop')