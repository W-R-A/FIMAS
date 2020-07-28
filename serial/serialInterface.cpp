/* 
 * Author: William Ross Andrewartha
 */

#include "serialInterface.hpp"
#include "hardware.hpp"

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

//Serial commands, as defined by table 2 in the coursework requirements
string cmdReadNow ("READ NOW");
string cmdReadAll ("READ BUFFER");
string cmdFlush   ("FLUSH");
string cmdEject   ("EJECT");
string cmdState   ("STATE ");
string cmdLogging ("LOGGING ");
string cmdSetT    ("SETT ");




//Decode the command sent over serial and take the appropiate action
//Pass the string comtaing the command
//Nothing is returned
void cmdDecode(string cmd)
{
    //Read Now
    if (cmd.find(cmdReadNow) != string::npos) {
        //Read current record
        sendString("Read current record\n");
		
	} 
    
    //Read All from buffer
    if (cmd.find(cmdReadAll) != string::npos) {
        //Echo confirmation
        sendString("Read all records");

    } 
    
    //Flush Buffer
    if (cmd.find(cmdFlush) != string::npos) {
        //Flush FIFO buffer
        sendString("Flush buffer");

    } 
    
    //Eject SD card after flushing buffer
    if (cmd.find(cmdEject) != string::npos) {
        //Flush all records to sd then eject SD card
        sendString("eject sd card");        
    } 
    
    //Enable/disable sampling
    if (cmd.find(cmdState) != string::npos) {
        //Check if sampling is to be turned on or off
        if (cmd.find("ON") != string::npos) {
            //Enable sampling

			
			//Echo confirmation to serial
            sendString("Sampling is enabled\n");
        } 
        else if (cmd.find("OFF") != string::npos) {

			
			//Echo confirmation to serial
            sendString("Sampling is disabled\n");
        } 
        else 
        {
			//Invalid option
            sendString("Invalid Option\n");
        }
    } 
    
    //Enable/disable logging
    if (cmd.find(cmdLogging) != string::npos) {
        //Check if logging is to be turned on or off
        if (cmd.find("ON") != string::npos) {

			
			//Echo confirmation to serial
            sendString("Logging is enabled");
        } 
        else if (cmd.find("OFF") != string::npos) {

			
			//Echo confirmation to serial
            sendString("Logging is disabled");
        } 
        else 
        {
			//Invalid option
            sendString("Invalid Option\n");
        }
    } 
    if (cmd.find(cmdSetT) != string::npos) {
        //Determine if a valid time has been specified, all charcters after the space which is at position 4 onwards to the end of the string
        string time = cmd.substr(5, string::npos);
        
        //Attempt to convert to float format
        float fTime = stof(time);
		
		//Check within bounds, 0.1<=T<=30
		if ((fTime>=0.1f) && (fTime <= 30.0f))
		{
		
			//Echo confirmation to serial
			//sendString("Sampling period set to %f seconds\n", fTime); 
		}
		else
		{
			//Print error to serial
			sendString("Invalid time period, T should be between 0.1 and 30 seconds\n"); 
		}
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
					
			//If string is over 15 in length, invalid, return
			if (i > 15)
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
void sendString(const char *string)
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
