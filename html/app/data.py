from flask import render_template
from app import app


@app.route('/getdevices')
def getDevices():
    # ToDo - Database lookup of current devices

    devices = '[{"devID":"1000","devName":"Sample Pump","devType":"perPump","devPin1":"2","devPin2":"3"},{"devID":"1001","devName":"Distribution Valve","devType":"swichValve","devPin1":"5","devPin2":"6"},{"devID":"1002","devName":"6-Port Valve","devType":"sixValve","devPin1":"9","devPin2":"10"}]'

    return devices
