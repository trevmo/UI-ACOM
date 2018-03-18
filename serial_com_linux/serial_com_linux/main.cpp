/**
 * This file is used for testing and utilizing the SerialPort class.
 *
 * @author trevmo
 */

#include "SerialPort.h"
#include "PortCom.h"
#include <iostream>

void session(SerialPort port);

const int MAX_CMD_LEN = 10;

int main()
{
	/*SerialPort port("/dev/ttyUSB0");
	bool success = port.open(true);
	if (success) {
		session(port);
	}*/
	PortCom pcom("/dev/ttyUSB0");
	pcom.session();

    return 0;
}

void session(SerialPort port) {
	char *cmd = new char[MAX_CMD_LEN];
	std::cin >> cmd;
	while (strcmp(cmd, "quit") != 0)
	{
		int cmdLen = strlen(cmd);
		cmd[cmdLen] = '\r';
		cmd[cmdLen+1] = '\0';
		port.write(cmd, cmdLen + 2);
		//std::cout << port.read();
		std::cin >> cmd;
	}
	port.close();
}