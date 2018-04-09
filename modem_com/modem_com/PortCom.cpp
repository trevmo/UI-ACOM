/**
 * This file contains the implementations of the methods of PortCom as well as
 * initialization of supporting data structures.
 *
 * @author trevmo
 */
#include "PortCom.h"


/**
 * Declare the static members of the class.
 */
PortSettings PortCom::SETTINGS;
SerialPortPointer PortCom::port;
const int PortCom::MAX_READ = 128;
bool PortCom::_continue;

/**
 * Initialize a new instance of PortCom, particulary its underlying serial port.
 */
PortCom::PortCom()
{
	port = SerialPortPointer(new asio::serial_port(service));
	_continue = true;
}
/**
 * Close the port upon end of use.
 */
PortCom::~PortCom()
{
	port->close();
}
/**
 * Open the specified port and initialize the settings.
 * @param portName Linux path to serial port (/dev/tty*)
 * @return if successful, true; otherwise, false
 */
bool PortCom::initPort(std::string portName)
{
	try
	{
		port->open(portName.c_str());

		port->set_option(SETTINGS.baudRate);
		port->set_option(SETTINGS.parity);
		port->set_option(SETTINGS.dataBits);
		port->set_option(SETTINGS.stopBits);
		port->set_option(SETTINGS.flowControl);

		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception occurred while opening port.\n";
		std::cerr << e.what() << std::endl;
	}
	return false;
}