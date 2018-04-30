# Modem Com

## Summary
This project builds an app to run on ArchLinux on a Raspberry Pi. It is designed to run as an auto-starting service at a user-defined time interval. The app communicates with a GPS receiver to retrieve the current latitude/longitude/elevation and then sends that information out as a Short Burst Data (SBD) message through an Iridium 9523 housed in an NAL A3LA-RS.

## Dependencies
- Boost
- NAL A3LA-RS
- GPS Receiver (GlobalSat BU353S4)

## Development
This project was developed as a cross-platform app in Visual Studio, targeted for an ARM-based Linux machine. 
### Remote Debugging
Visual Studio allows remote debugging after configuring a remote machine in the IDE.
Setup:
- [MSDN Instructions](https://docs.microsoft.com/en-us/cpp/linux/deploy-run-and-debug-your-linux-project)
- Add additional include libraries:
    - Project Properties -> C/C++ -> General -> Additional Include Directories... -> /path/to/boost
- Add additiona linker options:
    - Project Properties -> Linker -> Command Line -> Additional Options -> -lboost_system -lpthread
### ArchLinux Service
> TODO: add udev rule and service information

## Classes
### PortCom
Files:
- PortCom.h
- PortCom.cpp

PortCom serves as a base class for establishing serial communications with a device in Linux. It relies on Boost for setting up the port.

### ModemCom
Files:
- PortCom.h
- PortCom.cpp

ModemCom inherits from PortCom. It is the primary class for communicating with the NAL A3LA-RS. The class is designed to be run with multiple threads, one for sending commands to the modem and one for receiving responses from the modem. It provides methods for either running a user-bases session or an automated session. In the user-based session, a user can send AT commands to the modem from the command line and receive responses to stdout. In the automated session, the app reads GPS data from the attached receiver, sends the data as an SBD message over the Iridium network, and logs commands and responses to a file.

### GPSReader
Files:
- GPSReader.h
- GPSReader.cpp

GPSReader also inherits from PortCom. It is designed as a simple class for reading NMEA Sentences from a GPS receiver.
> Note: Be sure to configure your GPSReceiver according the instructions of the header commentn in GPSReader.h.
