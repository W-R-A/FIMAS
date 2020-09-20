from flask import render_template, url_for, flash, redirect, jsonify
from app import app, db
from app.models import Routine, Device,Timing


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
    # ToDo - Database lookup of current devices

    routines = [{"routineID":"1004","name":"AlCl","timings":[{"devID":"1000","timeStart":"0","timeStop":"4","state":"0"},{"devID":"1000","timeStart":"4","timeStop":"9","state":"1"},{"devID":"1000","timeStart":"9","timeStop":"15","state":"0"},{"devID":"1000","timeStart":"15","timeStop":"24","state":"1"},{"devID":"1000","timeStart":"24","timeStop":"56","state":"0"},{"devID":"1000","timeStart":"56","timeStop":"60","state":"1"},{"devID":"1001","timeStart":"0","timeStop":"4","state":"1"},{"devID":"1001","timeStart":"4","timeStop":"8","state":"0"},{"devID":"1001","timeStart":"8","timeStop":"15","state":"1"},{"devID":"1001","timeStart":"15","timeStop":"29","state":"0"},{"devID":"1001","timeStart":"29","timeStop":"47","state":"1"},{"devID":"1001","timeStart":"47","timeStop":"60","state":"0"},{"devID":"1002","timeStart":"0","timeStop":"3","state":"1"},{"devID":"1002","timeStart":"3","timeStop":"7","state":"0"},{"devID":"1002","timeStart":"7","timeStop":"15","state":"1"},{"devID":"1002","timeStart":"15","timeStop":"28","state":"0"},{"devID":"1002","timeStart":"28","timeStop":"40","state":"1"},{"devID":"1002","timeStart":"40","timeStop":"60","state":"0"}]},{"routineID":"1003","name":"CuSO4","timings":[{"devID":"1000","timeStart":"0","timeStop":"4","state":"1"},{"devID":"1000","timeStart":"4","timeStop":"9","state":"0"},{"devID":"1000","timeStart":"9","timeStop":"15","state":"1"},{"devID":"1001","timeStart":"0","timeStop":"6","state":"0"},{"devID":"1001","timeStart":"6","timeStop":"8","state":"1"},{"devID":"1001","timeStart":"8","timeStop":"15","state":"0"},{"devID":"1002","timeStart":"0","timeStop":"3","state":"1"},{"devID":"1002","timeStart":"3","timeStop":"7","state":"0"},{"devID":"1002","timeStart":"7","timeStop":"15","state":"1"}]}]

    return jsonify(routines)


@app.route('/gettypes')
def gettypes():
    # ToDo - Database lookup of current device types

    deviceTypes = [{"devType": "perPump", "friendlyName": "Peristaltic Pump"}, {"devType": "solValve", "friendlyName": "Solenoid Valve"}, {"devType": "sixValve", "friendlyName": "6-Port Valve"}, {"devType": "switchValve", "friendlyName": "Switching Valve"}]

    return jsonify(deviceTypes)
