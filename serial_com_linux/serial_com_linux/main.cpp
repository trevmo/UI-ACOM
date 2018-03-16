/**
 * This file is used for testing and utilizing the SerialPort class.
 *
 * @author trevmo
 */

#include "SerialPort.h"
#include <iostream>

int main()
{
	SerialPort port("/dev/ttyUSB0");
	bool success = port.open(true);
	if (success) {
		port.write("at\r", 3);
		std::cout << port.read(3);
		port.close();
	}
    return 0;
}