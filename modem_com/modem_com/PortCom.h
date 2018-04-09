/**
 * This file contains the class definition of PortCom and supporting data structures.
 * PortCom can be used as a parent/super class for any classes interfacing with a
 * serial-based device.
 *
 * Dependencies:
 * - Boost (www.boost.org)
 *
 * @author trevmo
 */

#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <fstream>
#include <chrono>
#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>

using namespace boost;


/**
 * PortSettings is a helper structure for storing serial port settings
 * used in ModemCom.
 */
struct PortSettings
{
	asio::serial_port_base::baud_rate baudRate;
	asio::serial_port_base::parity parity;
	asio::serial_port_base::character_size dataBits;
	asio::serial_port_base::stop_bits stopBits;
	asio::serial_port_base::flow_control flowControl;
};
typedef struct PortSettings PortSettings;

// Define a wrapper to a shared pointer of serial port
// Note: using a regular pointer results in an exception when opening the port
typedef shared_ptr<asio::serial_port> SerialPortPointer;

/**
 * PortCom is designed as a parent class for enabling communications over
 * an RS232 serial port. It can be inherited for use with more specific serial applications
 * or devices.
 */
class PortCom
{
protected:
	static const int MAX_READ;

	asio::io_service service;
	SerialPortPointer port;

	static bool _continue;
public:
	PortCom();
	~PortCom();

	bool initPort(std::string portName, PortSettings settings);
};

