#include <iostream>
#include <cstdlib>
#include <bitset>

#ifndef REG
#define REG

// https://wiki.osdev.org/CPU_Registers_x86
// https://blog.yossarian.net/2020/11/30/How-many-registers-does-an-x86-64-cpu-have

namespace REGISTER {
    struct GPR {
        // 64-bit
        struct R64 {
            uint64_t RAX; // accumulator
            uint64_t RBX; // base
            uint64_t RCX; // counter
            uint64_t RDX; // data
            uint64_t RSP; // stack pointer
            uint64_t RBP; // stack base pointer
            uint64_t RSI; // source index
            uint64_t RDI; // destination index
        } R64;

        // 32-bit
        struct R32 {
            uint32_t EAX;
            uint32_t EBX;
            uint32_t ECX;
            uint32_t EDX;
            uint32_t ESP;
            uint32_t EBP;
            uint32_t ESI;
            uint32_t EDI;
        } R32;

        // 16-bit
        struct R16 {
            uint16_t AX;
            uint16_t BX;
            uint16_t CX;
            uint16_t DX;
            uint16_t SP;
            uint16_t BP;
            uint16_t SI;
            uint16_t DI;
        } R16;

        // 8-bit
        struct R8 {
            uint8_t AH;
            uint8_t BH;
            uint8_t CH;
            uint8_t DH;
            uint8_t AL;
            uint8_t BL;
            uint8_t CL;
            uint8_t DL;

            uint8_t SPL;
            uint8_t BPL;
            uint8_t SIL;
            uint8_t DIL;
        } R8;
    } GPR;

    // Segment registers
    struct SREG {
        uint16_t SS; // stack
        uint16_t CS; // code
        uint16_t DS; // data
        uint16_t ES; // extra data
        uint16_t FS; // more extra data
        uint16_t GS; // still more extra data lol
    } SREG;

    // Pointer registers
    struct PREG {
        uint64_t RIP;
        uint32_t EIP;
        uint16_t IP;
    } PREG;

    // Custom (added for now)
    struct CUSREG {
        uint16_t IR;
    } CUSREG;




    // EFLAGS register
    struct EFLAGS {
        std::bitset<32> flagcode;

        enum collection { 
            CF = 0,   // carry
            PF = 2,   // parity
            AF = 4,   // adjust
            ZF = 6,   // zero
            SF,       // sign
            TF,       // trap
            IF,       // interupt
            DF,       // direction
            OF,       // overflow
            IOPL,     // I/O priviledge level field
            //IOPL, 
            NT = 14,  // nested
            RF = 16,  // resume
            VM,       // virtual 8086 mode
            AC,       // alignment check
            VIF,      // virtual interrupt
            VIP,      // virtual interrupt pending
            ID,       // identification
        };
    } EFLAGS;

    // Control registers
    struct CREG {
        struct CR0 {
            std::bitset<32> flagcode;
            enum collection {
                PE = 0,  // protected mode enable
                MP,      // monitor co-processor
                EM,      // x87 FPU emulation
                TS,      // task switched
                ET,      // extention type
                NE,      // numeric error
                WP = 16, // write protect
                AM = 18, // alignment mask
                NW = 29, // not-write through
                CD,      // cache disabled
                PG,      // paging
            };
        } CR0;

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

    // Reset all registers to 0
    bool ResetAll(void) {
        try {
            GPR.R64.RAX = GPR.R64.RBX = GPR.R64.RCX = GPR.R64.RDX = GPR.R64.RBP = GPR.R64.RSP = GPR.R64.RSI = GPR.R64.RDI = \
            GPR.R32.EAX = GPR.R32.EBX = GPR.R32.ECX = GPR.R32.EDX = GPR.R32.EBP = GPR.R32.ESP = GPR.R32.ESI = GPR.R32.EDI = \
            GPR.R16.AX = GPR.R16.BX = GPR.R16.CX = GPR.R16.DX = GPR.R16.BP = GPR.R16.SP = GPR.R16.SI = GPR.R16.DI = \
            GPR.R8.AH = GPR.R8.AL = GPR.R8.BH = GPR.R8.BL = GPR.R8.CH = GPR.R8.CL = GPR.R8.DH = GPR.R8.DL = GPR.R8.SPL = GPR.R8.BPL = GPR.R8.SIL = GPR.R8.DIL = \
            SREG.SS = SREG.CS = SREG.DS = SREG.ES = SREG.FS = SREG.GS = \
            PREG.RIP = PREG.EIP = PREG.IP = 0;

            return true;
        } catch (...) {
            return false;
        }
    }
};

#endif