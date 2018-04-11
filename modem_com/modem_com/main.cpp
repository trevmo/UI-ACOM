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
	bool success = controller.initPort(ModemCom::PORT_NAME, ModemCom::SETTINGS);
	if (success)
		controller.automatedSession("/home/acom/logging/log.txt");
	
	return 0;
}