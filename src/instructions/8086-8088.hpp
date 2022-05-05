#include "../cpu/flags.hpp"
#include "../cpu/registers.hpp"

#ifndef i8088_HPP
#define i8088_HPP

namespace i8088 {
    /*
     * Instruction: AAA
     * Description: ASCII adjust AL after addition
     * Opcode(s):   0x37
     */
    static inline void AAA(void) {

    }


    /*
     * Instruction: AAD
     * Description: ASCII adjust AX before division
     * Opcode(s):   0xD5
     */
    static inline void AAD() {

    } 


    /*
     * Instruction: AAM
     * Description: ASCII adjust AX after multiplication
     * Opcode(s):   0xD4
     */
    static inline void AAM() {

    }
    

    /*
     * Instruction: AAS
     * Description: ASCII adjust AL after substration
     * Opcode(s):   0x3F
     */
    static inline void AAS(void) {

    } 


    /*
     * Instruction: ADC
     * Description: Add with carry
     * Opcodes(s):  0x10...0x15, 0x80...0x81/2, 0x82...0x83/2
     */
    /*
    template <typename ADC1, typename ADC2>
    static inline void ADC(const uint8_t &opcode, const ADC1 &operand1, const ADC2 &operand2) {
        if (opcode == 0x10 || opcode == 0x11) {

        } else if (opcode == 0x12 || opcode == 0x13) {

        } else if (opcode == 0x14 || opcode == 0x15) {

        } else if (opcode == 0x80 || opcode == 0x81 || opcode == 0x82 || opcode == 0x83) {

        }
    }
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
     * Arguments:   None
     * Opcode(s):   0xF8
     */
    static inline void CLC(void) {
        FLAGS::EFLAGS_PTR->eflagcode.set(0, 0);
    }


    /*
     * Instruction: CLI
     * Description: Clear the interrupt flag
     * Arguments:   None
     * Opcode(s):   0xFA
     */
    static inline void CLI(void) {
        FLAGS::EFLAGS_PTR->eflagcode.set(9, 0);
    }


    /*
     * Instruction: CLD
     * Description: Clear the direction flag
     * Arguments:   None
     * Opcode(s):   0xFC
     */
    static inline void CLD(void) {
        FLAGS::EFLAGS_PTR->eflagcode.set(10, 0);
    }


    /*
     * Instruction: HLT
     * Description: Enter halt state
     * Arguments:   None
     * Opcode(s):   0xF4
     */
    static inline void HLT(void) {

    }


    /*
     * Instruction: INT
     * Description: Generate interrupt signal
     * Arguments:   None, 1 if opcode = 0xCD
     * Opcodes(s):  0xCC...0xCE, 0xF1
     */
    static inline void INT(const uint8_t &opcode, uint8_t operand1 = 0) {
        std::cout << opcode << operand1; // this is only here as a test for now
    }


    /*
     * Instruction: MOV
     * Description: Clear the carry flag
     * Arguments:   
     * Opcode(s):   0x88...0x8C, 0x8E, 0xA0...0xA3, 0xB0, 0xB8, 0xC6, 0xC7
     */
    static inline void MOV(/*const uint8_t &opcode, uint8_t operand1*/) {
        
    }


    /*
     * Instruction: STC
     * Description: Set the carry flag
     * Arguments:   None
     * Opcode(s):   0xF9
     */
    static inline void STC(void) {
        FLAGS::EFLAGS_PTR->eflagcode.set(0, 1);
    }


    /*
     * Instruction: STI
     * Description: Set the interrupt flag
     * Arguments:   None
     * Opcode(s):   0xFB
     */
    static inline void STI(void) {
        FLAGS::EFLAGS_PTR->eflagcode.set(9, 1);
    }


    /*
     * Instruction: STD
     * Description: Set the direction flag
     * Arguments:   None
     * Opcode(s):   0xFD
     */
    static inline void STD(void) {
        FLAGS::EFLAGS_PTR->eflagcode.set(10, 1);
    }
}

#endif