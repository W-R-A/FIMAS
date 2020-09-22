#Imports
#Flask
from flask import Flask

#Configuration
from config import Config

#Database and migration
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate

#Bootstrap
from flask_bootstrap import Bootstrap


#Create app
app = Flask(__name__)

#Configure it
app.config.from_object(Config)

#Setup database
db = SQLAlchemy(app)
migrate = Migrate(app, db)

#Import routes 
from app import routes, errors, data, device

#Import database models
from app import models

#Start bootstrap
bootstrap = Bootstrap(app)