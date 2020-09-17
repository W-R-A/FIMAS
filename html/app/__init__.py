from flask import Flask
from flask_bootstrap import Bootstrap

app = Flask(__name__)

from app import routes, errors

bootstrap = Bootstrap(app)

app.config['BOOTSTRAP_SERVE_LOCAL'] = True