#include "uart_comm_library.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string>

// flags
static int SIGNAL = 0;
static int started = 0;
static error_t error = NONE;

// Lowlevel interfaces
static struct sigaction sa;
static struct sigaction oldsa;

// Actual Port.
static TerminalStructure *head = 0;

// Error codes when initializing UART serial
static const std::string errors[] = {
        "NONE",
        "not started",
        "null pointer",
        "out of memory",
};

// This handles data when it arrives from Xbee Module
static void handler(int signo, siginfo_t *info, void *ignored);

// Get Error message
const std::string getErrorMessage() { return errors[error]; }
int getErrorCode() { return error; }

// IMPORTANT: Must run first
// This function starts the actual UART comm and does some basic setup.
void startComm() {
    // Don'TerminalStructure restart
    if (started) {
        return;
    }

    int sig = SIGRTMIN;
    do {

        // get old sigaction
        sigaction(sig, 0, &oldsa);

        // If starting sigaction for the first time
        if (oldsa.sa_handler == 0) {
            SIGNAL = sig;
            sa.sa_sigaction = handler;
            sa.sa_flags = SA_SIGINFO;
            sa.sa_restorer = NULL;
            sigemptyset(&sa.sa_mask);
            sigaction(SIGNAL, &sa, 0);

            started = 1;
            error = NONE;
            return;
        } else {
            sigaction(SIGNAL, &oldsa, 0);
        }
        // next signal
        sig++;
    } while (sig <= SIGRTMAX);

}

// Kill the serial comm
void stop() {
    if (!started)
        return;

    while (head)
        closePort(head);

    sigaction(SIGNAL, &oldsa, NULL);

    started = 0;
    error = NONE;
}

TerminalStructure * openPort(const char *portName, callback_t callbackFunction, int id, int baud, int numDataBits, int parity, int stop) {
    TerminalStructure *serial;

    if (!started) {
        error = ERROR_NOTSTARTED;
        return NULL;
    }

    // Initialize and zero out.
    serial = calloc(1, sizeof(TerminalStructure));

    // If allocation failed
    if (!serial) {
        error = ERROR_MEMORY;
        return 0;
    }

    // Initialize callback function capabilities
    if (callbackFunction) {
        serial->fileDescriptor = openPort(portName, O_RDWR | O_NOCTTY | O_NONBLOCK);
        fcntl(serial->fileDescriptor, F_SETSIG, SIGNAL);
        fcntl(serial->fileDescriptor, F_SETOWN, getpid());
        fcntl(serial->fileDescriptor, F_SETFL, O_ASYNC | O_NONBLOCK);
    } else {
        serial->fileDescriptor = openPort(portName, O_RDWR | O_NOCTTY);
    }

    // If we couldn'TerminalStructure open the comm port.
    if (serial->fileDescriptor == -1) {
        error = ERROR_OPEN;
        free(serial);
        return NULL;
    }

    // Get comm port attributes.
    tcgetattr(serial->fileDescriptor, &(serial->oldtio));
    // Configure the port.
    reconfigurePort(serial, baud, parity, numDataBits, stop);
    serial->id = id;
    serial->callBackFunction = callbackFunction;

    serial->next = head;
    head = serial;

    error = NONE;

    return serial;
}

// Close the port completely
// You should call this in order to handle properly closing the UART port
void closePort(TerminalStructure *serial) {
    TerminalStructure *cur;

    if (!started) {
        error = ERROR_NOTSTARTED;
        return;
    }

    if (!serial) {
        error = ERROR_NULLPOINTER;
        return;
    }

    // Make sure nothing is left in the buffer.
    tcflush(serial->fileDescriptor, TCOFLUSH);
    tcflush(serial->fileDescriptor, TCIFLUSH);

    tcsetattr(serial->fileDescriptor, TCSANOW, &(serial->oldtio));

    close(serial->fileDescriptor);

    if (head == serial) {
        head = serial->next;
        free(serial);
        error = NONE;
        return;
    }

    for (cur = head; cur; cur = cur->next) {
        if (cur->next == serial) {
            cur->next = serial->next;
            free(serial);
            error = NONE;
            return;
        }
    }
    // Should not reach here.
}

// Either configure the port for the first time if called from within open
// or reconfigure the port that has already been opened.
void reconfigurePort(TerminalStructure *serial, int baud, int numDataBits, int parity, int stop) {
    tcflag_t baudrate;
    tcflag_t databits;
    tcflag_t stopbits;
    tcflag_t checkparity;

    if (!started) {
        error = ERROR_NOTSTARTED;
        return;
    }

    if (!serial) {
        error = ERROR_NULLPOINTER;
        return;
    }

    // Must designate a supported baudrate.
    switch (baud) {
        case 75:
            baudrate = B75;
            break;
        case 110:
            baudrate = B110;
            break;
        case 150:
            baudrate = B150;
            break;
        case 300:
            baudrate = B300;
            break;
        case 600:
            baudrate = B600;
            break;
        case 1200:
            baudrate = B1200;
            break;
        case 2400:
            baudrate = B2400;
            break;
        case 4800:
            baudrate = B4800;
            break;
        case 9600:
            baudrate = B9600;
            break;
        case 19200:
            baudrate = B19200;
            break;
        case 38400:
            baudrate = B38400;
            break;
        case 57600:
            baudrate = B57600;
            break;
        case 115200:
            baudrate = B115200;
            break;
        default:
            baudrate = B9600;
    }

    // Set to the proper number of data bits
    switch (numDataBits) {
        case 7:
            databits = CS7;
            break;
        case 8:
            databits = CS8;
            break;
        default:
            databits = CS8;
    }

    // Change the parity
    switch (parity) {
        case 0:
            checkparity = 0;
            break;
        case 1:   //odd
            checkparity = PARENB | PARODD;
            break;
        case 2:
            checkparity = PARENB;
            break;
        default:
            checkparity = 0;
    }

    // Set whether a stop bit is used
    switch (stop) {
        case 1:
            stopbits = 0;
            break;
        case 2:
            stopbits = CSTOPB;
            break;
        default:
            stopbits = 0;
    }

    // Set the flags based on the settings determined above
    serial->tio.c_cflag = baudrate | databits | checkparity | stopbits | CLOCAL | CREAD;
    serial->tio.c_iflag = IGNPAR;
    serial->tio.c_oflag = 0;
    serial->tio.c_lflag = 0;
    serial->tio.c_cc[VMIN] = 1;
    serial->tio.c_cc[VTIME] = 0;

    tcflush(serial->fileDescriptor, TCOFLUSH);
    tcflush(serial->fileDescriptor, TCIFLUSH);

    tcsetattr(serial->fileDescriptor, TCSANOW, &(serial->tio));

    error = NONE;
}

// Set how long we should wait for a message
void settimeout(TerminalStructure *serial, int timeout) {
    if (!started) {
        error = ERROR_NOTSTARTED;
        return;
    }

    if (!serial) {
        error = ERROR_NULLPOINTER;
        return;
    }

    serial->tio.c_cc[VTIME] = timeout;
    tcsetattr(serial->fileDescriptor, TCSANOW, &(serial->tio));
    error = NONE;
}


// Send a single byte.
void sendByte(TerminalStructure *serial, uint8_t data) {
    if (!started) {
        error = ERROR_NOTSTARTED;
        return;
    }

    if (!serial) {
        error = ERROR_NULLPOINTER;
        return;
    }

    write(serial->fileDescriptor, &data, 1);
}

// Send mutliple bytes
void sendBytes(TerminalStructure *serial, uint8_t *data, int dataLength) {
    if (!started) {
        error = ERROR_NOTSTARTED;
        return;
    }

    if (!serial) {
        error = ERROR_NULLPOINTER;
        return;
    }

    write(serial->fileDescriptor, data, dataLength);
}

int getByte(TerminalStructure *serial) {
    int error;
    uint8_t byte;

    error = read(serial->fileDescriptor, &byte, sizeof(byte));
    if (error != 0)
        return -1;

    return byte;
}

// Force a read, this function should block, beware.
int getBytes(TerminalStructure *serial, uint8_t *buffer, int size) {
    return read(serial->fileDescriptor, buffer, size);
}

// This handles the callback function that is called when the buffer recieves data from
// the Xbee module. You should generally have one of these defined unless you want to ignore
// all data.
void handler(int signo, siginfo_t *info, void *ignored) {
    TerminalStructure *cur;
    int n;

    if (info->si_code == POLL_IN) {
        for (cur = head; cur; cur = cur->next) {
            if (cur->fileDescriptor == info->si_fd) {

                n = read(cur->fileDescriptor, cur->buffer, 255);
                if ((n > 0) && (cur->callBackFunction))
                    cur->callBackFunction(cur->id, cur->buffer, n);

                return;
            }
        }
    }
}


