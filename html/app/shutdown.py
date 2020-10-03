from flask import url_for, redirect
from app import app

import os

@app.route('/shutdown')
def shutdown():
    os.system('systemctl poweroff')
    return redirect(url_for('index'))