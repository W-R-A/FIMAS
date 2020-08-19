/* 
 * Author: William Ross Andrewartha
 */

#include "serialInterface.hpp"
#include "hardware.hpp"
#include "deviceConfig.hpp"
#include "routineConfig.hpp"

//Create a serial interface object to PC
UnbufferedSerial pc(USBTX, USBRX, 115200);

//Timeout used with serial
Timer serialTimeout;

//Serial Communication Thread
Thread serialThread;

//Create eventqueues
EventQueue serialQueue;

//Use standard namespace to keep things cleaner
using namespace std;

//Decode the command sent over serial and take the appropiate action
//Pass the string comtaing the command
//Nothing is returned
void cmdDecode(string cmd)
{
    //Clear devices
    if (cmd.find("CLEARDEVICES") != string::npos) {

        //Clear the devices on the system
        _dataManager.setClearDevices();
        
        //Send acknowledgement
        sendString("CLEARDEVICES: OK\n");

        return;	
	} 
    //Clear routine
    else if (cmd.find("CLEARROUTINE") != string::npos) {

        //Clear the routine on the system
        _dataManager.setClearRoutine();

        //Send acknowledgement
        sendString("CLEARROUTINE: OK\n");
		
	}     
    //Config devices
    else if (cmd.find("CONFIGDEVICE") != string::npos) {

        //Calculate the position of the command and use it to get the start of the arguments provided
        uint32_t configPos = cmd.find("CONFIGDEVICE")+13;

        //Get the argument string for the new device to be created after the configdevice command
        string devConfig = cmd.substr(configPos, string::npos);

        //Pass the config info to the parser to create the device, informing the user if the command succeeded
        if (configDevicesSerial(devConfig)) {

            //Send acknowledgement
            sendString("CONFIGDEVICE: FAIL\n");
        } else {

            //Send acknowledgement
            sendString("CONFIGDEVICE: OK\n");
        }

        
	} 
    //Config routine
    else if (cmd.find("CONFIGROUTINESTEP") != string::npos) {

        //Calculate the position of the command and use it to get the start of the arguments provided, length of command + 1 for space delimiter
        uint32_t configPos = cmd.find("CONFIGROUTINESTEP")+18;

        //Get the argument string for the new device to be created after the configdevice command
        string routineConfig = cmd.substr(configPos, string::npos);

        if (configRoutineSerial(routineConfig)) {
            
            //Send acknowledgement
            sendString("CONFIGROUTINESTEP: FAIL\n");
        } else {

            //Send acknowledgement
            sendString("CONFIGROUTINESTEP: OK\n");
        }    
		
	}
    //View devices
    else if (cmd.find("VIEWDEVICES") != string::npos) {

        //Send the devices string over USART
        sendString(_dataManager.getDevicesString());
            
        //Send acknowledgement
        sendString("VIEWDEVICES: OK\n");

        return;		
	}
    //View routine
    else if (cmd.find("VIEWROUTINE") != string::npos) {

        //Send the routine string over USART
        sendString(_dataManager.getRoutineString());
            
        //Send acknowledgement
        sendString("VIEWROUTINE: OK\n");

        return;
		
	}
    //Run routine
    else if (cmd.find("RUN") != string::npos) {

        _dataManager.setSystemState(STATE_RUNNING_START);

        //Send acknowledgement
        sendString("RUN: OK\n");
		
	} 
    
    //System status
    else if (cmd.find("STATUS") != string::npos) {

        sendString(_dataManager.getSystemStateString());

        //Send acknowledgement
        sendString("STATUS: OK\n");

        return;
    } 
    //ESTOP
    else if (cmd.find("ESTOP") != string::npos) {
        
        //Change the state to ESTOP
        _dataManager.setSystemState(STATE_ESTOP);

        //Send acknowledgement
        sendString("ESTOP: OK\n");		

        return;
	} 

    //Test devices
    else if (cmd.find("TESTDEVICES") != string::npos) {
        
        //Test the devices
        sendString(_dataManager.getTestDevices());

        //Send acknowledgement
        sendString("TESTDEVICES: OK\n");		

        return;
	} 
    else {
        sendString("Unrecognised command entered, please try again\n");
		sendString(SERIAL_COMMAND_GUIDE);  
    }

      

}


//Serial interface - Responsible for reading and writing to the serial interface
//No parameters need to be passed and nothing is returned
void serialInterface(void)
{
    //Attach an interrupt to detect when a character has been recieived over serial
    pc.attach(serialInputInterrupt, SerialBase::RxIrq);

    //Start event queue on thread
    serialQueue.dispatch();
}

//This interrpt fires when a character is recieived over the serial interface
//No paramters need to be passed and nothing is returned
void serialInputInterrupt(void)
{
    //Disable interupt
    pc.attach(NULL, SerialBase::RxIrq);
	
	//Restart timeout
	serialTimeout.stop();
	serialTimeout.reset();
	serialTimeout.start();

    //Call the serial input handler
    serialQueue.call(serialInputHandler);
}

//Handle serial input - block and allow the user to enter a command.
//Decode it and call cmdDecode to take the appropiate action
//No paramters need to be passed and nothing is returned
void serialInputHandler(void)
{
    //Empty string to hold the command sent over serial
    string cmd("");
    
    //Send instructions
    sendString("Enter Command: ");
    
    //Command length counter
    char i = 0;
    
	//Block the serial eventqueue while a command is being entered, 5s timeout
	//This does use a spin lock, polling a timer but this allows for a better user interface while the user is actively communicating with the device. When the device is not being controlled over serial, thi will not be run, saving power.
    while (true)
    { 
		//Check if there is a character to be read
		if (pc.readable())
		{
			//Declare char to recieve user input
			char j;

			//Get user input
            pc.read(&j, 1);

			//Echo user input
			pc.write(&j, 1);
					
			//If string is over 40 in length, invalid, return
			if (i > 40)
			{
				sendString("Unrecognised command entered, please try again\n");
				sendString(SERIAL_COMMAND_GUIDE);
				break;
			}
			//Check for commands if the enter key is pressed
			if (j == '\r') 
			{
				cmdDecode(cmd);
				break;
			}
			//If delete, ascii 127, do not add to string, remove last character added
			if (j == 127)
			{
				//Delete last char of string
				cmd.pop_back();
				
				//Decrement i
				i--;
			}
			else
			{
				//Add char to command string, after ensuring that it is in uppercase
				cmd.append(1,toupper(j));
				
				//Increment i 
				i++;
			}
			//restart timeout
			serialTimeout.stop();
			serialTimeout.reset();
			serialTimeout.start();
		}
		//If 5s has passed and no new char has been received, timeout and return to serial output
		else if (serialTimeout.read() > 5)
		{
			sendString("Serial command timeout, please try again ensuring each key presss is within 5 seconds of the last\n");
			break;
		}
    }

    //Reenable interrupt
    pc.attach(serialInputInterrupt, SerialBase::RxIrq);
}	

//Send a byte of data over USART
//Paul Davey - Lecture 6 Slide 3rd from the end
void send_usart(unsigned char d)
{
	//Wait for the serial port to be writeable
	while(!pc.writeable()) {};	

	//Write byte to the serial port
    pc.write(&d, 1);	
}


//Send a string over USART
//Paul Davey - Lecture 6 Slide 3rd from the end
void sendCString(const char *string)
{
	//Declare temporary variable
	unsigned short i = 0;

	//While there is data still to be sent
	while(string[i])
	{
		//Send char
		send_usart(string[i]);

		//Increment i
		i++;
	}
}

//Send a string over USART
//Paul Davey - Lecture 6 Slide 3rd from the end
void sendString(std::string strPrint)
{
    //Convert to a c string from c++ before sending as before
    sendCString(strPrint.c_str());
}
