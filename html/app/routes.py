from flask import render_template, url_for
from app import app
from app.forms import ADDDEVICEFORM


@app.route('/')
@app.route('/index')
def index():
    return render_template('index.html', title='Home')


@app.route('/devices')
def devices():
    return render_template('devices.html', title='Device Configuration')


@app.route('/routines')
def routines():
    return render_template('index.html', title='Routines Configuration')


@app.route('/estop')
def estop():
    return render_template('estop.html', title='Emergency Stop')


@app.route('/adddevice')
def adddevice():
    form = ADDDEVICEFORM()
    return render_template('adddevice.html', title='Add a device', form=form)
