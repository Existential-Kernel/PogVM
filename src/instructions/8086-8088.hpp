#include <iostream>

#include "../cpu/flags.hpp"
#include "../cpu/registers.hpp"
#include "../defs.hpp"


/*
Examples:
    mov eax, [ebx] 	            ; Move the 4 bytes in memory at the address contained in EBX into EAX
    mov [var], ebx 	            ; Move the contents of EBX into the 4 bytes at memory address var. (Note, var is a 32-bit constant).
    mov eax, [esi-4] 	        ; Move 4 bytes at memory address ESI + (-4) into EAX
    mov [esi+eax], cl 	        ; Move the contents of CL into the byte at address ESI+EAX
    mov edx, [esi+4*ebx]     	; Move the 4 bytes of data at address ESI+4*EBX into EDX
*/

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
    inline void AAM(void) {
        REGISTER::R8_PTR->AH = (uint8_t)(REGISTER::R8_PTR->AL / 10);
        REGISTER::R8_PTR->AL %= 10;
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
     * Description: Add 2 numbers and store in operand1 source register
     * Arguments:   2
     * Opcode(s):   0x00...0x05, 0x80/0...0x81/0, 0x82/0...0x83/0
     */
    static void ADD(const uint8_t &opcode, const uint8_t &operand1, const uint8_t &operand2) {
        switch (opcode) {
            case 0x00:
                switch (operand1) {
                    case 0xC0: REGISTER::R8_PTR->AL <<= 1; break;
                    case 0xC1: REGISTER::R8_PTR->CL += REGISTER::R8_PTR->AL; break;
                    case 0xC2: REGISTER::R8_PTR->DL += REGISTER::R8_PTR->AL; break;
                    case 0xC3: REGISTER::R8_PTR->BL += REGISTER::R8_PTR->AL; break;
                    case 0xC4: REGISTER::R8_PTR->AH += REGISTER::R8_PTR->AL; break;
                    case 0xC5: REGISTER::R8_PTR->CH += REGISTER::R8_PTR->AL; break;
                    case 0xC6: REGISTER::R8_PTR->DH += REGISTER::R8_PTR->AL; break;
                    case 0xC7: REGISTER::R8_PTR->BH += REGISTER::R8_PTR->AL; break;

                    case 0xC8: REGISTER::R8_PTR->AL += REGISTER::R8_PTR->CL; break;
                    case 0xC9: REGISTER::R8_PTR->CL <<= 1; break;
                    case 0xCA: REGISTER::R8_PTR->DL += REGISTER::R8_PTR->CL; break;
                    case 0xCB: REGISTER::R8_PTR->BL += REGISTER::R8_PTR->CL; break;
                    case 0xCC: REGISTER::R8_PTR->AH += REGISTER::R8_PTR->CL; break;
                    case 0xCD: REGISTER::R8_PTR->CH += REGISTER::R8_PTR->CL; break;
                    case 0xCE: REGISTER::R8_PTR->DH += REGISTER::R8_PTR->CL; break;
                    case 0xCF: REGISTER::R8_PTR->BH += REGISTER::R8_PTR->CL; break;

                    case 0xD0: REGISTER::R8_PTR->AL += REGISTER::R8_PTR->DL; break;
                    case 0xD1: REGISTER::R8_PTR->CL += REGISTER::R8_PTR->DL; break;
                    case 0xD2: REGISTER::R8_PTR->DL <<= 1; break;
                    case 0xD3: REGISTER::R8_PTR->BL += REGISTER::R8_PTR->DL; break;
                    case 0xD4: REGISTER::R8_PTR->AH += REGISTER::R8_PTR->DL; break;
                    case 0xD5: REGISTER::R8_PTR->CH += REGISTER::R8_PTR->DL; break;
                    case 0xD6: REGISTER::R8_PTR->DH += REGISTER::R8_PTR->DL; break;
                    case 0xD7: REGISTER::R8_PTR->BH += REGISTER::R8_PTR->DL; break;

                    case 0xD8: REGISTER::R8_PTR->AL += REGISTER::R8_PTR->BL; break;
                    case 0xD9: REGISTER::R8_PTR->CL += REGISTER::R8_PTR->BL; break;
                    case 0xDA: REGISTER::R8_PTR->DL += REGISTER::R8_PTR->BL; break;
                    case 0xDB: REGISTER::R8_PTR->BL <<= 1; break;
                    case 0xDC: REGISTER::R8_PTR->AH += REGISTER::R8_PTR->BL; break;
                    case 0xDD: REGISTER::R8_PTR->CH += REGISTER::R8_PTR->BL; break;
                    case 0xDE: REGISTER::R8_PTR->DH += REGISTER::R8_PTR->BL; break;
                    case 0xDF: REGISTER::R8_PTR->BH += REGISTER::R8_PTR->BL; break;

                    case 0xE0: REGISTER::R8_PTR->AL += REGISTER::R8_PTR->AH; break;
                    case 0xE1: REGISTER::R8_PTR->CL += REGISTER::R8_PTR->AH; break;
                    case 0xE2: REGISTER::R8_PTR->DL += REGISTER::R8_PTR->AH; break;
                    case 0xE3: REGISTER::R8_PTR->BL += REGISTER::R8_PTR->AH; break;
                    case 0xE4: REGISTER::R8_PTR->AH <<= 1; break;
                    case 0xE5: REGISTER::R8_PTR->CH += REGISTER::R8_PTR->AH; break;
                    case 0xE6: REGISTER::R8_PTR->DH += REGISTER::R8_PTR->AH; break;
                    case 0xE7: REGISTER::R8_PTR->BH += REGISTER::R8_PTR->AH; break;

                    case 0xE8: REGISTER::R8_PTR->AL += REGISTER::R8_PTR->CH; break;
                    case 0xE9: REGISTER::R8_PTR->CL += REGISTER::R8_PTR->CH; break;
                    case 0xEA: REGISTER::R8_PTR->DL += REGISTER::R8_PTR->CH; break;
                    case 0xEB: REGISTER::R8_PTR->BL += REGISTER::R8_PTR->CH; break;
                    case 0xEC: REGISTER::R8_PTR->AH += REGISTER::R8_PTR->CH; break;
                    case 0xED: REGISTER::R8_PTR->CH <<= 1; break;
                    case 0xEE: REGISTER::R8_PTR->DH += REGISTER::R8_PTR->CH; break;
                    case 0xEF: REGISTER::R8_PTR->BH += REGISTER::R8_PTR->CH; break;

                    case 0xF0: REGISTER::R8_PTR->AL += REGISTER::R8_PTR->DH; break;
                    case 0xF1: REGISTER::R8_PTR->CL += REGISTER::R8_PTR->DH; break;
                    case 0xF2: REGISTER::R8_PTR->DL += REGISTER::R8_PTR->DH; break;
                    case 0xF3: REGISTER::R8_PTR->BL += REGISTER::R8_PTR->DH; break;
                    case 0xF4: REGISTER::R8_PTR->AH += REGISTER::R8_PTR->DH; break;
                    case 0xF5: REGISTER::R8_PTR->CH += REGISTER::R8_PTR->DH; break;
                    case 0xF6: REGISTER::R8_PTR->DH <<= 1; break;
                    case 0xF7: REGISTER::R8_PTR->BH += REGISTER::R8_PTR->DH; break;

                    case 0xF8: REGISTER::R8_PTR->AL += REGISTER::R8_PTR->BH; break;
                    case 0xF9: REGISTER::R8_PTR->CL += REGISTER::R8_PTR->BH; break;
                    case 0xFA: REGISTER::R8_PTR->DL += REGISTER::R8_PTR->BH; break;
                    case 0xFB: REGISTER::R8_PTR->BL += REGISTER::R8_PTR->BH; break;
                    case 0xFC: REGISTER::R8_PTR->AH += REGISTER::R8_PTR->BH; break;
                    case 0xFD: REGISTER::R8_PTR->CH += REGISTER::R8_PTR->BH; break;
                    case 0xFE: REGISTER::R8_PTR->DH += REGISTER::R8_PTR->BH; break;
                    case 0xFF: REGISTER::R8_PTR->BH <<= 1; break;
                    default: OUTPUT::Abort("Invalid operand");
                }
                break;
            case 0x01: 
                switch (operand1) {
                    case 0xC0: REGISTER::R32_PTR->EAX <<= 1; break;
                    case 0xC1: REGISTER::R32_PTR->ECX += REGISTER::R32_PTR->EAX; break;
                    case 0xC2: REGISTER::R32_PTR->EDX += REGISTER::R32_PTR->EAX; break;
                    case 0xC3: REGISTER::R32_PTR->EBX += REGISTER::R32_PTR->EAX; break;
                    case 0xC4: REGISTER::R32_PTR->ESP += REGISTER::R32_PTR->EAX; break;
                    case 0xC5: REGISTER::R32_PTR->EBP += REGISTER::R32_PTR->EAX; break;
                    case 0xC6: REGISTER::R32_PTR->ESI += REGISTER::R32_PTR->EAX; break;
                    case 0xC7: REGISTER::R32_PTR->EDI += REGISTER::R32_PTR->EAX; break;

                    case 0xC8: REGISTER::R32_PTR->EAX += REGISTER::R32_PTR->ECX; break;
                    case 0xC9: REGISTER::R32_PTR->ECX <<= 1; break;
                    case 0xCA: REGISTER::R32_PTR->EDX += REGISTER::R32_PTR->ECX; break;
                    case 0xCB: REGISTER::R32_PTR->EBX += REGISTER::R32_PTR->ECX; break;
                    case 0xCC: REGISTER::R32_PTR->ESP += REGISTER::R32_PTR->ECX; break;
                    case 0xCD: REGISTER::R32_PTR->EBP += REGISTER::R32_PTR->ECX; break;
                    case 0xCE: REGISTER::R32_PTR->ESI += REGISTER::R32_PTR->ECX; break;
                    case 0xCF: REGISTER::R32_PTR->EDI += REGISTER::R32_PTR->ECX; break;

                    case 0xD0: REGISTER::R32_PTR->EAX += REGISTER::R32_PTR->EDX; break;
                    case 0xD1: REGISTER::R32_PTR->ECX += REGISTER::R32_PTR->EDX; break;
                    case 0xD2: REGISTER::R32_PTR->EDX <<= 1; break;
                    case 0xD3: REGISTER::R32_PTR->EBX += REGISTER::R32_PTR->EDX; break;
                    case 0xD4: REGISTER::R32_PTR->ESP += REGISTER::R32_PTR->EDX; break;
                    case 0xD5: REGISTER::R32_PTR->EBP += REGISTER::R32_PTR->EDX; break;
                    case 0xD6: REGISTER::R32_PTR->ESI += REGISTER::R32_PTR->EDX; break;
                    case 0xD7: REGISTER::R32_PTR->EDI += REGISTER::R32_PTR->EDX; break;

                    case 0xD8: REGISTER::R32_PTR->EAX += REGISTER::R32_PTR->EBX ; break;
                    case 0xD9: REGISTER::R32_PTR->ECX += REGISTER::R32_PTR->EBX ; break;
                    case 0xDA: REGISTER::R32_PTR->EDX += REGISTER::R32_PTR->EBX ; break;
                    case 0xDB: REGISTER::R32_PTR->EBX <<= 1; break;
                    case 0xDC: REGISTER::R32_PTR->ESP += REGISTER::R32_PTR->EBX ; break;
                    case 0xDD: REGISTER::R32_PTR->EBP += REGISTER::R32_PTR->EBX ; break;
                    case 0xDE: REGISTER::R32_PTR->ESI += REGISTER::R32_PTR->EBX ; break;
                    case 0xDF: REGISTER::R32_PTR->EDI += REGISTER::R32_PTR->EBX ; break;

                    case 0xE0: REGISTER::R32_PTR->EAX += REGISTER::R32_PTR->ESP; break;
                    case 0xE1: REGISTER::R32_PTR->ECX += REGISTER::R32_PTR->ESP; break;
                    case 0xE2: REGISTER::R32_PTR->EDX += REGISTER::R32_PTR->ESP; break;
                    case 0xE3: REGISTER::R32_PTR->EBX += REGISTER::R32_PTR->ESP; break;
                    case 0xE4: REGISTER::R32_PTR->ESP <<= 1; break;
                    case 0xE5: REGISTER::R32_PTR->EBP += REGISTER::R32_PTR->ESP; break;
                    case 0xE6: REGISTER::R32_PTR->ESI += REGISTER::R32_PTR->ESP; break;
                    case 0xE7: REGISTER::R32_PTR->EDI += REGISTER::R32_PTR->ESP; break;

                    case 0xE8: REGISTER::R32_PTR->EAX += REGISTER::R32_PTR->EBP; break;
                    case 0xE9: REGISTER::R32_PTR->ECX += REGISTER::R32_PTR->EBP; break;
                    case 0xEA: REGISTER::R32_PTR->EDX += REGISTER::R32_PTR->EBP; break;
                    case 0xEB: REGISTER::R32_PTR->EBX += REGISTER::R32_PTR->EBP; break;
                    case 0xEC: REGISTER::R32_PTR->ESP += REGISTER::R32_PTR->EBP; break;
                    case 0xED: REGISTER::R32_PTR->EBP <<= 1; break;
                    case 0xEE: REGISTER::R32_PTR->ESI += REGISTER::R32_PTR->EBP; break;
                    case 0xEF: REGISTER::R32_PTR->EDI += REGISTER::R32_PTR->EBP; break;

                    case 0xF0: REGISTER::R32_PTR->EAX += REGISTER::R32_PTR->ESI; break;
                    case 0xF1: REGISTER::R32_PTR->ECX += REGISTER::R32_PTR->ESI; break;
                    case 0xF2: REGISTER::R32_PTR->EDX += REGISTER::R32_PTR->ESI; break;
                    case 0xF3: REGISTER::R32_PTR->EBX += REGISTER::R32_PTR->ESI; break;
                    case 0xF4: REGISTER::R32_PTR->ESP += REGISTER::R32_PTR->ESI; break;
                    case 0xF5: REGISTER::R32_PTR->EBP += REGISTER::R32_PTR->ESI; break;
                    case 0xF6: REGISTER::R32_PTR->ESI <<= 1; break;
                    case 0xF7: REGISTER::R32_PTR->EDI += REGISTER::R32_PTR->ESI; break;

                    case 0xF8: REGISTER::R32_PTR->EAX += REGISTER::R32_PTR->EDI; break;
                    case 0xF9: REGISTER::R32_PTR->ECX += REGISTER::R32_PTR->EDI; break;
                    case 0xFA: REGISTER::R32_PTR->EDX += REGISTER::R32_PTR->EDI; break;
                    case 0xFB: REGISTER::R32_PTR->EBX += REGISTER::R32_PTR->EDI; break;
                    case 0xFC: REGISTER::R32_PTR->ESP += REGISTER::R32_PTR->EDI; break;
                    case 0xFD: REGISTER::R32_PTR->EBP += REGISTER::R32_PTR->EDI; break;
                    case 0xFE: REGISTER::R32_PTR->ESI += REGISTER::R32_PTR->EDI; break;
                    case 0xFF: REGISTER::R32_PTR->EDI <<= 1; break;
                    default: OUTPUT::Abort("Invalid operand");
                }

                // (int)log2(number)+1; count number of total bits


                
                    
            case 0x02: 
            case 0x03: break;
            case 0x04: REGISTER::R8_PTR->AL += operand1; break; //
            case 0x05: REGISTER::R32_PTR->EAX += operand1; break;

            case 0x80: //
                switch (operand1) {
                    case 0xC1: REGISTER::R8_PTR->CL += operand2; break;
                    case 0xC2: REGISTER::R8_PTR->DL += operand2; break;
                    case 0xC3: REGISTER::R8_PTR->BL += operand2; break;
                    case 0xC4: REGISTER::R8_PTR->AH += operand2; break;
                    case 0xC5: REGISTER::R8_PTR->CH += operand2; break;
                    case 0xC6: REGISTER::R8_PTR->DH += operand2; break;
                    case 0xC7: REGISTER::R8_PTR->BH += operand2; break;
                }
                break;
            case 0x81: break;
            default: OUTPUT::Abort("Invalid opcode");

        }
    }
 

    /*
     * Instruction: AND
     * Description: Logical AND
     * Opcode(s):   0x20...0x25, 0x80...0x81/4, 0x82...0x83/4
     */
    static inline void AND(const uint8_t &opcode, const uint8_t &operand1, const uint8_t &operand2) {
        __asm (
            ".byte 0xB8, 0x0C, 0x00, 0x00, 0x00"
        );
    }


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
     * Instruction: DEC
     * Description: Decrement by 1
     * Arguments:   None
     * Opcode(s):   0x48...0x4F, 0xFE/1, 0xFF/1
     */
    static inline void DEC(const uint8_t &prefix, const uint8_t &opcode, const uint8_t &operand1) {
        if (prefix == 0x66) {
            switch (opcode) {
                case 0x48: REGISTER::R16_PTR->AX--; break;
                case 0x49: REGISTER::R16_PTR->CX--; break;
                case 0x4A: REGISTER::R16_PTR->DX--; break;
                case 0x4B: REGISTER::R16_PTR->BX--; break;

                case 0x4C: REGISTER::R16_PTR->SP--; break;
                case 0x4D: REGISTER::R16_PTR->BP--; break;
                case 0x4E: REGISTER::R16_PTR->SI--; break;
                case 0x4F: REGISTER::R16_PTR->DI--; break;
                default: OUTPUT::Abort("Invalid opcode");
            }
            return;
        }

        switch (opcode) {
            case 0x48: REGISTER::R32_PTR->EAX--; break;
            case 0x49: REGISTER::R32_PTR->ECX--; break;
            case 0x4A: REGISTER::R32_PTR->EDX--; break;
            case 0x4B: REGISTER::R32_PTR->EBX--; break;

            case 0x4C: REGISTER::R32_PTR->ESP--; break;
            case 0x4D: REGISTER::R32_PTR->EBP--; break;
            case 0x4E: REGISTER::R32_PTR->ESI--; break;
            case 0x4F: REGISTER::R32_PTR->EDI--; break;

            if (opcode == 0xFF) {
                /*
                switch (operand1) {
                    case 0x48: REGISTER::R32_PTR->EAX--; break;
                    case 0x49: REGISTER::R32_PTR->ECX--; break;
                    case 0x4A: REGISTER::R32_PTR->EDX--; break;
                    case 0x4B: REGISTER::R32_PTR->EBX--; break;

                    case 0x4C: REGISTER::R32_PTR->ESP--; break;
                    case 0xCD: REGISTER::R32_PTR->EBP--; break;
                    case 0xCE: REGISTER::R32_PTR->ESI--; break;
                    case 0x4F: REGISTER::R32_PTR->EDI--; break;
                }
                */
            }

            case 0xFE:
                switch (operand1) {
                    case 0xC8: REGISTER::R8_PTR->AL--; break;
                    case 0xC9: REGISTER::R8_PTR->CL--; break;
                    case 0xCA: REGISTER::R8_PTR->DL--; break;
                    case 0xCB: REGISTER::R8_PTR->BL--; break;
    
                    case 0xCC: REGISTER::R8_PTR->AH--; break;
                    case 0xCD: REGISTER::R8_PTR->CH--; break;
                    case 0xCE: REGISTER::R8_PTR->DH--; break;
                    case 0xCF: REGISTER::R8_PTR->BH--; break;
                }

            default: OUTPUT::Abort("Invalid opcode");
        }
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
     * Instruction: INC
     * Description: Increment by 1
     * Arguments:   None, 1 if 0xFE
     * Opcode(s):   0x40...0x47, 0xFE/0, 0xFF/0
     */
    static inline void INC(const uint8_t &prefix, const uint8_t &opcode, const uint8_t &operand1) {
        if (prefix == 0x66) {
            switch (opcode) {
                case 0x40: REGISTER::R16_PTR->AX++; break;
                case 0x41: REGISTER::R16_PTR->CX++; break;
                case 0x42: REGISTER::R16_PTR->DX++; break;
                case 0x43: REGISTER::R16_PTR->BX++; break;

                case 0x44: REGISTER::R16_PTR->SP++; break;
                case 0x45: REGISTER::R16_PTR->BP++; break;
                case 0x46: REGISTER::R16_PTR->SI++; break;
                case 0x47: REGISTER::R16_PTR->DI++; break;
            }
            return;
        }
        
        switch (opcode) {
            case 0x40: ++REGISTER::R32_PTR->EAX; break;
            case 0x41: ++REGISTER::R32_PTR->ECX; break;
            case 0x42: ++REGISTER::R32_PTR->EDX; break;
            case 0x43: ++REGISTER::R32_PTR->EBX; break;
            case 0x44: ++REGISTER::R32_PTR->ESP; break;
            case 0x45: ++REGISTER::R32_PTR->EBP; break;
            case 0x46: ++REGISTER::R32_PTR->ESI; break;
            case 0x47: ++REGISTER::R32_PTR->EDI; break;

            case 0xFE: 
                switch (operand1) {
                    case 0xC0: ++REGISTER::R8_PTR->AL; break;
                    case 0xC1: ++REGISTER::R8_PTR->CL; break;
                    case 0xC2: ++REGISTER::R8_PTR->DL; break;
                    case 0xC3: ++REGISTER::R8_PTR->BL; break;
                    case 0xC4: ++REGISTER::R8_PTR->AH; break;
                    case 0xC5: ++REGISTER::R8_PTR->CH; break;
                    case 0xC6: ++REGISTER::R8_PTR->DH; break;
                    case 0xC7: ++REGISTER::R8_PTR->BH; break;
                }
        }
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
    static inline void MOV(const uint8_t &opcode, uint8_t operand1, uint8_t operand2, uint8_t operand3, uint8_t operand4) {
        switch (opcode) {
            case 0xBB: 
                const uint32_t lendian = operand4 << 24 | operand3 << 16 | operand2 << 8 | operand1;
                REGISTER::R32_PTR->EBX = lendian;
                break;
        }
    }

    
    /*
     * Instruction: SAL
     * Description: Arithmetic shift left
     * Arguments:   2
     * Opcode(s):   0xC0...0xC1/4, 0xD0...0xD3/4
     */
    static inline void SAL(const uint8_t &opcode, uint8_t &operand1, uint8_t &operand2) {
        //switch(opcode) {

        //}
        std::cout << opcode << operand1 << operand2;
    }


    /*
     * Instruction: POPF
     * Description: Pop FLAGS register from stack
     * Arguments:   None
     * Opcode(s):   0x9D
     */
    static inline void POPF(void) {

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

    /*
     * Instruction: XOR
     * Description: Logical exclusive OR
     * Arguments:   2
     * Opcode(s):   0x30...0x35, 0x80...0x81/6, 0x82...0x83/6
     */
    static inline void XOR(
        const uint8_t &opcode, 
        const size_t &operand1, 
        const size_t &operand2,
        const size_t &operand3, 
        const size_t &operand4) {
        uint8_t hex = opcode;
        switch (hex) {
            case 0x34: REGISTER::R8_PTR->AL ^= operand1; break;
            case 0x35: REGISTER::R8_PTR->AH ^= operand1; break;
        }
        std::cout << opcode << operand1 << operand2 << operand3 << operand4;

    }
}