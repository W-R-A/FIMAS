#!/usr/bin/env python3

# Import modules
# Time to allow for time delays when writing/reading from/to the serial port
# sys for clean exits if required
from time import sleep
import sys

# Attempt to import modules that might throw an error
try:
    # Serial to communicate with the MCU over USART
    import serial

    # Threading to allow for parallel tasks
    import threading

    # Flask to act as a web server to host the web interface
    from flask import Flask, url_for, render_template

# Catch import errors and exit cleanly
except ImportError:
    print("Error importing modules. Are we running on a Raspberry Pi and have all modules been installed")
    sys.exit(1)
finally:
    print("Imports done")

# Create a serial object with the following properties
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

"""
Define a function to send a command over USART to the MCU, blocking until a valid response is received back 
Valid responses end in OK or FAIL
Returns a string containing the response or error if no valid response is received
"""


def sendCommand(cmd):

    # Add a carriage return to mark the end of the command
    cmd = cmd + "\r"

    # Encode it in UTF-8 so that it can be send over serial
    encCmd = bytes(cmd, 'utf-8')

    # Send the command over serial
    ser.write(encCmd)

    # Block until a response is received
    while (ser.inWaiting() == 0):
        sleep(0.01)

    # Create a variable to hold the response
    data = ""

    # While there is data to be read, read it
    while(ser.inWaiting() > 0):
        data = data + str(ser.read(), 'utf-8')

    # If the command was successful, return the data
    if "OK" in data:
        return data
    elif "FAIL" in data:
        return data
    # Else, return a string instead of invalid data
    else:
        return "Invalid response received"


# # Currently working as a command passthrough
# try:
#     while True:
#         # Print out the response to entered commands
#         print(sendCommand(input("Enter Command: ")))

# # Catch CTRL+C exits
# except KeyboardInterrupt:
#     print("Exiting Program")

# # Catch any other exceptions
# except Exception as e:
#     print("An error has occurred. \nDetails:", end=e)

# finally:
#     ser.close()
#     sys.exit()


app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/cmd/<string:command>')
def webCmd(command):
    # Execute command
    response = sendCommand(command)
    return response
