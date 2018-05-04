#include <iostream>
#include "at_command_helper.h"
#include "at_bound_checker.h"
#include "uart_comm_library.h"
#include "xbee_comm_functions.h"

bool recievedFeedback = false;

bool responseReady = false;
static TerminalStructure *UARTPort;

// An example callback function that takes the data returned and fills a buffer.
static void callbackFunction(int id, uint8_t *buf, int length) {
    for (int i = 0; i < length; i++) {
        switch (buf[i]) {
            case '\0':  /* Ctrl-D */
                return;
            case '\r': /* replace \r with \n */
                buf[i] = '\n';
        }
        putchar(buf[i]);
    }
    responseReady = true;
    UARTPort->bufferDataLength = length;
    return;
}

// very simple example program to send single bytes through network
// You must force exit because there is no way to terminate the run loop.
// shows example of how to interact with device
int main() {
    int dataToSend = 0;
    startComm();
    UARTPort = openPort("/dev/ttyAMA0", callbackFunction, 0, 19200, 8, 0, 1);

    while (1) {
        std::cout << "Data to send: ";
        std::cin >> dataToSend;
        if (!sendData(UARTPort, dataToSend))
            exit(2);
        if(responseReady) {
            for (int i = 0; i < UARTPort->bufferDataLength; ++i) {
                std::cout << UARTPort->buffer[i] << " ";
            }
            std::cout << std::endl;
            responseReady = false;
        }
    }
}