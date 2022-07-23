#include <iostream>
#include <set>

#include "../cpu/flags.hpp"
#include "../cpu/registers.hpp"
#include "../defs.hpp"

namespace i80188 {
    /*
     * Instruction: 
     * Description: 
     * Opcode(s):   
     */
    static inline void idk(void) {

    }

        std::set<uint8_t, std::greater<uint8_t>> forbidden_80186_opcodes = {
        0x0F,

        0x63,
        0x64,
        0x65,
        0x66,
        0x67,

        0xD6,
        0xD8,
        0xD9,
        0xDA,
        0xDB,
        0xDC,
        0xDD,
        0xDE,
        0xDF,

        0xF1
    };
}