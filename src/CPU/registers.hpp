#include <iostream>
#include <cstdlib>

#ifndef REG
#define REG

class REGISTERS {
    public:

        // 64-bit
        struct R64 {
            uint64_t RAX; // accumulator
            uint64_t RCX; // counter
            uint64_t RDX; // data
            uint64_t RBX; // base
            uint64_t RSP; // stack pointer
            uint64_t RBP; // stack base pointer
            uint64_t RSI; // source index
            uint64_t RDI; // destination index
        } R64;

        // 32-bit
        struct R32 {
            uint32_t EAX;
            uint32_t ECX;
            uint32_t EDX;
            uint32_t EBX;
            uint32_t ESP;
            uint32_t EBP;
            uint32_t ESI;
            uint32_t EDI;
        } R32;

        // 16-bit
        struct R16 {
            uint16_t AX;
            uint16_t CX;
            uint16_t DX;
            uint16_t BX;
            uint16_t SP;
            uint16_t BP;
            uint16_t SI;
            uint16_t DI;
        } R16;

        // 8-bit
        struct R8 {
            uint8_t AH;
            uint8_t AL;
            uint8_t CH;
            uint8_t CL;
            uint8_t DH;
            uint8_t DL;
            uint8_t BH;
            uint8_t BL;

            uint8_t SPL;
            uint8_t BPL;
            uint8_t SIL;
            uint8_t DIL;
        } R8;

        // Segment registers
        struct SEGR {
            uint16_t SS; // stack
            uint16_t CS; // code
            uint16_t DS; // data
            uint16_t ES; // extra data
            uint16_t FS; // more extra data
            uint16_t GS; // still more extra data lol
        } SREG;

        // Reset all registers to 0
        bool ResetAll(void) {
            try {
                R64.RAX = R64.RBX = R64.RCX = R64.RDX = R64.RBP = R64.RSP = R64.RSI = R64.RDI = \
                R32.EAX = R32.EBX = R32.ECX = R32.EDX = R32.EBP = R32.ESP = R32.ESI = R32.EDI = \
                R16.AX = R16.BX = R16.CX = R16.DX = R16.BP = R16.SP = R16.SI = R16.DI = \
                R8.AH = R8.AL = R8.BH = R8.BL = R8.CH = R8.CL = R8.DH = R8.DL = R8.SPL = R8.BPL = R8.SIL = R8.DIL = 0;
                return true;
            } catch (...) {
                return false;
            }
        }

} REGISTER;

#endif