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

using namespace boost;

/**
 * ModemCom is designed for enabling communications with an Iridium modem over
 * an RS232 serial port. The modem expects and responds to AT commands.
 */
class ModemCom : public PortCom
{
private:
	static const PortSettings SETTINGS;

	static void transmit();
	static void send(std::string message);
	static void receive();

public:
	ModemCom() {}
	~ModemCom() {}

	void session();
	void automatedSession(std::string filename, int secondsDelay);
};

