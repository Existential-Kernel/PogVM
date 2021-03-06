#pragma once

#include "../instructions/8086-8088.hpp"
// https://stackoverflow.com/questions/30443501/why-do-these-two-instructions-have-the-same-opcode

class DECODE {
    public:
        DECODE();
        ~DECODE();

    private:
        static inline void SinglePush(std::vector<uint8_t> &v, const uint8_t &s, std::vector<std::vector<uint8_t>> &instructions) noexcept;
        static inline void Push(std::vector<uint8_t> &v, const uint8_t &s, uint8_t &arg, const uint8_t &count) noexcept;
        static inline void SingleDirectPush(std::deque<uint8_t> &q , std::vector<uint8_t> &v, const uint8_t &opcode) noexcept;
        static inline void DirectPush(std::deque<uint8_t> &v, std::vector<uint8_t> &result, const int8_t &count) noexcept;
        static void CheckBits(const uint8_t &acceptablebits, const uint8_t &kernelbits, const uint8_t &hex) noexcept;
        static void CheckProc(const uint8_t &opcode, const uint8_t &kernelproc) noexcept;
        static void MassCheckProc(const std::vector<std::vector<uint8_t>> &instructions, const uint8_t &kernelproc) noexcept;
        static void CheckProcError(const uint8_t &opcode, const uint8_t &kernelproc) noexcept;
    
    public:
        static void MassDecode(const std::vector<uint8_t> &hexvector, std::vector<std::vector<uint8_t>> &resultvector, const uint8_t &bits, const uint8_t &processor);
        static void Decode(std::deque<uint8_t> &hexvector, std::vector<uint8_t> &instruction, const uint8_t &bits, const uint8_t &processor);
};


inline void DECODE::Push(std::vector<uint8_t> &v, const uint8_t &s, uint8_t &arg, const uint8_t &count) noexcept {
    v.push_back(s);
    arg = count;
}

inline void DECODE::SinglePush(std::vector<uint8_t> &v, const uint8_t &s, std::vector<std::vector<uint8_t>> &instructions) noexcept {
    v.push_back(s);
    instructions.push_back(v);
}

inline void DECODE::DirectPush(std::deque<uint8_t> &buffer, std::vector<uint8_t> &instruction, const int8_t &count) noexcept {
    for (size_t i = 0; i <= count; i++) {
        instruction.push_back(buffer.at(0));
        buffer.pop_front();
    }
}

inline void DECODE::SingleDirectPush(std::deque<uint8_t> &buffer, std::vector<uint8_t> &instruction, const uint8_t &opcode) noexcept {
    instruction.push_back(opcode);
    buffer.pop_front();
}

void DECODE::CheckBits(const uint8_t &acceptablebits, const uint8_t &kernelbits, const uint8_t &hex) noexcept {
    if (acceptablebits != kernelbits) {
        std::stringstream error;
        error << hex << "is an invalid instruction in " << kernelbits << "-bit mode";
        OUTPUT::Abort(error.str());
    }
}


[[maybe_unused, deprecated]] void DECODE::MassCheckProc(const std::vector<std::vector<uint8_t>> &instructions, const uint8_t &kernelproc) noexcept {
    for (size_t i = 0; i <= instructions.size(); i++) {
        if (i8086::forbidden_8086_opcodes.find(instructions.at(i).at(0)) != i8086::forbidden_8086_opcodes.end()) {
            CheckProcError(instructions.at(i).at(0), kernelproc);
        }
    }
}

void DECODE::CheckProc(const uint8_t &opcode, const uint8_t &kernelproc) noexcept {
    switch (kernelproc) {
        case 1:
            if (i8086::forbidden_8086_opcodes.find(opcode) != i8086::forbidden_8086_opcodes.end()) {
                CheckProcError(opcode, kernelproc);
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            break;

    }

/*
    #if (kernelproc == 1)
        if (i8086::forbidden_8086_opcodes.find(opcode) != i8086::forbidden_8086_opcodes.end()) {
            CheckProcError(opcode, kernelproc);
        }
    #endif
*/
}

void DECODE::CheckProcError(const uint8_t &opcode, const uint8_t &kernelproc) noexcept {
    std::stringstream error{};
    const std::string proc = [&kernelproc](){
        switch (kernelproc) {
            case 1: return "8086/8088";
            case 2: return "80186/80188";
            case 3: return "NEC-V";
            case 4: return "80286";
            case 5: return "80386"; 
            case 6: return "80486";
            case 7: return "Pentium";
            case 8: return "Pentium-MMX";
            case 9: return "AMD-K6"; 
            case 10: return "Pentium-Pro";
            case 11: return "Pentium-II";
            case 12: return "Intel-Itanium";
            case 13: return "Cyrix-Geode";
        }
    }();

    error << "Hex " << opcode << " is not supported by the " << proc << " processor";
    OUTPUT::Abort(error.str());
}

void DECODE::MassDecode(const std::vector<uint8_t> &hexvector, std::vector<std::vector<uint8_t>> &resultvector, const uint8_t &bits, const uint8_t &processor) {
    std::vector<uint8_t> temp{};
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

        uint8_t hex = hexvector.at(i);
        CheckProc(hex, processor);
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
            case 0x41: // fallthrough
            case 0x42:
            case 0x43:
            case 0x44: SinglePush(temp, hex, resultvector); continue;
            case 0x45: // fallthrough
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
            case 0x65: break;
            case 0x66: temp.push_back(0x66); continue;
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
            case 0x87: break;
            case 0x88: Push(temp, hex, argcount, 2); continue;
            case 0x89: 
            case 0x8A: 
            case 0x8B: break;
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
            case 0xB7: break;
            case 0xB8: Push(temp, hex, argcount, 4); continue;
            case 0xB9:
            case 0xBA: break;
            case 0xBB: Push(temp, hex, argcount, 4); continue;
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
        }
    }
}

void DECODE::Decode(
        std::deque<uint8_t> &buffer,
        std::vector<uint8_t> &instruction,
        const uint8_t &bits, 
        const uint8_t &processor
    ) {
    instruction.clear();
    
    switch (buffer.front()) { //threading mode
        case 0x00: DirectPush(buffer, instruction, 1); return;
        case 0x01: // fallthrough (for now)
        case 0x02:
        case 0x03:
        case 0x04: DirectPush(buffer, instruction, 1); return;
        case 0x05: DirectPush(buffer, instruction, 2); return;
        case 0x06: 
        case 0x07:
        case 0x08:
        case 0x09:
        case 0x0A:
        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x0E: DirectPush(buffer, instruction, 2); return;
        case 0x0F:
        case 0x10:
        case 0x11: break;
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
        case 0x40: SingleDirectPush(buffer, instruction, 0x40); return;
        case 0x41: // fallthrough
        case 0x42:
        case 0x43:
        case 0x44: SingleDirectPush(buffer, instruction, 0x44); return;
        case 0x45: // fallthrough
        case 0x46:
        case 0x47: SingleDirectPush(buffer, instruction, 0x47); return;
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
        case 0x65: break;
        case 0x66: //temp.push_back(0x66); return; /// ????
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
        case 0x87: break;
        case 0x88: DirectPush(buffer, instruction, 2); return;
        case 0x89: 
        case 0x8A: 
        case 0x8B: break;
        case 0x8C: DirectPush(buffer, instruction, 2); return;
        case 0x8D: break;
        case 0x8E: DirectPush(buffer, instruction, 2); return;
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
        case 0x9A:
        case 0x9B:
        case 0x9C:
        case 0x9D:
        case 0x9E:
        case 0x9F: break;
        case 0xA0: 
        case 0xA1: 
        case 0xA2: 
        case 0xA3: DirectPush(buffer, instruction, 2); return;
        case 0xA4:
        case 0xA5:
        case 0xA6:
        case 0xA7:
        case 0xA8:
        case 0xA9:
        case 0xAA: break;
        case 0xAB:
        case 0xAC:
        case 0xAD:
        case 0xAE:
        case 0xAF:
        case 0xB0: DirectPush(buffer, instruction, 2); return;
        case 0xB1:
        case 0xB2:
        case 0xB3:
        case 0xB4:
        case 0xB5:
        case 0xB6:
        case 0xB7: break;
        case 0xB8: DirectPush(buffer, instruction, 4); return;
        case 0xB9:
        case 0xBA: break;
        case 0xBB: DirectPush(buffer, instruction, 4); return;
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
        case 0xC7: DirectPush(buffer, instruction, 2); return;
        case 0xC8:
        case 0xC9:
        case 0xCA:
        case 0xCB: break;
        case 0xCC: SingleDirectPush(buffer, instruction, 0xCC); return;
        case 0xCD: DirectPush(buffer, instruction, 1); return;
        case 0xCE: SingleDirectPush(buffer, instruction, 0xCE); return;
        case 0xCF: SingleDirectPush(buffer, instruction, 0xCF); return;
        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3: break;
        case 0xD4: 
            CheckBits(32, bits, 0xD4);
            if (buffer.at(1) == 0x0A) {
                DirectPush(buffer, instruction, 1);
                return;
            }
            return;
        case 0xD5: CheckBits(32, bits, 0xD5);
        case 0xD6: CheckBits(32, bits, 0xD6);
        case 0xD7:
        case 0xD8:
        case 0xD9:
        case 0xDA:
        case 0xDB:
        case 0xDC:
        case 0xDD: break;
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
        case 0xEF:
        case 0xF0:
        case 0xF1: SingleDirectPush(buffer, instruction, 0xF1); return;
        case 0xF2:
        case 0xF3: break;
        case 0xF4: SingleDirectPush(buffer, instruction, 0xF4); return;
        case 0xF5:
        case 0xF6:
        case 0xF7: break;
        case 0xF8: SingleDirectPush(buffer, instruction, 0xF8); return;
        case 0xF9: SingleDirectPush(buffer, instruction, 0xF9); return;
        case 0xFA: SingleDirectPush(buffer, instruction, 0xFA); return;
        case 0xFB: SingleDirectPush(buffer, instruction, 0xFB); return;
        case 0xFC: SingleDirectPush(buffer, instruction, 0xFC); return;
        case 0xFD: SingleDirectPush(buffer, instruction, 0xFD); return;
        case 0xFE:
        case 0xFF: break;
    }
}

DECODE::DECODE()
{
}

DECODE::~DECODE()
{
}