#ifndef XBEE_AT_COMMAND_HELPER_H
#define XBEE_AT_COMMAND_HELPER_H

#include <string>

// List of AT commands that have support with this module.
// Most AT commands have a hex code, however ones that don'TerminalStructure have a
// proper code according to documentation have been assigned a free one.
enum ATCOMMAND {
    PV = 0x3B,
    AM = 0x40,
    APV2 = 0x30,
    AT = 0x05,
    BD = 0x15,
    BR = 0x39,
    BT = 0x04,
    CC = 0x13,
    CD = 0x28,
    CF = 0x32,
    CN = 0x09,
    CS = 0x1F,
    CT = 0x06,
    DB = 0x36,
    DT = 0x00,
    E0 = 0x0A,
    E1 = 0x0B,
    ER = 0x0F,
    FH = 0x0D,
    FL = 0x07,
    FS = 0x3E,
    FT = 0x24,
    GD = 0x10,
    HP = 0x11,
    HT = 0x03,
    HV = 0x33,
    ID = 0x27,
    KY = 0x3C,
    LH = 0x0C,
    MDV2 = 0x31,
    MK = 0x12,
    MT = 0x3D,
    MY = 0x2A,
    NB = 0x23,
    PBV2 = 0x45,
    PDV2 = 0x47,
    PEV2 = 0x46,
    PK = 0x29,
    PL = 0x3A,
    PW = 0x1D,
    RB = 0x20,
    RC = 0x34,
    RE = 0x0E,
    RM = 0x35,
    RN = 0x19,
    RO = 0x21,
    RP = 0x22,
    RR = 0x18,
    RT = 0x16,
    SB = 0x37,
    SH = 0x25,
    SL = 0x26,
    SM = 0x01,
    ST = 0x02,
    TP = 0x38,
    TR = 0x1B,
    TT = 0x1A,
    TX = 0x3F,
    VL = 0x41,
    VR = 0x14,
    WA = 0x42,
    WN = 0x43,
    WR = 0x08,
    WS = 0x44,
};

// Simple function that returns the string description of an AT command.
// Helpful for debugging purposes.
std::string getATCommandDescription(enum ATCOMMAND command) {
    switch (command) {
        case PV:
            return "Board Voltage";
        case AM:
            return "Auto-set MY";
        case APV2:
            return "API Enable";
        case AT:
            return "Guard Time After";
        case BD:
            return "Interface Data Rate";
        case BR:
            return "RF Data Rate";
        case BT:
            return "Guard Time Before";
        case CC:
            return "Command Sequence Character";
        case CD:
            return "GPO2 Configuration";
        case CF:
            return "Number Base";
        case CN:
            return "Exit Command Mode";
        case CS:
            return "GPO1 Configuration";
        case CT:
            return "Command Mode Timeout";
        case DB:
            return "Received Signal Strength";
        case DT:
            return "Destination Address";
        case E0:
            return "Echo Off";
        case E1:
            return "Echo On";
        case ER:
            return "Receive Error Count";
        case FH:
            return "Force Wake-up Initializer";
        case FL:
            return "Software Flow Control";
        case FS:
            return "Forced Sync Time";
        case FT:
            return "Flow Control Threshold";
        case GD:
            return "Receive Good Count";
        case HP:
            return "Hopping Channel";
        case HT:
            return "Time before Wake-up Initializer";
        case HV:
            return "Hardware Version";
        case ID:
            return "Modem VID";
        case KY:
            return "AES Encryption Key";
        case LH:
            return "Wake-up Initializer Timer";
        case MDV2:
            return "RF Mode";
        case MK:
            return "Address Mask";
        case MT:
            return "Multi-Transmit";
        case MY:
            return "Source Address";
        case NB:
            return "Parity Serial Interfacing";
        case PBV2:
            return "Polling Begin Address";
        case PDV2:
            return "Minimum Polling Delay";
        case PEV2:
            return "Polling End Address";
        case PK:
            return "Maximum RF Packet Size";
        case PL:
            return "TX Power Level";
        case PW:
            return "Pin Wake-up";
        case RB:
            return "Packetization Threshold";
        case RC:
            return "Ambient Power";
        case RE:
            return "Restore Defaults";
        case RM:
            return "Ambient Power All Channels";
        case RN:
            return "Delay Slots";
        case RO:
            return "Packetization Timeout";
        case RP:
            return "RSSI PWM Timer";
        case RR:
            return "Retries";
        case RT:
            return "GPI1 Configuration";
        case SB:
            return "Stop Bits";
        case SH:
            return "Serial Number High";
        case SL:
            return "Serial Number Low";
        case SM:
            return "Sleep Mode";
        case ST:
            return "Time before Sleep";
        case TP:
            return "Board Temperature";
        case TR:
            return "Delivery Failure Count";
        case TT:
            return "Streaming Limit";
        case TX:
            return "Transmit Only";
        case VL:
            return "Firmware Version verbose";
        case VR:
            return "Firmware Version";
        case WA:
            return "Active Warning Numbers";
        case WN:
            return "Warning Data";
        case WR:
            return "Write";
        case WS:
            return "Sticky Warning Numbers";
        default:
            return "Uknown Command";
    }
}

#endif //XBEE_AT_COMMAND_HELPER_H
