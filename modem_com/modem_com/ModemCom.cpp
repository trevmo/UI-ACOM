/**
* This file contains the implementations of the methods of ModemCom as well as
* initialization of supporting data structures.
*
* @author trevmo
*/

#include "ModemCom.h"

/**
 * Initialize a static, constant structure holding all of the settings for the serial
 * port connected to the Iridium modem.
 */
const PortSettings ModemCom::SETTINGS = {
	asio::serial_port_base::baud_rate(19200),
	asio::serial_port_base::parity(asio::serial_port_base::parity::none),
	asio::serial_port_base::character_size(8),
	asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one),
	asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none)
};

/**
 * Declare the static members of the class.
 */
const int ModemCom::MAX_READ = 20;
SerialPortPointer ModemCom::port;
bool ModemCom::_continue;

/**
 * Initialize a new instance of ModemCom, particulary its underlying serial port.
 */
ModemCom::ModemCom()
{
	port = SerialPortPointer(new asio::serial_port(service));
	_continue = true;
}
/**
 * Close the port upon end of use.
 */
ModemCom::~ModemCom()
{
	port->close();
}
/**
 * Open the specified port and initialize the settings.
 * @param portName Linux path to serial port (/dev/tty*)
 * @return if successful, true; otherwise, false
 */
bool ModemCom::initPort(std::string portName)
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
/**
 * Start a session allowing a user to interface with the modem by
 * entering commands and receiving its response(s).
 */
void ModemCom::session()
{
	std::thread receiveThread(ModemCom::receive);
	std::thread transmitThread(ModemCom::transmit);

	receiveThread.detach();
	transmitThread.join();
}
/**
 * Accept input from the user and send the command to the modem.
 * Note: This method is static and designed to be run in its own thread.
 */
void ModemCom::transmit()
{
	while (_continue)
	{
		if (port == NULL || !port->is_open())
			return;

		std::string command;
		std::cin >> command;

		if (command != "quit")
			send(command);
		else
			_continue = false;
	}
}
/**
 * Send the specified message over the port.
 * @param message AT command
 */
void ModemCom::send(std::string message)
{
	if (port == NULL || !port->is_open())
		return;

	asio::write(*port, asio::buffer(message, message.length()));
}
/**
 * Continually try to receive responses from the modem through the port.
 * Note: This method is static and designed to be run in its own thread.
 * TODO: debug why only the first line of the response is received and not the rest.
 */
void ModemCom::receive()
{
	while (_continue)
	{
		if (port == NULL || !port->is_open())
			return;
	
		try
		{
			char *msgReceived = new char[MAX_READ];
			int numRead = port->read_some(asio::buffer(msgReceived, MAX_READ));
			if (numRead > 0)
				std::cout << "\t" << msgReceived << std::endl;
			delete[] msgReceived;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception occurred while reading from port.\n";
			std::cerr << e.what() << std::endl;
		}
		
	}
}

