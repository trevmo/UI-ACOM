/**
* This file contains the class definition of GPSReader. It is a child class of PortCom.
* GPSReader is designed for reading NMEA sentences from a GPS receiver through a serial
* port. It was tested with a GlobalSat BU-353S4 USB Receiver.
*
* Note: The GPS receiver must be configured prior to use with this class. It must be setup
* to only send GGA sentences following the NMEA standard. Download SIRFdemo.exe from here
* (http://www.stargps.ca/downloads.htm). Once downloaded, open the program, go to
* Action->Switch to NMEA Protocol... and configure through the dialog box.
*
* References:
* - NMEA Standard (http://www.gpsinformation.org/dale/nmea.htm#GGA)
* - BU-353S4 (http://usglobalsat.com/store/p-733-bu-353-s4.aspx)
*
* Dependencies:
* - Boost (www.boost.org)
* - PortCom.h/cpp
*
* @author trevmo
*/

#pragma once
#include "PortCom.h"
#include <boost/algorithm/string.hpp>

using namespace boost;
/**
 * GPSReader is designed for reading location and elevation information from a
 * GPS receiver over a serial interface.
 */
class GPSReader :
	public PortCom
{
public:
	static const PortSettings SETTINGS;

	GPSReader() { }
	~GPSReader();

	std::string read();
};

