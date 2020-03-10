#ifndef FIMAS_PERPUMP
#define FIMAS_PERPUMP

#include "mbed.h"

//Peristaltic Pump class

//Class

class perPump
{
    //Private Properties
    private:
	
	//Declare a digital out to hold the pin used to control the pump
	DigitalOut* controlPin;
	
	//The state of the pump, 0 is off and 1 is on
	//Inital state is 0, off
	uint8_t state = 0;
	
	//ID of the device, important to allow for control by ID
	unsigned short devID = 0;
	


    //Public API
    public:
    //Constructor
    //Pin specifies the pin that the pump is connected to
    perPump(PinName pin, unsigned short deviceID);

    //Destructor
    ~perPump();

    //Change the state of the 
    //0 turns the pump off, 1 turns the pump on
    void changeState(int newState);	
	
	//Get the ID of the device
	unsigned short getID (void);
};

#endif
