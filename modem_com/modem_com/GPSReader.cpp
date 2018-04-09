/**
* This file contains the implementations of the methods of GPSReader as well as
* initialization of supporting data structures.
*
* @author trevmo
*/

#include "GPSReader.h"

/**
* Initialize a static, constant structure holding all of the settings for the serial
* port connected to the Iridium modem.
*/
const PortSettings GPSReader::SETTINGS = {
	asio::serial_port_base::baud_rate(4800),
	asio::serial_port_base::parity(asio::serial_port_base::parity::none),
	asio::serial_port_base::character_size(8),
	asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one),
	asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none)
};
const std::string GPSReader::PORT_NAME = "/dev/ttyUSB0";

/**
* Close the port upon end of use.
*/
GPSReader::~GPSReader()
{
	port->close();
}
/**
 * Attempt to read an NMEA sentence from the GPS receiver.
 * Note: expects the receiver to be setup to send GGA sentences only.
 */
std::string GPSReader::read()
{
	std::string message = "";
	std::vector<std::string> nmeaValues;
	bool allReceived = false;
	// Following the NMEA standard for GPGGA strings
	// index of the latitude coordinate
	int latIndex = 2;
	// index of the longitude coordinate
	int longIndex = latIndex + 2;
	// index of the altitude measurement
	int altIndex = longIndex + 5;
	while (!allReceived)
	{
		if (port == NULL || !port->is_open())
			return "";

		try
		{
			char c;
			int numRead = port->read_some(asio::buffer(&c, 1));
			if (numRead > 0)
			{
				if (c == '\r')
					allReceived = true;
				else
					message += c;
				if (allReceived)
				{
					boost::split(nmeaValues, message, [](char c) { return c == ','; });
					return nmeaValues[latIndex] + nmeaValues[latIndex+1] + 
						"," + 
						nmeaValues[longIndex] + nmeaValues[longIndex+1] +
						"," +
						nmeaValues[altIndex] + nmeaValues[altIndex+1];
				}
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception occurred while reading from port.\n";
			std::cerr << e.what() << std::endl;
			return "";
		}
	}
	return "";
}
