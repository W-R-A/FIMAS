#include "solValve.hpp"

//pin specifies the pin that the solenoid valve is connected to
//deviceID uniquely identifies the device
//Constructor is inhertited from baseDevice
solValve::solValve(PinName pin, unsigned short deviceID) : baseDevice(pin, deviceID) {}
