#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>

namespace OPCODE {
    enum {
        AAA = 0,
        BR, // branch
        ADD,    // add
        LD,     // load
        ST,     // store
        JSR,    // jump register
        AND,    // bitwise and
        LDR,    // load register
        STR,    // store register
        RTI,    // unused
        NOT,    // bitwise not
        LDI,    // load indirect
        STI,    // store indirect
        JMP,    // jump
        RES,    // reserved (unused)
        LEA,    // load effective address
        TRAP    // execute trap
    };
}