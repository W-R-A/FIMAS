/* 
 * Author: William Ross Andrewartha
 */

#include "serialInterface.hpp"
#include "hardware.hpp"

#include "serialInterface.hpp"
#include "sdInterface.hpp"
#include "sampling.hpp"

//Logging control variable
volatile bool logging = ON;

//Create a serial interface object to PC
RawSerial pc(USBTX, USBRX, 115200);

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


//Read all data from the internal buffer to serial
//No paramters need to be passed and nothing is returned
void readAll(void)
{
	//Create a temporary variable to hold the data from the FIFO buffer
	enviroParams data;
	
	//While the buffer still has data in it, pop the data out and write it to the SD card
	while (!enviroBuffer.empty())
	{
		//Pop the data off the buffer
		enviroBuffer.pop(data);
		
		//Write it to serial
		pc.printf("Light Level: %f, Temperature: %f degrees celsius, Pressure %f mBar, Timestamp %s", data.ldr, data.temperature, data.pressure, ctime(&data.seconds));
	}
}

//Decode the command sent over serial and take the appropiate action
//Pass the string comtaing the command
//Nothing is returned
void cmdDecode(string cmd)
{
    //Read Now
    if (cmd.find(cmdReadNow) != string::npos) {
        //Read current record
        pc.printf("Read current record\n");
		
		//Read the environmental sensors
		//Returns a enviroParams structure containg the enviornmental data along with a timestamp
		enviroParams data = readNow();
		
		//Sent the data over serial
		pc.printf("Light Level: %f, Temperature: %f degrees celsius, Pressure %f mBar, Timestamp %s\n", data.ldr, data.temperature, data.pressure, ctime(&data.seconds));
    } 
    
    //Read All from buffer
    if (cmd.find(cmdReadAll) != string::npos) {
        //Echo confirmation
        pc.printf("Read all records");
		
		//Read all records to serial
		readAll();
    } 
    
    //Flush Buffer
    if (cmd.find(cmdFlush) != string::npos) {
        //Flush FIFO buffer
        pc.printf("Flush buffer");
        //SDQueue.call(flushBuffer);
    } 
    
    //Eject SD card after flushing buffer
    if (cmd.find(cmdEject) != string::npos) {
        //Flush all records to sd then eject SD card
        pc.printf("eject sd card");
        //SDQueue.call(flushBuffer);
        //SDQueue.call(SDclose);
        
    } 
    
    //Enable/disable sampling
    if (cmd.find(cmdState) != string::npos) {
        //Check if sampling is to be turned on or off
        if (cmd.find("ON") != string::npos) {
            //Enable sampling
			samplingQueue.call(startSampling);
			
			//Echo confirmation to serial
            pc.printf("Sampling is enabled\n");
        } 
        else if (cmd.find("OFF") != string::npos) {
            //Disable sampling
			samplingQueue.call(stopSampling);
			
			//Echo confirmation to serial
            pc.printf("Sampling is disabled\n");
        } 
        else 
        {
			//Invalid option
            pc.printf("Invalid Option\n");
        }
    } 
    
    //Enable/disable logging
    if (cmd.find(cmdLogging) != string::npos) {
        //Check if logging is to be turned on or off
        if (cmd.find("ON") != string::npos) {
            //Enable logging
			logging = ON;
			
			//Echo confirmation to serial
            pc.printf("Logging is enabled");
        } 
        else if (cmd.find("OFF") != string::npos) {
            //Disable logging
			logging = OFF;
			
			//Echo confirmation to serial
            pc.printf("Logging is disabled");
        } 
        else 
        {
			//Invalid option
            pc.printf ("Invalid Option\n");
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
			//Check if the buffer needs to be flushed before the sample rate is updated
			SDQueue.call(checkBufferSpace);
			
			//Update the sampling period
			samplingQueue.call(updateSamplingPeriod, fTime);
		
			//Echo confirmation to serial
			pc.printf("Sampling period set to %f seconds\n", fTime); 
		}
		else
		{
			//Print error to serial
			pc.printf("Invalid time period, T should be between 0.1 and 30 seconds\n"); 
		}
    }
}


//Serial interface - Responsible for reading and writing to the serial interface
//No parameters need to be passed and nothing is returned
void serialInterface(void)
{
    //Attach an interrupt to detect when a character has been recieived over serial
    pc.attach(serialInputInterrupt, Serial::RxIrq);

    //Start event queue on thread
    serialQueue.dispatch();
}

//This interrpt fires when a character is recieived over the serial interface
//No paramters need to be passed and nothing is returned
void serialInputInterrupt(void)
{
    //Disable interupt
    pc.attach(NULL, Serial::RxIrq);
	
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
    pc.printf("Enter Command: ");
    
    //Command length counter
    char i = 0;
    
	//Block the serial eventqueue while a command is being entered, 5s timeout
	//This does use a spin lock, polling a timer but this allows for a better user interface while the user is actively communicating with the device. When the device is not being controlled over serial, thi will not be run, saving power.
    while (true)
    { 
		//Check if there is a character to be read
		if (pc.readable())
		{
			//Get user input
			char j = pc.getc();
			
			//Echo user input
			pc.putc(j);
					
			//If string is over 15 in length, invalid, return
			if (i > 15)
			{
				pc.printf("Unrecognised command entered, please try again\n");
				pc.printf(SERIAL_COMMAND_GUIDE);
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
			pc.printf("Serial command timeout, please try again ensuring each key presss is within 5 seconds of the last\n");
			break;
		}
    }

    //Reenable interrupt
    pc.attach(serialInputInterrupt, Serial::RxIrq);
}	