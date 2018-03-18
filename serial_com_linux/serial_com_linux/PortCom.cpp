/**
* This file contains the implementation of the PortCom class methods
* as well as the declaration of some globals and static members.
*
* @author trevmo
*/

#include "PortCom.h"
#include <thread>
#include <iostream>

using namespace std;

const int MAX_CMD_LEN = 10;
SerialPort PortCom::port;
bool PortCom::_continue;

/**
 * Initialize an instance of PortCom for the given serial port path.
 * @param path file path (Linux) to the serial port
 */
PortCom::PortCom(string path) {
	port = SerialPort(path);
	_continue = true;
}
/**
 * Unused deconstructor.
 */
PortCom::~PortCom() {

}
/**
 * Create a session to allow a user to send commands to the serial port
 * and receive responses back from the device under test (DUT).
 */
void PortCom::session() {
	//thread readThread(&SerialPort::read, ref(port));
	thread readThread(PortCom::receive);
	port.open(false);

	port.setBaudRate(19200);
	port.setParity(none);
	port.setDataBits(8);
	port.setFlowControl(false);

	readThread.detach();
	thread writeThread(PortCom::transmit);
	writeThread.join();
	//readThread.join();

	port.close();
}
/** 
 * While the flag is set, continue to look for responses from the DUT.
 * Note: this method is designed to be run on a separate thread.
 */
void PortCom::receive() {
	while (_continue) {
		port.read();
	}
}
/**
 * While the flag is set and there is no response incoming from the DUT,
 * allow the user to input a command and set it out through the port.
 * Note: this method runs on the primary thread.
 */
void PortCom::transmit() {
	char *cmd = new char[MAX_CMD_LEN];
	while (_continue)
	{
		std::cin >> cmd;
		if (strcmp(cmd, "quit") != 0)
		{
			int cmdLen = strlen(cmd);
			cmd[cmdLen] = '\r';
			cmd[cmdLen + 1] = '\0';
			port.write(cmd, cmdLen + 2);
		}
		else
			_continue = false;
	}
}