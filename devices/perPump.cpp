#include "perPump.hpp"

//pin specifies the pin that the Peristaltic Pump is connected to
//deviceID uniquely identifies the device
//Constructor is inhertited from baseDevice
perPump::perPump(PinName pin, unsigned short deviceID) : baseDevice(pin, deviceID) {}
