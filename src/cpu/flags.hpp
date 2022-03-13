#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>
#include <array>
#include <bitset>

#ifndef FLAGS
#define FLAGS

namespace FLAGS {
    std::bitset<32> eflagcode;

    enum collection { 
        CF,   // carry
        RESERVED,  
        PF,   //parity
        RESERVED,
        AF,   // adjust
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

#endif