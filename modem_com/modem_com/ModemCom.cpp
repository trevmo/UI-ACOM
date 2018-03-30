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
 * Initialize a new instance of ModemCom, particulary its underlying serial port.
 */
ModemCom::ModemCom()
{
	port = SerialPortPointer(new asio::serial_port(service));
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
 * Send the specified message over the port.
 * @param message AT command
 */
void ModemCom::transmit(std::string message)
{
	if (port == NULL || !port->is_open())
		return;

	asio::write(*port, asio::buffer(message, message.length()));
}

