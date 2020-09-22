from flask import render_template, url_for, flash, redirect
from app import app, db
from app.forms import AddDeviceForm, DeleteDeviceForm
from app.models import Routine, Device,Timing


@app.route('/')
@app.route('/index')
def index():
    return render_template('index.html', title='Home')


@app.route('/devices')
def devices():
    return render_template('devices.html', title='Device Configuration')


@app.route('/routines')
def routines():
    return render_template('routines.html', title='Routines Configuration')


@app.route('/estop')
def estop():
    return render_template('estop.html', title='Emergency Stop')


@app.route('/adddevice', methods=['GET', 'POST'])
def adddevice():
    form = AddDeviceForm()
    if form.validate_on_submit():
        dev = Device(name = form.devName.data, devType = form.devType.data, interface1 = form.devPin1.data, interface2 = form.devPin2.data)
        db.session.add(dev)
        db.session.commit()
        flash('Device added!')
        return redirect(url_for('devices'))
    return render_template('managedevice.html', deviceOperation = "Add", title='Add a device', form=form)


@app.route('/deletedevice', methods=['GET', 'POST'])
def deletedevice():
    form = DeleteDeviceForm()
    form.populateDevices()
    if form.validate_on_submit():
        dev = Device.query.get(form.devID.data)
        db.session.delete(dev)
        db.session.commit()
        flash('Device deleted!')
        return redirect(url_for('devices'))
    return render_template('managedevice.html', deviceOperation = "Delete", title='Delete a device', form=form)