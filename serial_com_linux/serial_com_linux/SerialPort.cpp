/**
 * This file contains the implementations of the SerialPort class methods.
 *
 * @author trevmo
 */

#include "SerialPort.h"

/**
 * Construct a new instance of SerialPort.
 * @param portName file path to the Linux serial port
 * @return default SerialPort object
 */
SerialPort::SerialPort(string portName) {
	this->portName = portName;
	setBaudRate(19200);
	setParity(none);
	setDataBits(8);
}
/**
 * Unused deconstructor.
 */
SerialPort::~SerialPort() {

}
/**
 * Open the serial port and grab a file descriptor for read/write
 * operations.
 * @param blocking indicate whether to open a blocking line or not
 * @return boolean indicating success or failure of open operation
 */
bool SerialPort::open(bool blocking) {
	fileDescriptor = ::open(portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	if (fileDescriptor == -1) {
		cerr << "Failed to open port.\n";
		return false;
	}
	else if (blocking) {
		fcntl(fileDescriptor, F_SETFL, 0);
		return true;
	}
	else {
		fcntl(fileDescriptor, F_SETFL, FNDELAY);
		return true;
	}
}
/**
 * Close the serial port.
 */
void SerialPort::close() {
	::close(fileDescriptor);
}
/**
 * Write a message out to the serial port.
 * @param buffer pointer to the message
 * @param numBytes number of bytes in the message
 */
void SerialPort::write(char *buffer, int numBytes) {
	int numWritten = ::write(fileDescriptor, buffer, numBytes);
	if (numWritten < 0)
		cerr << "Failed to write the buffer to the port.\n";
}
/**
 * Read a specified number of bytes from the serial port.
 * @param numBytes number of bytes to read
 * @return buffer of read bytes
 */
char* SerialPort::read(int numBytes) {
	char *buffer = new char[numBytes];
	int numRead = ::read(fileDescriptor, buffer, numBytes);
	if (numRead < 0) {
		cerr << "Failed to read data from port.\n";
		return NULL;
	}
	return buffer;
}
/**
 * Read an indefinite number of characters from the port.
 * TODO: finish/debug this method
 * @return string containing the entire message
 */
string SerialPort::read() {
	string msg = "";
	char *c = new char;
	int numRead = 0;
	while ((numRead = ::read(fileDescriptor, c, 1)) > 0)
		msg.append(c);
	return msg;
}
/**
 * Translate the integer into the corresponding baud rate and
 * set the port's rate accordingly.
 * @param rate baud rate as an integer
 */
void SerialPort::setBaudRate(int rate) {
	tcgetattr(fileDescriptor, &options);
	baudRate = convertRate(rate);
	cfsetispeed(&options, rate);
	cfsetospeed(&options, rate);
	options.c_cflag |= (CLOCAL | CREAD);
	tcsetattr(fileDescriptor, TCSANOW, &options);
}
/**
 * Modify the port's flags according to the specified parity option
 * @param parity {none, even, odd, space}
 */
void SerialPort::setParity(Parity parity) {
	switch (parity) {
	case none:
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;
		break;
	case even:
		options.c_cflag |= PARENB;
		options.c_cflag &= ~PARODD;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS7;
		break;
	case odd:
		options.c_cflag |= PARENB;
		options.c_cflag |= PARODD;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS7;
		break;
	case space:
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;
		break;
	}
	tcsetattr(fileDescriptor, TCSANOW, &options);
}
/**
 * Set the port to use the specified number of data bits.
 * @param dataBits number of bits as an integer
 */
void SerialPort::setDataBits(int dataBits) {
	//TODO: allow for data bit size 5-8
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

	tcsetattr(fileDescriptor, TCSANOW, &options);
}
/**
 * Convert the integer to the corresponding baud rate value.
 * TODO: expand to handle all common baud rates
 * @param rate baud rate as an integer
 * @return baud rate as speed_t
 */
speed_t SerialPort::convertRate(int rate) {
	switch (rate) {
	case 9600:
		return B9600;
	case 19200:
		return B19200;
	case 115200:
		return B115200;
	default:
		return B19200;
	}
}
