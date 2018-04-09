/**
* This file tests and utilizes the ModemCom class for communicating with an Iridium modem.
*
* @author trevmo
*/

#include <cstdio>
#include "ModemCom.h"

int main()
{
	ModemCom controller;
	bool success = controller.initPort("/dev/ttyUSB1", ModemCom::SETTINGS);
	if (success)
		controller.automatedSession("/home/acom/logging/log.txt", 3);
		//controller.session();
	
	return 0;
}