/*
 * Instruction: CLD
 * Description: Clear the direction flag
 * Opcode:      0xFC
 */

#include "../cpu/flags.hpp"

void CLD(void) {
    FLAGS::EFLAGS.eflagcode[10] = 0;
}