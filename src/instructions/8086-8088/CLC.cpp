/*
 * Instruction: CLC
 * Description: Clear the carry flag
 * Opcode(s):   0xF8
 */

#include "../cpu/flags.hpp"
#include "../instructions/constructor.cpp"

inline void CLC_FUNC(void) {
    FLAGS::EFLAGS.eflagcode[0] = 0;
}

Construct CLC(&CLC_FUNC);