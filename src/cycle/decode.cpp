#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <typeinfo>

#include "../defs.hpp"

#pragma once

// https://stackoverflow.com/questions/30443501/why-do-these-two-instructions-have-the-same-opcode

class DECODE {
    private:
        #define sec 0x55  // sections
        #define sub 0x11  // subelements

        static inline void Push(std::vector<u_char> &v, const u_char &s, uint8_t &arg, const uint8_t &count) {
            v.push_back(s);
            arg = count;
        }

        static inline void SinglePush(std::vector<u_char> &v, const u_char &s, std::vector<std::vector<u_char>> &instructions) {
            v.push_back(s);
            instructions.push_back(v);
        }

        static void CheckBits(const uint8_t &acceptablebits, const uint8_t &kernelbits, const uint8_t &hex) {
            if (acceptablebits != kernelbits) {
                std::stringstream error;
                error << hex << "is an invalid instruction in " << kernelbits << "-bit mode";
                OUTPUT::Error(error.str(), 0x12);
            }
        }

        static void CheckProc(const uint8_t &acceptableproc, const uint8_t &kernelproc) {
            if (acceptableproc > kernelproc) {
                std::stringstream error;
                std::string proc;
                switch (kernelproc) {
                    case 1: proc = "8086/8088"; break;
                    case 2: proc = "80186/80188"; break;
                    case 3: proc = "NEC-V"; break;
                    case 4: proc = "80286"; break;
                    case 5: proc = "80386"; break;
                    case 6: proc = "80486"; break;
                    case 7: proc = "Pentium"; break;
                    case 8: proc = "Pentium-MMX"; break;
                    case 9: proc = "AMD-K6"; break;
                    case 10: proc = "Pentium-Pro"; break;
                    case 11: proc = "Pentium-II"; break;
                    case 12: proc = "Intel-Itanium"; break;
                    case 13: proc = "Cyrix-Geode"; break;
                }
                error << "This instruction is not supported by the " << proc << " processor";
                OUTPUT::Error(error.str(), 0x13);
            }
        }

    public:
        static void Decode(const std::vector<u_char> &hexvector, std::vector<std::vector<u_char>> &resultvector, const uint8_t &bits, const uint8_t &processor) {
            std::vector<u_char> temp;
            uint8_t argcount = 0;

            for (size_t i = 0; i < hexvector.size(); ++i) {
                if (argcount > 0) {
                    temp.push_back(hexvector.at(i));
                    --argcount;
                    if (argcount == 0) {
                        resultvector.push_back(temp);
                        temp.clear();
                    }
                    continue;
                }
                temp.clear();

                u_char hex = hexvector.at(i);
                if (hex <= sec) {
                    CheckProc(1, processor); // add this for now as a parameter buffer
                    if (hex <= sub) {
                        switch (hex) {
                            case 0x00: Push(temp, hex, argcount, 1); continue;
                            case 0x01: // fallthrough (for now)
                            case 0x02:
                            case 0x03:
                            case 0x04: Push(temp, hex, argcount, 1); continue;
                            case 0x05: Push(temp, hex, argcount, 2); continue;
                            case 0x06: 
                            case 0x07:
                            case 0x08:
                            case 0x09:
                            case 0x0A:
                            case 0x0B:
                            case 0x0C:
                            case 0x0D:
                            case 0x0E: Push(temp, hex, argcount, 2); continue;
                            case 0x0F:
                            case 0x10:
                            case 0x11: break;
                        }
                    } else if (hex <= sub * 2) {
                        switch (hex) {
                            case 0x12:
                            case 0x13:
                            case 0x14:
                            case 0x15:
                            case 0x16:
                            case 0x17:
                            case 0x18:
                            case 0x19:
                            case 0x1A:
                            case 0x1B:
                            case 0x1C:
                            case 0x1D:
                            case 0x1E:
                            case 0x1F:
                            case 0x20:
                            case 0x21:
                            case 0x22: break;
                        }
                    } else if (hex <= sub * 3) {
                        switch (hex) {
                            case 0x23:
                            case 0x24:
                            case 0x25:
                            case 0x26:
                            case 0x27:
                            case 0x28:
                            case 0x29:
                            case 0x2A:
                            case 0x2B:
                            case 0x2C:
                            case 0x2D:
                            case 0x2E:
                            case 0x2F:
                            case 0x30:
                            case 0x31:
                            case 0x32:
                            case 0x33: break;
                        }
                    } else if (hex <= sub * 4) {
                        switch (hex) {
                            case 0x34:
                            case 0x35:
                            case 0x36:
                            case 0x37:
                            case 0x38:
                            case 0x39:
                            case 0x3A:
                            case 0x3B:
                            case 0x3C:
                            case 0x3D:
                            case 0x3E:
                            case 0x3F: break;
                            case 0x40: SinglePush(temp, hex, resultvector); continue;
                            case 0x41:
                            case 0x42:
                            case 0x43:
                            case 0x44: SinglePush(temp, hex, resultvector); continue;
                        }
                    } else if (hex <= sub * 5) {
                        switch (hex) {
                            case 0x45:
                            case 0x46:
                            case 0x47: SinglePush(temp, hex, resultvector); continue;
                            case 0x48:
                            case 0x49:
                            case 0x4A:
                            case 0x4B:
                            case 0x4C:
                            case 0x4D:
                            case 0x4E:
                            case 0x4F:
                            case 0x50:
                            case 0x51:
                            case 0x52:
                            case 0x53:
                            case 0x54:
                            case 0x55: break;
                        }
                    }
                } 
                else if (hex <= sec * 2) {
                    if (hex <= sub * 6) {
                        switch (hex) {
                            case 0x56:
                            case 0x57:
                            case 0x58:
                            case 0x59:
                            case 0x5A:
                            case 0x5B:
                            case 0x5C:
                            case 0x5D:
                            case 0x5E:
                            case 0x5F:
                            case 0x60:
                            case 0x61:
                            case 0x62:
                            case 0x63:
                            case 0x64:
                            case 0x65:
                            case 0x66: temp.push_back(0x66); continue;
                        }
                    } else if (hex <= sub * 7) {
                        switch (hex) {
                            case 0x67:
                            case 0x68:
                            case 0x69:
                            case 0x6A:
                            case 0x6B:
                            case 0x6C:
                            case 0x6D:
                            case 0x6E:
                            case 0x6F:
                            case 0x70:
                            case 0x71:
                            case 0x72:
                            case 0x73:
                            case 0x74:
                            case 0x75:
                            case 0x76: break;
                        }
                    } else if (hex <= sub * 8) {
                        switch (hex) {
                            case 0x77:
                            case 0x78:
                            case 0x79:
                            case 0x7A:
                            case 0x7B:
                            case 0x7C:
                            case 0x7D:
                            case 0x7E:
                            case 0x7F:
                            case 0x80:
                            case 0x81:
                            case 0x82:
                            case 0x83:
                            case 0x84:
                            case 0x85:
                            case 0x86:
                            case 0x87:
                            case 0x88: Push(temp, hex, argcount, 2); continue;
                        }
                    } else if (hex <= sub * 9) {
                        switch (hex) {
                            case 0x89: 
                            case 0x8A: 
                            case 0x8B: 
                            case 0x8C: Push(temp, hex, argcount, 2); continue;
                            case 0x8D: break;
                            case 0x8E: Push(temp, hex, argcount, 2); continue;
                            case 0x8F:
                            case 0x90:
                            case 0x91:
                            case 0x92:
                            case 0x93:
                            case 0x94:
                            case 0x95:
                            case 0x96:
                            case 0x97:
                            case 0x98:
                            case 0x99: break;
                        }
                    } else if (hex <= sub * 10) {
                        switch (hex) {
                            case 0x9A:
                            case 0x9B:
                            case 0x9C:
                            case 0x9D:
                            case 0x9E:
                            case 0x9F: break;
                            case 0xA0: 
                            case 0xA1: 
                            case 0xA2: 
                            case 0xA3: Push(temp, hex, argcount, 2); continue;
                            case 0xA4:
                            case 0xA5:
                            case 0xA6:
                            case 0xA7:
                            case 0xA8:
                            case 0xA9:
                            case 0xAA: break;
                        }
                    }
                } 
                else if (hex <= sec * 3) {
                    if (hex <= sub * 11) {
                        switch (hex) {
                            case 0xAB:
                            case 0xAC:
                            case 0xAD:
                            case 0xAE:
                            case 0xAF:
                            case 0xB0: Push(temp, hex, argcount, 2); continue;
                            case 0xB1:
                            case 0xB2:
                            case 0xB3:
                            case 0xB4:
                            case 0xB5:
                            case 0xB6:
                            case 0xB7:
                            case 0xB8: Push(temp, hex, argcount, 2); continue;
                            case 0xB9:
                            case 0xBA:
                            case 0xBB: break;
                        }
                    } else if (hex <= sub * 12) {
                        switch (hex) {
                            case 0xBC:
                            case 0xBD:
                            case 0xBE:
                            case 0xBF:
                            case 0xC0:
                            case 0xC1:
                            case 0xC2:
                            case 0xC3:
                            case 0xC4:
                            case 0xC5: break;
                            case 0xC6: 
                            case 0xC7: Push(temp, hex, argcount, 2); continue;
                            case 0xC8:
                            case 0xC9:
                            case 0xCA:
                            case 0xCB: break;
                            case 0xCC: SinglePush(temp, hex, resultvector); continue;
                        }
                    } else if (hex <= sub * 13) {
                        switch (hex) {
                            case 0xCD: Push(temp, hex, argcount, 1); continue;
                            case 0xCE: SinglePush(temp, hex, resultvector); continue;
                            case 0xCF: SinglePush(temp, hex, resultvector); continue;
                            case 0xD0:
                            case 0xD1:
                            case 0xD2:
                            case 0xD3: break;
                            case 0xD4: 
                                CheckBits(32, bits, 0xD4);
                                if (hexvector.at(i + 1) == 0x0A) {
                                    Push(temp, hex, argcount, 1);
                                    continue;
                                }
                                continue;
                            case 0xD5: CheckBits(32, bits, 0xD5); continue;
                            case 0xD6: CheckBits(32, bits, 0xD6); continue;
                            case 0xD7:
                            case 0xD8:
                            case 0xD9:
                            case 0xDA:
                            case 0xDB:
                            case 0xDC:
                            case 0xDD: break;
                        }
                    } else if (hex <= sub * 14) {
                        switch (hex) {
                            case 0xDE:
                            case 0xDF:
                            case 0xE0:
                            case 0xE1:
                            case 0xE2:
                            case 0xE3:
                            case 0xE4:
                            case 0xE5:
                            case 0xE6:
                            case 0xE7:
                            case 0xE8:
                            case 0xE9:
                            case 0xEA: CheckBits(32, bits, 0xEA);
                            case 0xEB:
                            case 0xEC:
                            case 0xED:
                            case 0xEE: break;
                        }
                    } else {
                        switch (hex) {
                            case 0xEF:
                            case 0xF0:
                            case 0xF1: SinglePush(temp, hex, resultvector); continue;
                            case 0xF2:
                            case 0xF3: break;
                            case 0xF4: SinglePush(temp, hex, resultvector); continue;
                            case 0xF5:
                            case 0xF6:
                            case 0xF7: break;
                            case 0xF8: SinglePush(temp, hex, resultvector); continue;
                            case 0xF9: SinglePush(temp, hex, resultvector); continue;
                            case 0xFA: SinglePush(temp, hex, resultvector); continue;
                            case 0xFB: SinglePush(temp, hex, resultvector); continue;
                            case 0xFC: SinglePush(temp, hex, resultvector); continue;
                            case 0xFD: SinglePush(temp, hex, resultvector); continue;
                            case 0xFE:
                            case 0xFF: break;
                            default: OUTPUT::Error("Unknown hex", 0x10); break;
                        }
                    }
                }
            }
        }

} DECODE;