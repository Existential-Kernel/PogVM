/*
 * Instruction: CLD
 * Description: Clear the direction flag
 * Opcode(s):   0xFC
 */

#include "../cpu/flags.hpp"

inline void CLD(void) {
    FLAGS::EFLAGS.eflagcode[10] = 0;
}