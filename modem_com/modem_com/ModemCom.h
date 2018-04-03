/**
 * This file contains the class definition of ModemCom as well as supporting structures.
 * ModemCom is designed around the boost library and is intended for use in communicating
 * with an Iridium modem.
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
 * ModemCom is designed for enabling communications with an Iridium modem over
 * an RS232 serial port. The modem expects and responds to AT commands.
 */
class ModemCom
{
private:
	static const PortSettings SETTINGS;
	static const int MAX_READ;

	asio::io_service service;
	static SerialPortPointer port;

	static bool _continue;

	static void transmit();
	static void send(std::string message);
	static void receive();

public:
	ModemCom();
	~ModemCom();

	bool initPort(std::string portName);
	void session();
	void automatedSession(std::string filename, int secondsDelay);
};

