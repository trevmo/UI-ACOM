/**
* This file contains the definition of the PortCom class.
*
* @author trevmo
*/
#pragma once
#include "SerialPort.h"

/**
 * PortCom utilizes the SerialPort class to establish a user-driven session
 * of serial communications.
 */
class PortCom
{
public:
	PortCom(string path);
	~PortCom();

	void session();
private:
	static SerialPort port;
	static bool _continue;

	static void receive();
	static void transmit();
};

