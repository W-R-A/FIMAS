# Overview #

The Web-Serial interface is based on the excellent flask tutorial by [Miguel Grinberg](https://github.com/miguelgrinberg), [available here](https://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-i-hello-world).

The interface provides an easy to use GUI to configure the system, while translating instructions into serial to control the microcontroller. It also handles all persistant storage and complex data processing, leaving the microcontroller free to focus on the precise timing required. 

All serial commands are initiated by the web interface, and the microcontroller acknowledges each command sent, along with completing any other action required, as specified in the serial command guide [here](https://github.com/W-R-A/FIMAS/blob/master/Microcontroller%20Software/serial/README.md).

To develop the code, a python virtual environment needs to be created. The following instructions apply to Windows 10. Firstly, download and install the latest version of python from [here](https://www.python.org/downloads). After downloading the code, and navigating to the Web-Serial Interface Software folder, open a command prompt and type `python3 -m venv venv` or `py -m venv venv` for newer versions of Windows.

Next, activate the virtual environment by typing `venv\Scripts\activate` into the command prompt. Now, install all of the dependicies by typing `pip install -r requirements.txt`. 

Once all of the dependicies have been installed, the database can be created, by running the following commands.<br>
`flask db init` <br>
`flask db migrate -m "Create database"` <br>
`flask db upgrade`

As soon as this is finished, the development server can be started by entering `flask run` and can be accesssed by navigating to [localhost](http://localhost:5000) in a web browser on port 5000. Note that the serial commands will not work when running in development mode and that attempting to use them will cause a error. 
