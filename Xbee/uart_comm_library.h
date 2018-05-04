#ifndef XBEE_UART_COMM_LIBRARY_H
#define XBEE_UART_COMM_LIBRARY_H

#include <stdint.h>
#include <signal.h>
#include <termios.h> // Linux terminal library, will not compile outside linux

// Prototype definition for callback function
typedef void (*callback_t)(int id, uint8_t *buffer, int len);

// Terminal structure that has self contained
typedef struct TerminalStructure {

    uint8_t buffer[255]; // Byte buffer
    int bufferDataLength = 0;
    int fileDescriptor; // Terminal file descriptor

    struct termios tio; // terminal struct
    struct termios oldtio; // previous terminal struct

    callback_t callBackFunction; // saved callback function
    int id;

    struct TerminalStructure *next;
} TerminalStructure;

typedef enum {
    NONE,
    ERROR_NOTSTARTED,   // Not initialized
    ERROR_NULLPOINTER,  // unexpected NULL pointer
    ERROR_MEMORY,       // not enough memory
    ERROR_OPEN
} error_t;

// get message based on error code.
const std::string getErrorMessage();
// get error message code.
int getErrorCode();
// This must run before you use the UART terminal.
void startComm();
// Run this to finish up UART Terminal
void stop();


// Opens the UART comm using initial settings provided
TerminalStructure *openPort(const char *portName, callback_t callbackFunction, int id,
            int baud, int numDataBits, int parity, int stop);

// Close the port when you're finished using it
void closePort(TerminalStructure *serial);

// Reconfigure a port once you've already instantiated it.
void reconfigurePort(TerminalStructure *serial, int baud, int numDataBits, int parity, int stop);

// send a single byte of data throug UART
void sendByte(TerminalStructure *serial, uint8_t data);

// Send a series of bytes through the UART
void sendBytes(TerminalStructure *serial, uint8_t *data, int datalen);

// Set the timeout for responses (important for blocking calls)
void settimeout(TerminalStructure *serial, int timeout);

// Get a single byte response
int getByte(TerminalStructure *serial);

// Get multiple byte response.
int getBytes(TerminalStructure *serial, uint8_t *buffer, int size);

#endif //XBEE_UART_COMM_LIBRARY_H
