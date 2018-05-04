#ifndef XBEE_AT_BOUND_CHECKER_H
#define XBEE_AT_BOUND_CHECKER_H

#include "at_command_helper.h"

// FUTURE WORK: Add more functions for packet error checking.

// checks whether the input ranges are valid for the AT command type.
bool isWithinBounds(enum ATCOMMAND command, uint16_t input);

#endif //XBEE_AT_BOUND_CHECKER_H
