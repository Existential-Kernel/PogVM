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
        nullreg = 0,  
        PF,   //parity
        nullreg = 0,
        AF,   // adjust
        nullreg = 0, 
        ZF,   // zero
        SF,   // sign
        TF,   // trap
        IF,   // interupt
        DF,   // direction
        OF,   // overflow
        IOPL, // I/O priviledge level field
        IOPL, 
        NT,   // nested
        nullreg = 0,
        RF,   // resume
        VM,   // virtual 8086 mode
        AC,   // alignment check
        VIF,  // virtual interrupt
        VIP,  // virtual interrupt pending
        ID,   // identification
        nullreg = 0, nullreg = 0, nullreg = 0, nullreg = 0, nullreg = 0,  
        nullreg = 0, nullreg = 0, nullreg = 0, nullreg = 0, nullreg = 0
    };
} FLAGS;

#endif