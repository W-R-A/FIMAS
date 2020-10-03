from flask import url_for, redirect
from app import app

import subprocess
import shlex




@app.route('/shutdown')
def shutdown():
    cmd = shlex.split("sudo shutdown -h now")
    subprocess.call(cmd)
    flash("Shutdown request sucessful, please wait for 30 seconds before unplugging the USB cable!")
    return redirect(url_for('index'))