#include "at_bound_checker.h"

// checks whether the input ranges are valid for the AT command type
// Returns true if the value is read only
// If the command it unknown it will return false

bool atCommandSsWithinBounds(enum ATCOMMAND command, uint16_t input) {
    switch (command) {
        case PV:
            return true;
        case AM:
            return true;
        case APV2:
            return (0 <= input && input <= 2);
        case AT:
            return true;
        case BD:
            return (0 <= input && input <= 8);
        case BR:
            return (0 <= input && input <= 1);
        case BT:
            return (0 <= input && input <= 0xFFFF);
        case CC:
            return (0x20 <= input && input <= 0x7F);
        case CD:
            return (0 <= input && input <= 4);
        case CF:
            return (0 <= input && input <= 2);
        case CN:
            return true;
        case CS:
            return (0 <= input && input <= 4);
        case CT:
            return (2 <= input && input <= 0xFFFF);
        case DB:
            return true;
        case DT:
            return (0 <= input && input <= 0xFFFF);
        case E0:
            return true;
        case E1:
            return true;
        case ER:
            return (0 <= input && input <= 0xFFFF);
        case FH:
            return true;
        case FL:
            return (0 <= input && input <= 0xFFFF);
        case FS:
            return (0 <= input && input <= 9);
        case FT:
            return true;
        case GD:
            return (0 <= input && input <= 0xFFFF);
        case HP:
            return (0 <= input && input <= 9);
        case HT:
            return (0 <= input && input <= 0xFFFF);
        case HV:
            return true;
        case ID:
            return (0x11 <= input && input <= 0x7FFF);
        case KY:
            return true;
        case LH:
            return (0 <= input && input <= 0xFF);
        case MDV2:
            return (0 <= input && input <= 6);
        case MK:
            return (0 <= input && input <= 0xFFFF);
        case MT:
            return (0 <= input && input <= 0xFF);
        case MY:
            return (0 <= input && input <= 0xFFFF);
        case NB:
            return (0 <= input && input <= 4);
        case PBV2:
            return (0 <= input && input <= 0xFFFF);
        case PDV2:
            return (0 <= input && input <= 0xFFFF);
        case PEV2:
            return (0 <= input && input <= 0xFFFF);
        case PK:
            return (0 <= input && input <= 0x800);
        case PL:
            return (0 <= input && input <= 4);
        case PW:
            return (0 <= input && input <= 1);
        case RB:
            return true;
        case RC:
            return true;
        case RE:
            return true;
        case RM:
            return true;
        case RN:
            return (0 <= input && input <= 0xFF);
        case RO:
            return (0 <= input && input <= 0xFFFF);
        case RP:
            return (0 <= input && input <= 0xFF);
        case RR:
            return (0 <= input && input <= 0xFF);
        case RT:
            return (0 <= input && input <= 2);
        case SB:
            return (0 <= input && input <= 1);
        case SH:
            return true;
        case SL:
            return true;
        case SM:
            return (0 <= input && input <= 8) && (input != 3);
        case ST:
            return (0 <= input && input <= 0x7FFF);
        case TP:
            return true;
        case TR:
            return true;
        case TT:
            return (0 <= input && input <= 0xFFFF);
        case TX:
            return (0 <= input && input <= 1);
        case VL:
            return true;
        case VR:
            return true;
        case WA:
            return true;
        case WN:
            return true;
        case WR:
            return true;
        case WS:
            return true;
        default:
            return false;
    }
}