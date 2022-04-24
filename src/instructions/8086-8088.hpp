#include "../cpu/flags.hpp"
#include "../cpu/registers.hpp"

namespace ORIGINAL {
    /*
    * Instruction: AAA
    * Description: ASCII adjust AL after addition
    * Opcode(s):   0x37
    */



    /*
    * Instruction: AAD
    * Description: ASCII adjust AX before division
    * Opcode(s):   0xD5
    */



    /*
    * Instruction: AAM
    * Description: ASCII adjust AX after multiplication
    * Opcode(s):   0xD4
    */



    /*
    * Instruction: AAS
    * Description: ASCII adjust AL after substration
    * Opcode(s):   0x3F
    */



    /*
    * Instruction: ADC
    * Description: Add with carry
    * Opcodes(s):  0x10...0x15, 0x80...0x81/2, 0x82...0x83/2
    */



    /*
    * Instruction: ADD
    * Description: Add
    * Opcode(s):   0x00...0x05, 0x80/0...0x81/0, 0x82/0...0x83/0
    */



    /*
    * Instruction: AND
    * Description: Logical AND
    * Opcode(s):   0x20...0x25, 0x80...0x81/4, 0x82...0x83/4
    */



    /*
    * Instruction: CLC
    * Description: Clear the carry flag
    * Opcode(s):   0xF8
    */
    inline void CLC(void) {
        FLAGS::EFLAGS.eflagcode[0] = 0;
    }



    /*
    * Instruction: CLD
    * Description: Clear the direction flag
    * Opcode(s):   0xFC
    */
    inline void CLD(void) {
        FLAGS::EFLAGS.eflagcode[10] = 0;
    }



    /*
    * Instruction: CLI
    * Description: Clear the interrupt flag
    * Opcode(s):   0xFA
    */
    inline void CLI(void) {
        FLAGS::EFLAGS.eflagcode[9] = 0;
    }
}