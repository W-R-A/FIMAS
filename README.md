# Flow Injection Micro Analysis System #

## Project Overview ##

The FIMAS project is designed to automate lab machines used to perform flow injection analysis. The project consists of two main parts. A microcontroller running mbed-os is connected through relays and other interface circuits to the lab devices, and is responsible for producing the signals required at the precise times necessary to produce accurate and repeatable results. Running alongside it is a Raspberry Pi Zero W, which interfaces to a computer over a USB connection and provides a user-freindly way of configuring the system. The Raspberry Pi communicates with the microcontroller over USART. 

The only software needed on the control computer is a web browser, which greatly simplifies the setup process as no specific programs need to be installed. The use of a web browser saves istallation time and makes the system portable between different operating systems. 