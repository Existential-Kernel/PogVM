#include <bitset>

#ifndef REG
#define REG

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

        // 64-bit
        struct R64_STRUCT {
            uint64_t RAX = 0; // accumulator
            uint64_t RBX = 0; // base
            uint64_t RCX = 0; // counter
            uint64_t RDX = 0; // data
            uint64_t RSP = 0; // stack pointer
            uint64_t RBP = 0; // stack base pointer
            uint64_t RSI = 0; // source index
            uint64_t RDI = 0; // destination index
        } R64;

        // 32-bit
        struct R32_STRUCT {
            uint32_t EAX = 0;
            uint32_t EBX = 0;
            uint32_t ECX = 0;
            uint32_t EDX = 0;
            uint32_t ESP = 0;
            uint32_t EBP = 0;
            uint32_t ESI = 0;
            uint32_t EDI = 0;
        } R32;

        // 16-bit
        struct R16_STRUCT {
            uint16_t AX = 0;
            uint16_t BX = 0;
            uint16_t CX = 0;
            uint16_t DX = 0;
            uint16_t SP = 0;
            uint16_t BP = 0;
            uint16_t SI = 0;
            uint16_t DI = 0;
        } R16;

        // 8-bit
        struct R8_STRUCT {
            uint8_t AH = 0;
            uint8_t BH = 0;
            uint8_t CH = 0;
            uint8_t DH = 0;
            uint8_t AL = 0;
            uint8_t BL = 0;
            uint8_t CL = 0;
            uint8_t DL = 0;

            uint8_t SPL = 0;
            uint8_t BPL = 0;
            uint8_t SIL = 0;
            uint8_t DIL = 0;
        } R8;

        // Segment registers
        struct SREG_STRUCT {
            uint16_t SS = 0; // stack
            uint16_t CS = 0; // code
            uint16_t DS = 0; // data
            uint16_t ES = 0; // extra data
            uint16_t FS = 0; // more extra data
            uint16_t GS = 0; // still more extra data lol
        } SREG;

        // Pointer registers
        struct PREG_STRUCT {
            uint64_t RIP = 0;
            uint32_t EIP = 0;
            uint16_t IP = 0;
        } PREG;

        // Auxilary registers (added for now)
        struct AREG_STRUCT {
            uint16_t IR = 0; // instruction counter
            uint64_t PC = 0; // program counter
        } AREG;


        // Control registers
        struct CREG {
            uint32_t CR0 = 0;
            uint32_t CR1 = 0;
            uint32_t CR2 = 0;
            uint32_t CR3 = 0;
            uint32_t CR4 = 0;
            uint32_t CR5 = 0;
            uint32_t CR6 = 0;
            uint32_t CR7 = 0;

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
        
} REGISTER;

#endif