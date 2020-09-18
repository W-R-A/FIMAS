from flask_wtf import FlaskForm
from wtforms import StringField, SelectField, SubmitField
from wtforms.validators import DataRequired

class ADDDEVICEFORM(FlaskForm):
    devName = StringField('Device Name', validators=[DataRequired()])
    #choices, machineoption, user friendly option
    devType = SelectField('Device Type', choices = [['test ggf', 'ffcc']], validators=[DataRequired()])
    devPin1 = SelectField('Primary Interface', validators=[DataRequired()])
    devPin2 = SelectField('Secondary Interface', validators=[DataRequired()])
    submit = SubmitField('Add Device')