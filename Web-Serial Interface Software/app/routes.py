from flask import render_template, url_for, flash, redirect
from app import app, db
from app.forms import AddDeviceForm, DeleteDeviceForm, AddRoutineForm, DeleteRoutineForm, AddTimingForm, DeleteTimingForm
from app.models import Routine, Device, Timing


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
        timings = Timing.query.filter_by(device_id=form.devID.data).all()
        for i in range(0, len(timings)):
            db.session.delete(timings[i])
        db.session.delete(dev)
        db.session.commit()
        flash('Device deleted!')
        return redirect(url_for('devices'))
    return render_template('managedevice.html', deviceOperation = "Delete", title='Delete a device', form=form)

@app.route('/addroutine', methods=['GET', 'POST'])
def addroutine():
    form = AddRoutineForm()
    if form.validate_on_submit():
        rou = Routine(name = form.name.data)
        db.session.add(rou)
        db.session.commit()
        flash('Routine added!')
        return redirect(url_for('routines'))
    return render_template('manageroutine.html', routineOperation = "Add", title='Add a routine', form=form)

@app.route('/deleteroutine', methods=['GET', 'POST'])
def deleteroutine():
    form = DeleteRoutineForm()
    form.populateRoutines()
    if form.validate_on_submit():
        rou = Routine.query.get(form.rouID.data)
        timings = Timing.query.filter_by(routine_id=form.rouID.data).all()
        for i in range(0, len(timings)):
            db.session.delete(timings[i])
        db.session.delete(rou)
        db.session.commit()
        flash('Routine deleted!')
        return redirect(url_for('routines'))
    return render_template('manageroutine.html', routineOperation = "Delete", title='Delete a routine', form=form)


@app.route('/addtiming', methods=['GET', 'POST'])
def addtiming():
    form = AddTimingForm()
    form.populateRoutines()
    form.populateDevices()
    if form.validate_on_submit():
        time = Timing(device_id = form.devID.data, routine_id = form.rouID.data, startTime = int(form.timeStart.data), stopTime = int(form.timeStop.data), state = int(form.state.data))
        db.session.add(time)
        db.session.commit()
        flash('Timing created!')
        return redirect(url_for('routines'))
    return render_template('manageroutine.html', routineOperation = "Edit", title='Edit a routine', form=form)


@app.route('/deletetiming', methods=['GET', 'POST'])
def deletetiming():
    form = DeleteTimingForm()
    form.populateTimings()
    if form.validate_on_submit():
        time = Timing.query.get(form.timeID.data)
        db.session.delete(time)
        db.session.commit()
        flash('Timing deleted!')
        return redirect(url_for('routines'))
    return render_template('manageroutine.html', routineOperation = "Edit", title='Edit a routine', form=form)