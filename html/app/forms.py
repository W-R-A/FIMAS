from flask_wtf import FlaskForm
from wtforms import StringField, SelectField, SubmitField
from wtforms.validators import DataRequired
from app import db
from app.models import Routine, Device, Timing



class AddDeviceForm(FlaskForm):
    devTypes = [{"devType": "perPump", "friendlyName": "Peristaltic Pump"}, {"devType": "solValve", "friendlyName": "Solenoid Valve"}, {"devType": "sixValve", "friendlyName": "6-Port Valve"}, {"devType": "switchValve", "friendlyName": "Switching Valve"}]
    devPins = [{"pin":"1","type":"output"},{"pin":"2","type":"output"},{"pin":"3","type":"output"},{"pin":"4","type":"output"},{"pin":"5","type":"output"},{"pin":"6","type":"output"},{"pin":"7","type":"output"},{"pin":"8","type":"output"},{"pin":"1","type":"input"},{"pin":"2","type":"input"},{"pin":"3","type":"input"},{"pin":"4","type":"input"}]

    devChoices = []

    for i in range (0, len(devTypes)):
        devChoices.append([devTypes[i]["devType"], devTypes[i]["friendlyName"]])

    devPinChoices = []

    for i in range (0, len(devPins)):
        devPinChoices.append([devPins[i]["pin"], str(devPins[i]["type"].capitalize() + " " + str(devPins[i]["pin"]))])

    devName = StringField('Device Name', validators=[DataRequired()])
    #choices, machine option, user friendly option
    devType = SelectField('Device Type', choices = devChoices, validators=[DataRequired()])
    devPin1 = SelectField('Primary Interface', choices = devPinChoices, validators=[DataRequired()])

    #Append not used to all options other than the primary one
    # There have to be unique lists of choices for each option, as the code does not execute sequentaly 
    devPinChoices2 = devPinChoices.copy()

    devPinChoices2.append(["-1", "Not Used"])

    devPin2 = SelectField('Secondary Interface', choices = devPinChoices2, validators=[DataRequired()])
    submit = SubmitField('Add Device')



class DeleteDeviceForm(FlaskForm):

    #Create the select input and submit button
    devID = SelectField('Device Name', coerce=int, validators=[DataRequired()])
    submit = SubmitField('Delete Device')


    def populateDevices(self):

        #Create empty list to hold the devices on the system
        deviceChoices = []

        #Get all of the devices on the system
        devices = Device.query.all()
        
        #Setup options for html select
        for i in range(0, len(devices)): 
            deviceChoices.append([devices[i].id, devices[i].name])

        self.devID.choices = deviceChoices



class AddRoutineForm(FlaskForm):

    #Create the name input field and submit button
    name = StringField('Routine Name', validators=[DataRequired()])
    
    submit = SubmitField('Add Routine')



class DeleteRoutineForm(FlaskForm):

    #Create the select input and submit button
    rouID = SelectField('Routine Name', coerce=int, validators=[DataRequired()])
    submit = SubmitField('Delete Routine')


    def populateRoutines(self):

        #Create empty list to hold the routines on the system
        routineChoices = []

        #Get all of the routines on the system
        routines = Routine.query.all()
        
        #Setup options for html select
        for i in range(0, len(routines)): 
            routineChoices.append([routines[i].id, routines[i].name])

        self.rouID.choices = routineChoices
