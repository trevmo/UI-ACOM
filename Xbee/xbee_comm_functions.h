#ifndef XBEE_XBEE_COMM_FUNCTIONS_H
#define XBEE_XBEE_COMM_FUNCTIONS_H

#include "at_command_helper.h"
#include "uart_comm_library.h"
#include "at_bound_checker.h"
// Basic pass through function that sends a single byte of data
bool sendData(TerminalStructure *UARTPort, uint8_t data);

// This function sends an AT command to the Xbee module.
bool sendData(TerminalStructure *UARTPort, uint8_t *data, uint32_t length);

// This is a basic pass through function for sending a series of data bytes.
bool enterCommandMode(TerminalStructure *UARTPort);

// This function tells the module to enter into command mode so it will accept AT commands.
bool sendCommand(TerminalStructure *UARTPort, enum ATCOMMAND command, uint16_t input);

#endif //XBEE_XBEE_COMM_FUNCTIONS_H
