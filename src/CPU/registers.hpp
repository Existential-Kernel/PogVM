#include <iostream>
#include <cstdlib>

union REGISTERS {
    // 64-bit
    struct ULL_REGISTER_STRUCT {
        uint64_t RAX; // accumulator
        uint64_t RCX; // counter
        uint64_t RDX; // data
        uint64_t RBX; // base
        uint64_t RSP; // stack pointer
        uint64_t RBP; // stack base pointer
        uint64_t RSI; // source index
        uint64_t RDI; // destination index
    } ULL_REGISTERS;

    // 32-bit
    struct UL_REGISTER_STRUCT {
        uint32_t EAX;
        uint32_t ECX;
        uint32_t EDX;
        uint32_t EBX;
        uint32_t ESP;
        uint32_t EBP;
        uint32_t ESI;
        uint32_t EDI;
    } UL_REGISTERS;

    // 16-bit
    struct SHORT_REGISTER_STRUCT {
        uint16_t AX;
        uint16_t CX;
        uint16_t DX;
        uint16_t BX;
        uint16_t SP;
        uint16_t BP;
        uint16_t SI;
        uint16_t DI;
    } SHORT_REGISTERS;

    // 8-bit
    struct CHAR_REGISTER_STRUCT {
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
    } CHAR_REGISTERS;
} REGISTERS;

struct SEGMENT_REGISTERS {
    uint16_t SS; // stack
    uint16_t CS; // code
    uint16_t DS; // data
    uint16_t ES; // extra data
    uint16_t FS; // more extra data
    uint16_t GS; // still more extra data lol
} SREG;