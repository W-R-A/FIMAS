from dotenv import load_dotenv
load_dotenv()

import os

class Config(object):
    SECRET_KEY = os.environ.get('SECRET_KEY') or 'random secret key'
    BOOTSTRAP_SERVE_LOCAL = os.environ.get('BOOTSTRAP_SERVE_LOCAL') or True