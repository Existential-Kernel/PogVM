#include <bitset>

#pragma once

class REGISTER {
    public:
        // 256-bit
        struct R256_STRUCT {
            std::bitset<256> YMM0 = 0;
            std::bitset<256> YMM1 = 0;
            std::bitset<256> YMM2 = 0;
            std::bitset<256> YMM3 = 0;
            std::bitset<256> YMM4 = 0;
            std::bitset<256> YMM5 = 0;
            std::bitset<256> YMM6 = 0;
            std::bitset<256> YMM7 = 0;
        } R256;

        // 128-bit
        struct R128_STRUCT {
            std::bitset<128> XMM0 = 0;
            std::bitset<128> XMM1 = 0;
            std::bitset<128> XMM2 = 0;
            std::bitset<128> XMM3 = 0;
            std::bitset<128> XMM4 = 0;
            std::bitset<128> XMM5 = 0;
            std::bitset<128> XMM6 = 0;
            std::bitset<128> XMM7 = 0;
        } R128;

        // 80-bit
        struct R80_STRUCT {
            std::bitset<80> ST0 = 0;
            std::bitset<80> ST1 = 0;
            std::bitset<80> ST2 = 0;
            std::bitset<80> ST3 = 0;
            std::bitset<80> ST4 = 0;
            std::bitset<80> ST5 = 0;
            std::bitset<80> ST6 = 0;
            std::bitset<80> ST7 = 0;
        } R80;


    /*
    * A = accumulator
    * B = base
    * C = counter
    * D = data
    * SP = stack pointer
    * BP = stack base pointer
    * SI = source index
    * DI = destination index
    */
        // 64-bit
        struct R64_STRUCT {
            uint64_t RAX, RBX, RCX, RDX, RSP, RBP, RSI, RDI = 0;
        } R64;

        // 32-bit
        struct R32_STRUCT {
            uint32_t EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI = 0;
        } R32;

        // 16-bit
        struct R16_STRUCT {
            uint16_t AX, BX, CX, DX, SP, BP, SI, DI = 0;
        } R16;

        // 8-bit
        struct R8_STRUCT {
            uint8_t AH, BH, CH, DH = 0;
            uint8_t AL, BL, CL, DL = 0;
            uint8_t SPL, BPL, SIL, DIL = 0;
        } R8;

        // Segment registers
        struct SREG_STRUCT {
            uint16_t
                SS, // stack
                CS, // code
                DS, // data
                ES, // extra data
                FS, // more extra data
                GS  // still more extra data lol
            = 0;
        } SREG;

        // Pointer registers
        struct PREG_STRUCT {
            uint64_t RIP = 0;
            uint32_t EIP = 0;
            uint16_t IP = 0;
        } PREG;

        // Auxiliary registers (added for convenience)
        struct AREG_STRUCT {
            uint16_t IR = 0; // instruction register
            uint64_t PC = 0; // program counter
        } AREG;


        // Control registers
        struct CREG {
            uint32_t CR0, CR1, CR2, CR3, CR4, CR5, CR6, CR7 = 0;

    /*
            struct CR4 {
                enum collection {
                    VME = 0,       // Virtual 8086 Mode Extensions
                    PVI, 	       // Protected-mode Virtual Interrupts
                    TSD, 	       // Time Stamp Disable
                    DE,            // Debugging Extensions
                    PSE, 	       // Page Size Extension
                    PAE, 	       // Physical Address Extension
                    MCE, 	       // Machine Check Exception
                    PGE,	       // Page Global Enabled
                    PCE, 	       // Performance-Monitoring Counter enable
                    OSFXSR, 	   // Operating system support for FXSAVE and FXRSTOR instructions
                    OSXMMEXCPT,    // Operating System Support for Unmasked SIMD Floating-Point Exceptions
                    UMIP, 	       // User-Mode Instruction Prevention (if set, #GP on SGDT, SIDT, SLDT, SMSW, and STR instructions when CPL > 0)
                    VMXE = 13, 	   // Virtual Machine Extensions Enable
                    SMXE, 	       // Safer Mode Extensions Enable
                    FSGSBASE = 16, // Enables the instructions RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE
                    PCIDE, 	       // PCID Enable
                    OSXSAVE, 	   // XSAVE and Processor Extended States Enable
                    SMEP = 20, 	   // Supervisor Mode Execution Protection Enable
                    SMAP,          // Supervisor Mode Access Prevention Enable
                    PKE, 	       // Protection Key Enable
                    CET, 	       // Control-flow Enforcement Technology
                    PKS, 	       // Enable Protection Keys for Supervisor-Mode Pages 
                };
            } CR4;
    */
        } CREG;

        // Extended control registers
        struct XCREG {

            // NOTE: XCR0 can only be accessed if bit 18 of CR4 is set to 1. XGETBV and XSETBV instructions are used to access XCR0.
            struct XCR0 {
                enum collection {
                    X87 = 0,   // x87 FPU/MMX support (must be 1) 
                    SSE,       // XSAVE support for MXCSR and XMM registers 
                    AVX,       // AVX enabled and XSAVE support for upper halves of YMM registers
                    BNDREG,    // MPX enabled and XSAVE support for BND0-BND3 registers 
                    BNDCSR,    // MPX enabled and XSAVE support for BNDCFGU and BNDSTATUS registers 
                    opmask,    // AVX-512 enabled and XSAVE support for opmask registers k0-k7
                    ZMM_Hi256, // AVX-512 enabled and XSAVE support for upper halves of lower ZMM registers 
                    Hi16_ZMM,  // AVX-512 enabled and XSAVE support for upper ZMM registers 
                    PKRU = 9   // XSAVE support for PKRU register 
                };
            } XCR0;
        } XCREG;

        // Debug registers
        struct DREG {
            struct DR7 {
                enum collection {

                };
            } DR7;
        } DREG;

        // Struct pointers
        R256_STRUCT *R256_PTR = &R256;
        R128_STRUCT *R128_PTR = &R128;
        R80_STRUCT *R80_PTR = &R80;
        R64_STRUCT *R64_PTR = &R64;
        R32_STRUCT *R32_PTR = &R32;
        R16_STRUCT *R16_PTR = &R16;
        R8_STRUCT *R8_PTR = &R8;
        SREG_STRUCT *SREG_PTR = &SREG;
        PREG_STRUCT *PREG_PTR = &PREG;
        AREG_STRUCT *AREG_PTR = &AREG;
};