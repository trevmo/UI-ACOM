/**
 * This file contains the class definition of ModemCom. It is a child class of PortCom.
 * ModemCom is designed around the boost library and is intended for use in communicating
 * with an Iridium modem.
 *
 * Dependencies:
 * - Boost (www.boost.org)
 * - PortCom.h/cpp
 *
 * @author trevmo
 */

#pragma once
#include "PortCom.h"
#include "GPSReader.h"

using namespace boost;

/**
 * ModemCom is designed for enabling communications with an Iridium modem over
 * an RS232 serial port. The modem expects and responds to AT commands.
 */
class ModemCom : 
	public PortCom
{
private:
	// Since ModemCom's transmit/receive methods are used as separate threads, ModemCom
	// needs a separate static reference to the underlying port from PortCom. If you
	// set the port in PortCom to be static, then all derived classes will share the same
	// static instance at runtime.
	static SerialPortPointer modemPort;
	GPSReader gpsReader;

	static void transmit();
	static void send(std::string message);
	static void receive();

public:
	static const PortSettings SETTINGS;

	ModemCom();
	~ModemCom();

	void session();
	void automatedSession(std::string filename, int secondsDelay);
};

