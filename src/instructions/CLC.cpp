/*
 * Instruction: CLC
 * Description: Clear the carry flag
 * Opcode:      0xF8
 */

#include "../cpu/flags.hpp"

void CLC(void) {
    FLAGS::EFLAGS.eflagcode[0] = 0;
}