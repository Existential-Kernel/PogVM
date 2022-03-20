/*
 * Instruction: CLI
 * Description: Clear the interrupt flag
 * Opcode(s):   0xFA
 */

#include "../cpu/flags.hpp"

inline void CLI(void) {
    FLAGS::EFLAGS.eflagcode[9] = 0;
}