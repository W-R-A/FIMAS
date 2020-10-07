# Hardware Configuration #

In order to provide an easy way to adapt the firmware to different devices, all the utilised interfaces are defined in hardware.hpp and hardware.cpp. These files are then included by the rest of the program.

The pin configuration is done in the hardware.cpp file. The array defines the pins that are to be used and can be adjusted to suit the microcontroller that the firmware is running on. 

The USART interface and types of devices are configured in hardware.hpp. The USART pins used and the hardware interface will need to be defined for the microcontroller, so that the specific USART hardware registers can be used. This overcomes deadlocking issues and poor performance that occurred whe using the serial abstraction provided by mbed-os. 

If another type of device is to be used, a new enumeration will need to be created and a new class written, inheriting from the base device class. The new header file can be included and then after updating the add device part of the data manger and serial device configuration, the new device should be ready for use. 

Finally, if the number of input/output pins has been changed, the size of the array will need to be updated. 