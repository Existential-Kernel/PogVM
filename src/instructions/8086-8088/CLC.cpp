/*
 * Instruction: CLC
 * Description: Clear the carry flag
 * Opcode(s):   0xF8
 */

#include "../cpu/flags.hpp"

inline void CLC(void) {
    FLAGS::EFLAGS.eflagcode[0] = 0;
}