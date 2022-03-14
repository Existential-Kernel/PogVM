#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>
#include <array>
#include <bitset>

namespace FLAGS {
    struct EFLAGS {
        std::bitset<32> eflagcode;

        void CF(bool b) { eflagcode[0] == b; }
        void PF(bool b) { eflagcode[2] == b; }
        void AF(bool b) { eflagcode[4] == b; }
        void ZF(bool b) { eflagcode[6] == b; }
        void SF(bool b) { eflagcode[7] == b; }
        void TF(bool b) { eflagcode[8] == b; }
        void IF(bool b) { eflagcode[9] == b; }
        void DF(bool b) { eflagcode[10] == b; }
        void OF(bool b) { eflagcode[11] == b; }
        void IOPL(int pos, bool b) { if (pos == 1) { eflagcode[12] == b; } else { eflagcode[13] == b; } }
        void NT(bool b) { eflagcode[14] == b; }
        void RF(bool b) { eflagcode[15] == b; }
        void VM(bool b) { eflagcode[16] == b; }
        void AC(bool b) { eflagcode[17] == b; }
        void VIF(bool b) { eflagcode[18] == b; }
        void VIP(bool b) { eflagcode[19] == b; }
        void ID(bool b) { eflagcode[20] == b; }

        void Reset() { eflagcode = 0; }

        /*
        enum collection { 
            CF,   // carry
            RESERVED,  
            PF,   // parity
            RESERVED,
            AF,   // adjusT
            RESERVED, 
            ZF,   // zero
            SF,   // sign
            TF,   // trap
            IF,   // interupt
            DF,   // direction
            OF,   // overflow
            IOPL, // I/O priviledge level field
            IOPL,
            NT,   // nested
            RESERVED,
            RF,   // resume
            VM,   // virtual 8086 mode
            AC,   // alignment check
            VIF,  // virtual interrupt
            VIP,  // virtual interrupt pending
            ID,   // identification
            RESERVED, RESERVED, RESERVED, RESERVED, RESERVED,  
            RESERVED, RESERVED, RESERVED, RESERVED, RESERVED
        };
        */
    } EFLAGS;

    struct CONTROL {
        std::bitset<32> controlcode;
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
    } CONTROL;
};