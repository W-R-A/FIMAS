from app import db


class Routine(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(32))

    def __repr__(self):
        return '<Routine ID: {}, Name: {}>'.format(self.id, self.name)


class Device(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(32))
    devType = db.Column(db.String(16))
    interface1 = db.Column(db.Integer)
    interface2 = db.Column(db.Integer)
    routine_id = db.Column(db.Integer, db.ForeignKey('routine.id'))

    def __repr__(self):
        return '<Device ID: {}, Name: {}, Type: {}, Interface 1: {}, Interface 2: {}, Routine ID: {}>'.format(self.id, self.name, self.devType, self.interface1, self.interface2, self.routine_id)


class Timing(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    device_id = db.Column(db.Integer, db.ForeignKey('device.id'))
    routine_id = db.Column(db.Integer, db.ForeignKey('routine.id'))
    startTime = db.Column(db.Integer)
    stopTime = db.Column(db.Integer)
    state = db.Column(db.Integer)

    def __repr__(self):
        return 'Timing ID: {}, Device ID: {}, Routine ID: {}, Start Time: {}, Stop Time: {}, State: {}>'.format(self.id, self.device_id, self.routine_id, self.startTime, self.stopTime, self.state)

