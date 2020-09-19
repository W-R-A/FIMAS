from app import app, db
from app.models import Routine, Device, Timing

@app.shell_context_processor
def make_shell_context():
    return {'db': db, 'Routine': Routine, 'Device': Device, 'Timing': Timing}