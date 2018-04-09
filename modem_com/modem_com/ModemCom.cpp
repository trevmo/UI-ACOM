/**
 * This file contains the implementations of the methods of ModemCom as well as
 * initialization of supporting data structures.
 *
 * @author trevmo
 */

#include "ModemCom.h"

/**
 * Initialize a static, constant structure holding all of the settings for the serial
 * port connected to the Iridium modem.
 */
const PortSettings ModemCom::SETTINGS = {
	asio::serial_port_base::baud_rate(19200),
	asio::serial_port_base::parity(asio::serial_port_base::parity::none),
	asio::serial_port_base::character_size(8),
	asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one),
	asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none)
};
SerialPortPointer ModemCom::modemPort;

/**
* Initialize a new instance of PortCom, particularly its instance of a GPSReader.
*/
ModemCom::ModemCom()
{
	modemPort = PortCom::port;
	gpsReader.initPort("/dev/ttyUSB0", GPSReader::SETTINGS);
}
/**
* Close the port upon end of use.
*/
ModemCom::~ModemCom()
{
	port->close();
}
/**
 * Start a session allowing a user to interface with the modem by
 * entering commands and receiving its response(s).
 */
void ModemCom::session()
{
	std::thread receiveThread(ModemCom::receive);
	std::thread transmitThread(ModemCom::transmit);

	receiveThread.detach();
	transmitThread.join();
}
/**
 * Start an automated session where commands are sent to the modem in
 * delayed intervals and the responses are stored in a log file.
 * @param filename path to the log file
 * @param secondsDelay number of seconds to delay between transmissions
 */
void ModemCom::automatedSession(std::string filename, int secondsDelay)
{
	std::ofstream *logFile = new std::ofstream;
	logFile->open(filename, std::fstream::out);

	std::string gpsInfo = "";
	std::thread receiveThread(ModemCom::receive);
	if (logFile->is_open())
	{
		//save the read buffer for restoration later
		std::streambuf *coutBuf = std::cout.rdbuf();
		//redirect cout to the logFile
		std::cout.rdbuf(logFile->rdbuf());

		receiveThread.detach();
		//TODO: adapt to send commands for test launch at larger interval
		for (int i = 0; i < 2; i++)
		{
			gpsInfo = gpsReader.read();
			std::cout << "Sent: at+sbdwt=\"" << gpsInfo << "\"" << std::endl;
			send("at+sbdwt=\"" + gpsInfo + "\"");
			//send("at+sbdi");
			std::this_thread::sleep_for(std::chrono::seconds(secondsDelay));
		}
		//signal the read thread to stop running
		_continue = false;
		std::cout.rdbuf(coutBuf);
		logFile->close();
	}
}
/**
 * Accept input from the user and send the command to the modem.
 * Note: This method is static and designed to be run in its own thread.
 */
void ModemCom::transmit()
{
	while (_continue)
	{
		if (modemPort == NULL || !modemPort->is_open())
			return;

		std::string command;
		std::cin >> command;

		if (command != "quit")
			send(command);
		else
			_continue = false;
	}
}
/**
 * Send the specified message over the port.
 * @param message AT command
 */
void ModemCom::send(std::string message)
{
	if (modemPort == NULL || !modemPort->is_open())
		return;

	//IMPORTANT: be sure to append a carriage return to the command before sending
	//to ensure that the full response is received from the modem
	message.append("\r");
	asio::write(*modemPort, asio::buffer(message, message.length()));
}
/**
 * Continually try to receive responses from the modem through the port.
 * Note: This method is static and designed to be run in its own thread.
 */
void ModemCom::receive()
{
	while (_continue)
	{
		if (modemPort == NULL || !modemPort->is_open())
			return;
	
		try
		{
			char *msgReceived = new char[MAX_READ];
			int numRead = modemPort->read_some(asio::buffer(msgReceived, MAX_READ));
			if (numRead > 0)
				for (int i = 0; i < numRead; i++)
					std::cout << msgReceived[i];
			delete[] msgReceived;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception occurred while reading from port.\n";
			std::cerr << e.what() << std::endl;
		}
		
	}
}

