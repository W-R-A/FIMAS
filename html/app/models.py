from app import db


class Device(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(32))
    devType = db.Column(db.String(16))
    interface1 = db.Column(db.Integer)
    interface2 = db.Column(db.Integer)

    def __repr__(self):
        return '<Device ID: {}, Name: {}, Type: {}, Interface 1: {}, Interface 2: {}>'.format(self.id, self.name, self.devType, self.interface1, self.interface2)
