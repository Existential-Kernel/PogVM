#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>
#include <array>
#include <bitset>

#ifndef FLAGS
#define FLAGS

class EFLAGS {
    public:
        uint32_t flagcode;
        std::bitset<32> FLAG;

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
} FLAGS;

#endif