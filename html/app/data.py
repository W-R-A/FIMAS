from flask import render_template, url_for, flash, redirect, jsonify
from app import app, db
from app.models import Routine, Device, Timing


@app.route('/getdevices')
def getdevices():
    # Database lookup of current devices

    devices = Device.query.all()

    dev = []

    for i in range(0, len(devices)):
        dev.append({'devID':devices[i].id,'devName':devices[i].name,'devType':devices[i].devType,'devPin1':devices[i].interface1,'devPin2':devices[i].interface2,'routineID':devices[i].routine_id})
    
    return jsonify(dev)


@app.route('/getroutines')
def getroutines():
    #Database lookup of current routines

    routines = Routine.query.all()
    
    rou = []

    for i in range(0, len(routines)):
        rou.append({'routineID':routines[i].id,'name':routines[i].name})

    return jsonify(rou)

#get timings - get the current timings for a routine, by pasing the routine ID
@app.route('/gettimings/<int:routineID>')
def gettimings(routineID):
    #Database query of all timings with the requested routine ID

    timings = Timing.query.filter_by(routine_id=routineID).all()

    time = []

    for i in range(0, len(timings)):
        time.append({"devID":timings[i].device_id,"timeStart":timings[i].startTime,"timeStop":timings[i].stopTime,"state":timings[i].state})

    return jsonify(time)




@app.route('/gettypes')
def gettypes():
    # ToDo - Database lookup of current device types

    deviceTypes = [{"devType": "perPump", "friendlyName": "Peristaltic Pump"}, {"devType": "solValve", "friendlyName": "Solenoid Valve"}, {"devType": "sixValve", "friendlyName": "6-Port Valve"}, {"devType": "switchValve", "friendlyName": "Switching Valve"}]

    return jsonify(deviceTypes)
