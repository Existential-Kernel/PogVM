#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>
#include <array>

#ifndef FLAGS
#define FLAGS
struct EFLAGS_REGISTER {
    std::array<std::string, 32> collection = { 
        "CF",   // carry
        "1",  
        "PF",   //parity
        "0",
        "AF",   // adjust
        "0", 
        "ZF",   // zero
        "SF",   // sign
        "TF",   // trap
        "IF",   // interupt
        "DF",   // direction
        "OF",   // overflow
        "IOPL", // I/O priviledge level field
        "IOPL", 
        "NT",   // nested
        "0",
        "RF",   // resume
        "VM",   // virtual 8086 mode
        "AC",   // alignment check
        "VIF",  // virtual interrupt
        "VIP",  // virtual interrupt pending
        "ID",   // identification
        "0", "0", "0", "0", "0",  
        "0", "0", "0", "0", "0"
    };
        

} FLAGS;
#endif