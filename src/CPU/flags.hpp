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
        nullflag = 0,  
        PF,   //parity
        nullflag = 0,
        AF,   // adjust
        nullflag = 0, 
        ZF,   // zero
        SF,   // sign
        TF,   // trap
        IF,   // interupt
        DF,   // direction
        OF,   // overflow
        IOPL, // I/O priviledge level field
        IOPL, 
        NT,   // nested
        nullflag = 0,
        RF,   // resume
        VM,   // virtual 8086 mode
        AC,   // alignment check
        VIF,  // virtual interrupt
        VIP,  // virtual interrupt pending
        ID,   // identification
        nullflag = 0, nullflag = 0, nullflag = 0, nullflag = 0, nullflag = 0,  
        nullflag = 0, nullflag = 0, nullflag = 0, nullflag = 0, nullflag = 0
    };
} FLAGS;

#endif