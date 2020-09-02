/* 
 * Author: William Ross Andrewartha
 */

#include "serialInterface.hpp"
#include "hardware.hpp"
#include "deviceConfig.hpp"
#include "routineConfig.hpp"


#define USEDUSART USART2
//Create a serial interface object on USART 2
//Debugging, use the USART 3 instead. UnbufferedSerial pc(USBTX, USBRX, 115200);
//Also, adjust USART above with the used interface to allow for the serial interrupt to work correctly
//Serial default setttings - int bits=8, Parity parity=SerialBase::None, int stop_bits=1
UnbufferedSerial pc(PD_5, PD_6, 115200);


//Serial Communication Threads
Thread serialThread(osPriorityNormal, OS_STACK_SIZE, nullptr, "Serial Communicator");
Thread serialInputThread(osPriorityNormal, OS_STACK_SIZE, nullptr, "Input Serial Communicator");

//Create eventqueues
EventQueue serialQueue;

//Mailbox to hold recieved chars - max command length 40 chars
Mail<char, 40> serial_mail_box;

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

    //Test a device
    else if (cmd.find("TESTDEVICE") != string::npos) {
        
        //Calculate the position of the command and use it to get the start of the arguments provided, length of command + 1 for space delimiter
        uint32_t configPos = cmd.find("TESTDEVICE")+11;

        //Get the argument string for the device ID to test
        string testConfig = cmd.substr(configPos, string::npos);

        //Send results string
        sendString(testDeviceSerial(testConfig));

        //Send acknowledgement
        sendString("TESTDEVICE: OK\n");

        return;
	} 

    //Reset
    else if (cmd.find("RESET") != string::npos) {
        
        //Change the state to IDLE
        _dataManager.setSystemState(STATE_IDLE);

        //Clear the routine on the system
        _dataManager.setClearRoutine();

        //Clear the devices on the system
        _dataManager.setClearDevices();

        //Send acknowledgement
        sendString("RESET: OK\n");		

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

    //Start serial input thread
    serialInputThread.start(serialInputHandler);

    //Start event queue on thread
    serialQueue.dispatch();
}


//This interrpt fires when a character is recieived over the serial interface
//No paramters need to be passed and nothing is returned
void serialInputInterrupt(void)
{
    //Based on work by Sam Duffield - MDAS
    
    //Allocate space in the mailbox, blocking if needed - ISR SAFE as milisecond parameter is set to zero
    //https://os.mbed.com/docs/mbed-os/v6.2/mbed-os-api-doxy/classrtos_1_1_mail.html#ac01d110ce7cb71b9c1f5a0ff59216c15
    char *mail = serial_mail_box.try_alloc_for(0s);

    //Read the incoming char
    *mail = USEDUSART->DR;

    //Update the mailbox
    serial_mail_box.put(mail);
}


//Handle serial input 
//Decode it and call cmdDecode to take the appropiate action
//No paramters need to be passed and nothing is returned
void serialInputHandler(void)
{
    //Empty string to hold the command sent over serial
    string cmd("");
    
    //Command length counter
    char i = 0;        

    //Declare a char to recieve user input
	char j;

	//Spin and wait for a char to be recieved
    while (true)
    {
        //Block and wait for mail
		osEvent evt = serial_mail_box.get();

        //Get address of next char
        char *mail = (char *)evt.value.p;

        //Copy the value to j
        j = *mail;

        //send_usart(*mail);

        //Free memory
        serial_mail_box.free(mail);
        
        //If string is over 40 in length, invalid, reset
        if (i > 40)
        {
            serialQueue.call(sendCString, "Unrecognised command entered, please try again\n");
            serialQueue.call(sendCString, SERIAL_COMMAND_GUIDE);

            //Reset length counter
            i = 0;

            //Clear cmd
            cmd.clear();
        }
        //Check for commands if the enter key is pressed
        if (j == '\r') 
        {
            //Decode command
            cmdDecode(cmd);

            //Reset length counter
            i = 0;

            //Clear cmd
            cmd.clear();
        }
        else
        {
            //Add char to command string, after ensuring that it is in uppercase
            cmd.append(1,toupper(j));
            
            //Increment i 
            i++;
        }
		
    }
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
