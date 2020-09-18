from dotenv import load_dotenv
load_dotenv()

import os

class Config(object):
    SECRET_KEY = os.environ.get('SECRET_KEY') or 'random secret key'
    BOOTSTRAP_SERVE_LOCAL = os.environ.get('BOOTSTRAP_SERVE_LOCAL') or True
    DEVICETYPES = [{"devType": "perPump", "friendlyName": "Peristaltic Pump"}, {"devType": "solValve", "friendlyName": "Solenoid Valve"}, {"devType": "sixValve", "friendlyName": "6-Port Valve"}, {"devType": "switchValve", "friendlyName": "Switching Valve"}]