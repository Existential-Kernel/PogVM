#include "../cpu/flags.hpp"
#include "../cpu/registers.hpp"

namespace i8088 {
    /*
     * Instruction: AAA
     * Description: ASCII adjust AL after addition
     * Opcode(s):   0x37
     */
    inline void AAA(void) {

    }


    /*
     * Instruction: AAD
     * Description: ASCII adjust AX before division
     * Opcode(s):   0xD5
     */
    inline void AAD() {

    } 


    /*
     * Instruction: AAM
     * Description: ASCII adjust AX after multiplication
     * Opcode(s):   0xD4
     */
    inline void AAM() {

    }
    

    /*
     * Instruction: AAS
     * Description: ASCII adjust AL after substration
     * Opcode(s):   0x3F
     */
    inline void AAS(void) {

    } 


    /*
     * Instruction: ADC
     * Description: Add with carry
     * Opcodes(s):  0x10...0x15, 0x80...0x81/2, 0x82...0x83/2
     */
    /*
    template <typename ADC1, typename ADC2>
    inline void ADC(const uint8_t &opcode, const ADC1 &operand1, const ADC2 &operand2) {
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


    /*
     * Instruction: INT
     * Description: Generate interrupt signal
     * Opcodes(s):  0xCC...0xCE, 0xF1
     */
    inline void INT(const uint8_t &opcode, uint8_t operand1 = 0) {
        std::cout << opcode << operand1; // this is only here as a test for now
    }


    /*
     * Instruction: MOV
     * Description: Clear the carry flag
     * Opcode(s):   0x88...0x8C, 0x8E, 0xA0...0xA3, 0xB0, 0xB8, 0xC6, 0xC7
     */
    inline void MOV(void) {
        
    }
}