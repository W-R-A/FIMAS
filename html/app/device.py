from flask import render_template, url_for, flash, redirect, jsonify
from app import app, db
from app.models import Routine, Device, Timing

