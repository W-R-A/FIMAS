#include "perPump.hpp"

class perPump
{
    //Private Properties
    private:

	uint8_t state;


    //Public API
    public:
    //Constructor
    //Pin specifies the pin that the pump is connected to
    perPump(PinName pin);

    //Destructor
    ~perPump();

    //Change the state of the 
    //0 turns the pump off, 1 turns the pump on
    void changeState(int newState);	
};
