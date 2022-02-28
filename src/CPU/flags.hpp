#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>
#include <array>

#ifndef FLAGS
#define FLAGS

struct EFLAGS_REGISTER {
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