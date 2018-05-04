#include "xbee_comm_functions.h"

// Basic pass through function that sends a single byte of data
bool sendData(TerminalStructure *UARTPort, uint8_t data) {
    sendByte(UARTPort, data);
    return true;
}

// This function sends an AT command to the Xbee module.
// It first checks to make sure that if the input command takes in a value it
// fits within the input interval for that command.
bool sendCommand(TerminalStructure *UARTPort, enum ATCOMMAND command, uint16_t input) {
    if (!isWithinBounds(command, input))
        return false;
    uint8_t *bytes = (uint8_t *) malloc(sizeof(uint8_t) * 3);
    *bytes = (uint8_t)command;
    *(bytes++) = input & 0xFF;
    if (input > 0xFF) {
        *(bytes+2) = input >> 8;
        sendBytes(UARTPort, bytes, 2);
    } else {
        sendBytes(UARTPort, bytes, 1);
    }
    return true;
}

// This is a basic pass through function for sending a series of data bytes.
bool sendData(TerminalStructure *UARTPort, uint8_t *data, uint32_t length) {
    sendBytes(UARTPort, data, length);
    return true;
}

// This function tells the module to enter into command mode so it will accept AT commands.
bool enterCommandMode(TerminalStructure *UARTPort) {
    uint8_t *bytes = (uint8_t *) malloc(sizeof(uint8_t) * 3);
    for (int i = 0; i < 3; ++i) {
        *(bytes + i) = '+';
    }
    sendBytes(UARTPort, bytes, 3);
    return false;
}
