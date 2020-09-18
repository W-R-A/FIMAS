from flask import render_template, url_for, flash, redirect
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


@app.route('/adddevice', methods=['GET', 'POST'])
def adddevice():
    form = ADDDEVICEFORM()
    if form.validate_on_submit():
        flash('Device added!')
        return redirect('/devices')
    return render_template('adddevice.html', title='Add a device', form=form)
