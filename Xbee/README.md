# Xbee Com

## Summary
This code base builds an application that can be used to send data to and through the Xbee module using a UART interface on the Raspberry Pi. The main portion of the application code focuses on sending and receiving data through the UART comm port. Along with the facilities to send and receive data bytes through the UART there is basic functionality for configuring the Xbee module which is necessary to get the network set up and determine what modules should communicate with one another.

## Dependencies
- Configured Xbee Xtend 900 1W module
- Linux OS
- UART wired connection

## Development
Developed natively on Raspberry Pi running Arch Linux.

### Hardware UART on Raspberry Pi V2 or Greater
This application was designed to use the native UART port on the Raspberry Pi. On any Raspberry Pi with Bluetooth functionality the hardware UART is owned by the Bluetooth module by default. you MUST reconfigure the Raspberry Pi so that Bluetooth is either disabled or it uses the mini-UART or else the code will not function.

## Files
### main
This file contains the main entry point of the application and showcases a small example of how you might use the built in functionality. 

The first function in this file is the callback function. This callback function shows a simple way to capture data returned by the Xbee module into a buffer. The buffer is contained within the specific comm port structure and is accessed through the defined struct.

The second function is main and it shows how to set up and initialize the comm port struct as well as a run loop that takes in user input and sends it to the Xbee module through UART.

### at_bound_checker
These files only contains a single function at this point but future work would revolve around adding more error checking code to this file.

The single function accessible in this file checks to see if the input for a given AT command falls within the possible range of values expected for that command. If the function is read only then it returns true because there is no input required. Otherwise if the input is within range it returns true, and if the input is not within range it returns false.

### at_command_helper
This file contains information regarding the AT commands.

The first thing in the file is an enumerated list of all the AT commands supported by this specific Xbee module. 
* Each AT command has a decimal value associated with it which will be the actual value sent when sending an AT command to configure the module. 
* Some of the AT command abbreviated names do not match what is in the documentation exactly. This is due to C/C++ naming conventions and is the reason behind the assigned enumerated values which do match the documented values.  
* Some of the AT commands do not have values associated with them. These values simply had available values assigned to them. These values are in the 0x30 - 0x45 range but do not include all values in that range.

The function found in this file is used for debugging and returns a string description of an AT command.

### xbee_comm_functions
These files provide a small interface between the UART comm library and the Xbee specific commands. These functions are what should be used for sending data. Currently most of them do not do much more than pass input through to the UART comm library however some do provide input validation and also append information to the data being sent to the Xbee.

### uart_comm_library
This makes up the bulk of the application and consist of code that facilitates communication between the Raspberry Pi and the Xbee module. 

The files contain a definition for a serial comm structure that contains information about the specific comm port opened. This code was written based off of generic code for opening and utilizing any comm ports on a Linux system however it has had specific modifications made in order to work with the UART hardware found on the Rapsberry Pi.

When first starting communication over UART you first want to start the comm port by running startComm(). You will then want to open the port with your desired setting. An example of settings that should work using this specific Xbee module can be found in the main.cpp file.

You will then want to use the UART port structure you initialized when sending data or AT commands to the Xbee module.
> NOTE: These files and the application use the termios.h libraries included in Linux distributions. Therefore you can not compile this code on a non-Linux based OS.