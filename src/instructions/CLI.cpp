/*
 * Instruction: CLI
 * Description: Clear the interrupt flag
 * Opcode:      0xFA
 */

#include "../cpu/flags.hpp"

void CLI(void) {
    FLAGS::EFLAGS.IF(0);
}