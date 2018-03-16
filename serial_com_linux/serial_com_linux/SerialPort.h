#pragma once
/**
 * This file contains the definition of the SerialPort class as well
 * as supporting data structures. SerialPort is designed for communications
 * on a Linux-based machine.
 * Reference: https://www.cmrr.umn.edu/~strupp/serial.html
 *
 * @author trevmo
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <string>
#include <iostream>

using namespace std;

enum Parity {
	none,
	even,
	odd,
	space
};
/**
 * This class provides simple communication capabilities with serial ports
 * on linux.
 */
class SerialPort {
private:
	string portName;
	int fileDescriptor;
	struct termios options;
	speed_t baudRate;
	Parity parity;
	int dataBits;

	speed_t convertRate(int rate);

public:
	SerialPort(string portName);
	~SerialPort();

	bool open(bool blocking);
	void close();
	void write(char *buffer, int numBytes);
	char *read(int numBytes);
	string read();

	void setBaudRate(int rate);
	void setParity(Parity parity);
	void setDataBits(int dataBits);
};
