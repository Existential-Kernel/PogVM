#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>
#include <functional>
#include <memory>

#include "../cpu/flags.hpp"
#include "../cpu/registers.hpp"
#include "../cpu/stack.hpp"
#include "../defs.hpp"

#pragma once

/*
Examples:
    mov eax, [ebx] 	            ; Move the 4 bytes in memory at the address contained in EBX into EAX
    mov [var], ebx 	            ; Move the contents of EBX into the 4 bytes at memory address var. (Note, var is a 32-bit constant).
    mov eax, [esi-4] 	        ; Move 4 bytes at memory address ESI + (-4) into EAX
    mov [esi+eax], cl 	        ; Move the contents of CL into the byte at address ESI+EAX
    mov edx, [esi+4*ebx]     	; Move the 4 bytes of data at address ESI+4*EBX into EDX
*/

namespace i8088 {
    //https://stackoverflow.com/questions/24092600/how-do-ascii-adjust-and-decimal-adjust-instructions-work
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
    static inline void AAD(const uint8_t &extension, const uint8_t &operand1) {
        std::cout << operand1 << std::endl;
        if (extension == 0x0A) {
            std::cout << "something idk";
        }
    }


    /*
     * Instruction: AAM
     * Description: ASCII adjust AX after multiplication
     * Opcode(s):   0xD4
     */
    inline void AAM(void) {
        std::unique_ptr<REGISTER>REG(new REGISTER);
        REG->R8_PTR->AH = static_cast<uint8_t>(REG->R8_PTR->AL / 10);
        REG->R8_PTR->AL %= 10;
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
    static void ADD(class REGISTER REG, const uint8_t &opcode, const uint8_t &operand1, const uint8_t &operand2) {
        switch (opcode) {
            case 0x00:
                switch (operand1) {
                    case 0xC0:REG->R8_PTR->AL <<= 1; break;
                    case 0xC1:REG->R8_PTR->CL +=REG->R8_PTR->AL; break;
                    case 0xC2:REG->R8_PTR->DL +=REG->R8_PTR->AL; break;
                    case 0xC3:REG->R8_PTR->BL +=REG->R8_PTR->AL; break;
                    case 0xC4:REG->R8_PTR->AH +=REG->R8_PTR->AL; break;
                    case 0xC5:REG->R8_PTR->CH +=REG->R8_PTR->AL; break;
                    case 0xC6:REG->R8_PTR->DH +=REG->R8_PTR->AL; break;
                    case 0xC7:REG->R8_PTR->BH +=REG->R8_PTR->AL; break;

                    case 0xC8:REG->R8_PTR->AL +=REG->R8_PTR->CL; break;
                    case 0xC9:REG->R8_PTR->CL <<= 1; break;
                    case 0xCA:REG->R8_PTR->DL +=REG->R8_PTR->CL; break;
                    case 0xCB:REG->R8_PTR->BL +=REG->R8_PTR->CL; break;
                    case 0xCC:REG->R8_PTR->AH +=REG->R8_PTR->CL; break;
                    case 0xCD:REG->R8_PTR->CH +=REG->R8_PTR->CL; break;
                    case 0xCE:REG->R8_PTR->DH +=REG->R8_PTR->CL; break;
                    case 0xCF:REG->R8_PTR->BH +=REG->R8_PTR->CL; break;

                    case 0xD0:REG->R8_PTR->AL +=REG->R8_PTR->DL; break;
                    case 0xD1:REG->R8_PTR->CL +=REG->R8_PTR->DL; break;
                    case 0xD2:REG->R8_PTR->DL <<= 1; break;
                    case 0xD3:REG->R8_PTR->BL +=REG->R8_PTR->DL; break;
                    case 0xD4:REG->R8_PTR->AH +=REG->R8_PTR->DL; break;
                    case 0xD5:REG->R8_PTR->CH +=REG->R8_PTR->DL; break;
                    case 0xD6:REG->R8_PTR->DH +=REG->R8_PTR->DL; break;
                    case 0xD7:REG->R8_PTR->BH +=REG->R8_PTR->DL; break;

                    case 0xD8:REG->R8_PTR->AL +=REG->R8_PTR->BL; break;
                    case 0xD9:REG->R8_PTR->CL +=REG->R8_PTR->BL; break;
                    case 0xDA:REG->R8_PTR->DL +=REG->R8_PTR->BL; break;
                    case 0xDB:REG->R8_PTR->BL <<= 1; break;
                    case 0xDC:REG->R8_PTR->AH +=REG->R8_PTR->BL; break;
                    case 0xDD:REG->R8_PTR->CH +=REG->R8_PTR->BL; break;
                    case 0xDE:REG->R8_PTR->DH +=REG->R8_PTR->BL; break;
                    case 0xDF:REG->R8_PTR->BH +=REG->R8_PTR->BL; break;

                    case 0xE0:REG->R8_PTR->AL +=REG->R8_PTR->AH; break;
                    case 0xE1:REG->R8_PTR->CL +=REG->R8_PTR->AH; break;
                    case 0xE2:REG->R8_PTR->DL +=REG->R8_PTR->AH; break;
                    case 0xE3:REG->R8_PTR->BL +=REG->R8_PTR->AH; break;
                    case 0xE4:REG->R8_PTR->AH <<= 1; break;
                    case 0xE5:REG->R8_PTR->CH +=REG->R8_PTR->AH; break;
                    case 0xE6:REG->R8_PTR->DH +=REG->R8_PTR->AH; break;
                    case 0xE7:REG->R8_PTR->BH +=REG->R8_PTR->AH; break;

                    case 0xE8:REG->R8_PTR->AL +=REG->R8_PTR->CH; break;
                    case 0xE9:REG->R8_PTR->CL +=REG->R8_PTR->CH; break;
                    case 0xEA:REG->R8_PTR->DL +=REG->R8_PTR->CH; break;
                    case 0xEB:REG->R8_PTR->BL +=REG->R8_PTR->CH; break;
                    case 0xEC:REG->R8_PTR->AH +=REG->R8_PTR->CH; break;
                    case 0xED:REG->R8_PTR->CH <<= 1; break;
                    case 0xEE:REG->R8_PTR->DH +=REG->R8_PTR->CH; break;
                    case 0xEF:REG->R8_PTR->BH +=REG->R8_PTR->CH; break;

                    case 0xF0:REG->R8_PTR->AL +=REG->R8_PTR->DH; break;
                    case 0xF1:REG->R8_PTR->CL +=REG->R8_PTR->DH; break;
                    case 0xF2:REG->R8_PTR->DL +=REG->R8_PTR->DH; break;
                    case 0xF3:REG->R8_PTR->BL +=REG->R8_PTR->DH; break;
                    case 0xF4:REG->R8_PTR->AH +=REG->R8_PTR->DH; break;
                    case 0xF5:REG->R8_PTR->CH +=REG->R8_PTR->DH; break;
                    case 0xF6:REG->R8_PTR->DH <<= 1; break;
                    case 0xF7:REG->R8_PTR->BH +=REG->R8_PTR->DH; break;

                    case 0xF8:REG->R8_PTR->AL +=REG->R8_PTR->BH; break;
                    case 0xF9:REG->R8_PTR->CL +=REG->R8_PTR->BH; break;
                    case 0xFA:REG->R8_PTR->DL +=REG->R8_PTR->BH; break;
                    case 0xFB:REG->R8_PTR->BL +=REG->R8_PTR->BH; break;
                    case 0xFC:REG->R8_PTR->AH +=REG->R8_PTR->BH; break;
                    case 0xFD:REG->R8_PTR->CH +=REG->R8_PTR->BH; break;
                    case 0xFE:REG->R8_PTR->DH +=REG->R8_PTR->BH; break;
                    case 0xFF:REG->R8_PTR->BH <<= 1; break;
                    default: OUTPUT::Abort("Invalid operand");
                }
                break;
            case 0x01: 
                switch (operand1) {
                    case 0xC0:REG->R32_PTR->EAX <<= 1; break;
                    case 0xC1:REG->R32_PTR->ECX +=REG->R32_PTR->EAX; break;
                    case 0xC2:REG->R32_PTR->EDX +=REG->R32_PTR->EAX; break;
                    case 0xC3:REG->R32_PTR->EBX +=REG->R32_PTR->EAX; break;
                    case 0xC4:REG->R32_PTR->ESP +=REG->R32_PTR->EAX; break;
                    case 0xC5:REG->R32_PTR->EBP +=REG->R32_PTR->EAX; break;
                    case 0xC6:REG->R32_PTR->ESI +=REG->R32_PTR->EAX; break;
                    case 0xC7:REG->R32_PTR->EDI +=REG->R32_PTR->EAX; break;

                    case 0xC8:REG->R32_PTR->EAX +=REG->R32_PTR->ECX; break;
                    case 0xC9:REG->R32_PTR->ECX <<= 1; break;
                    case 0xCA:REG->R32_PTR->EDX +=REG->R32_PTR->ECX; break;
                    case 0xCB:REG->R32_PTR->EBX +=REG->R32_PTR->ECX; break;
                    case 0xCC:REG->R32_PTR->ESP +=REG->R32_PTR->ECX; break;
                    case 0xCD:REG->R32_PTR->EBP +=REG->R32_PTR->ECX; break;
                    case 0xCE:REG->R32_PTR->ESI +=REG->R32_PTR->ECX; break;
                    case 0xCF:REG->R32_PTR->EDI +=REG->R32_PTR->ECX; break;

                    case 0xD0:REG->R32_PTR->EAX +=REG->R32_PTR->EDX; break;
                    case 0xD1:REG->R32_PTR->ECX +=REG->R32_PTR->EDX; break;
                    case 0xD2:REG->R32_PTR->EDX <<= 1; break;
                    case 0xD3:REG->R32_PTR->EBX +=REG->R32_PTR->EDX; break;
                    case 0xD4:REG->R32_PTR->ESP +=REG->R32_PTR->EDX; break;
                    case 0xD5:REG->R32_PTR->EBP +=REG->R32_PTR->EDX; break;
                    case 0xD6:REG->R32_PTR->ESI +=REG->R32_PTR->EDX; break;
                    case 0xD7:REG->R32_PTR->EDI +=REG->R32_PTR->EDX; break;

                    case 0xD8:REG->R32_PTR->EAX +=REG->R32_PTR->EBX ; break;
                    case 0xD9:REG->R32_PTR->ECX +=REG->R32_PTR->EBX ; break;
                    case 0xDA:REG->R32_PTR->EDX +=REG->R32_PTR->EBX ; break;
                    case 0xDB:REG->R32_PTR->EBX <<= 1; break;
                    case 0xDC:REG->R32_PTR->ESP +=REG->R32_PTR->EBX ; break;
                    case 0xDD:REG->R32_PTR->EBP +=REG->R32_PTR->EBX ; break;
                    case 0xDE:REG->R32_PTR->ESI +=REG->R32_PTR->EBX ; break;
                    case 0xDF:REG->R32_PTR->EDI +=REG->R32_PTR->EBX ; break;

                    case 0xE0:REG->R32_PTR->EAX +=REG->R32_PTR->ESP; break;
                    case 0xE1:REG->R32_PTR->ECX +=REG->R32_PTR->ESP; break;
                    case 0xE2:REG->R32_PTR->EDX +=REG->R32_PTR->ESP; break;
                    case 0xE3:REG->R32_PTR->EBX +=REG->R32_PTR->ESP; break;
                    case 0xE4:REG->R32_PTR->ESP <<= 1; break;
                    case 0xE5:REG->R32_PTR->EBP +=REG->R32_PTR->ESP; break;
                    case 0xE6:REG->R32_PTR->ESI +=REG->R32_PTR->ESP; break;
                    case 0xE7:REG->R32_PTR->EDI +=REG->R32_PTR->ESP; break;

                    case 0xE8:REG->R32_PTR->EAX +=REG->R32_PTR->EBP; break;
                    case 0xE9:REG->R32_PTR->ECX +=REG->R32_PTR->EBP; break;
                    case 0xEA:REG->R32_PTR->EDX +=REG->R32_PTR->EBP; break;
                    case 0xEB:REG->R32_PTR->EBX +=REG->R32_PTR->EBP; break;
                    case 0xEC:REG->R32_PTR->ESP +=REG->R32_PTR->EBP; break;
                    case 0xED:REG->R32_PTR->EBP <<= 1; break;
                    case 0xEE:REG->R32_PTR->ESI +=REG->R32_PTR->EBP; break;
                    case 0xEF:REG->R32_PTR->EDI +=REG->R32_PTR->EBP; break;

                    case 0xF0:REG->R32_PTR->EAX +=REG->R32_PTR->ESI; break;
                    case 0xF1:REG->R32_PTR->ECX +=REG->R32_PTR->ESI; break;
                    case 0xF2:REG->R32_PTR->EDX +=REG->R32_PTR->ESI; break;
                    case 0xF3:REG->R32_PTR->EBX +=REG->R32_PTR->ESI; break;
                    case 0xF4:REG->R32_PTR->ESP +=REG->R32_PTR->ESI; break;
                    case 0xF5:REG->R32_PTR->EBP +=REG->R32_PTR->ESI; break;
                    case 0xF6:REG->R32_PTR->ESI <<= 1; break;
                    case 0xF7:REG->R32_PTR->EDI +=REG->R32_PTR->ESI; break;

                    case 0xF8:REG->R32_PTR->EAX +=REG->R32_PTR->EDI; break;
                    case 0xF9:REG->R32_PTR->ECX +=REG->R32_PTR->EDI; break;
                    case 0xFA:REG->R32_PTR->EDX +=REG->R32_PTR->EDI; break;
                    case 0xFB:REG->R32_PTR->EBX +=REG->R32_PTR->EDI; break;
                    case 0xFC:REG->R32_PTR->ESP +=REG->R32_PTR->EDI; break;
                    case 0xFD:REG->R32_PTR->EBP +=REG->R32_PTR->EDI; break;
                    case 0xFE:REG->R32_PTR->ESI +=REG->R32_PTR->EDI; break;
                    case 0xFF:REG->R32_PTR->EDI <<= 1; break;
                    default: OUTPUT::Abort("Invalid operand");
                }

                // (int)log2(number)+1; count number of total bits


                
                    
            case 0x02: 
            case 0x03: break;
            case 0x04:REG->R8_PTR->AL += operand1; break; //
            case 0x05:REG->R32_PTR->EAX += operand1; break;

            case 0x80: //
                switch (operand1) {
                    case 0xC1:REG->R8_PTR->CL += operand2; break;
                    case 0xC2:REG->R8_PTR->DL += operand2; break;
                    case 0xC3:REG->R8_PTR->BL += operand2; break;
                    case 0xC4:REG->R8_PTR->AH += operand2; break;
                    case 0xC5:REG->R8_PTR->CH += operand2; break;
                    case 0xC6:REG->R8_PTR->DH += operand2; break;
                    case 0xC7:REG->R8_PTR->BH += operand2; break;
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
/*
    static inline void AND(const uint8_t &opcode, const uint8_t &operand1, const uint8_t &operand2) {
        __asm (
            ".byte 0xB8, 0x0C, 0x00, 0x00, 0x00"
        );
    }
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
     * Instruction: DEC
     * Description: Decrement by 1
     * Arguments:   None
     * Opcode(s):   0x48...0x4F, 0xFE/1, 0xFF/1
     */
    static inline void DEC(const uint8_t &prefix, const uint8_t &opcode, const uint8_t &operand1) {
        std::unique_ptr<REGISTER>REG(new REGISTER);
        if (prefix == 0x66) {
            switch (opcode) {
                case 0x48:REG->R16_PTR->AX--; break;
                case 0x49:REG->R16_PTR->CX--; break;
                case 0x4A:REG->R16_PTR->DX--; break;
                case 0x4B:REG->R16_PTR->BX--; break;

                case 0x4C:REG->R16_PTR->SP--; break;
                case 0x4D:REG->R16_PTR->BP--; break;
                case 0x4E:REG->R16_PTR->SI--; break;
                case 0x4F:REG->R16_PTR->DI--; break;
                default: OUTPUT::Abort("Invalid opcode");
            }
            return;
        }

        switch (opcode) {
            case 0x48:REG->R32_PTR->EAX--; break;
            case 0x49:REG->R32_PTR->ECX--; break;
            case 0x4A:REG->R32_PTR->EDX--; break;
            case 0x4B:REG->R32_PTR->EBX--; break;

            case 0x4C:REG->R32_PTR->ESP--; break;
            case 0x4D:REG->R32_PTR->EBP--; break;
            case 0x4E:REG->R32_PTR->ESI--; break;
            case 0x4F:REG->R32_PTR->EDI--; break;

            if (opcode == 0xFF) {
                /*
                switch (operand1) {
                    case 0x48:REG->R32_PTR->EAX--; break;
                    case 0x49:REG->R32_PTR->ECX--; break;
                    case 0x4A:REG->R32_PTR->EDX--; break;
                    case 0x4B:REG->R32_PTR->EBX--; break;

                    case 0x4C:REG->R32_PTR->ESP--; break;
                    case 0xCD:REG->R32_PTR->EBP--; break;
                    case 0xCE:REG->R32_PTR->ESI--; break;
                    case 0x4F:REG->R32_PTR->EDI--; break;
                }
                */
            }

            case 0xFE:
                switch (operand1) {
                    case 0xC8:REG->R8_PTR->AL--; break;
                    case 0xC9:REG->R8_PTR->CL--; break;
                    case 0xCA:REG->R8_PTR->DL--; break;
                    case 0xCB:REG->R8_PTR->BL--; break;
    
                    case 0xCC:REG->R8_PTR->AH--; break;
                    case 0xCD:REG->R8_PTR->CH--; break;
                    case 0xCE:REG->R8_PTR->DH--; break;
                    case 0xCF:REG->R8_PTR->BH--; break;
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
        std::unique_ptr<REGISTER>REG(new REGISTER);
        if (prefix == 0x66) {
            switch (opcode) {
                case 0x40:REG->R16_PTR->AX++; break;
                case 0x41:REG->R16_PTR->CX++; break;
                case 0x42:REG->R16_PTR->DX++; break;
                case 0x43:REG->R16_PTR->BX++; break;

                case 0x44:REG->R16_PTR->SP++; break;
                case 0x45:REG->R16_PTR->BP++; break;
                case 0x46:REG->R16_PTR->SI++; break;
                case 0x47:REG->R16_PTR->DI++; break;
            }
            return;
        }
        
        switch (opcode) {
            case 0x40: REG->R32_PTR->EAX; break;
            case 0x41: REG->R32_PTR->ECX; break;
            case 0x42: REG->R32_PTR->EDX; break;
            case 0x43: REG->R32_PTR->EBX; break;
            case 0x44: REG->R32_PTR->ESP; break;
            case 0x45: REG->R32_PTR->EBP; break;
            case 0x46: REG->R32_PTR->ESI; break;
            case 0x47: REG->R32_PTR->EDI; break;

            case 0xFE: 
                switch (operand1) {
                    case 0xC0: REG->R8_PTR->AL; break;
                    case 0xC1: REG->R8_PTR->CL; break;
                    case 0xC2: REG->R8_PTR->DL; break;
                    case 0xC3: REG->R8_PTR->BL; break;
                    case 0xC4: REG->R8_PTR->AH; break;
                    case 0xC5: REG->R8_PTR->CH; break;
                    case 0xC6: REG->R8_PTR->DH; break;
                    case 0xC7: REG->R8_PTR->BH; break;
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
        std::unique_ptr<REGISTER>REG(new REGISTER);
        switch (opcode) {
            case 0xBB: 
                const uint32_t lendian = operand4 << 24 | operand3 << 16 | operand2 << 8 | operand1;
               REG->R32_PTR->EBX = lendian;
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
        std::unique_ptr<REGISTER>REG(new REGISTER);
        uint8_t hex = opcode;
        switch (hex) {
            case 0x34:REG->R8_PTR->AL ^= operand1; break;
            case 0x35:REG->R8_PTR->AH ^= operand1; break;
        }
        std::cout << opcode << operand1 << operand2 << operand3 << operand4;

    }

        /*
     * Instruction: TEST
     * Description: add 1 to register AH, this is not an actual instruction just to be clear.
     * Opcode(s):   0x0E
     */
    inline void TEST(uint8_t operand1 = 1, uint8_t operand2 = 1) {
        std::unique_ptr<REGISTER>REG(new REGISTER);
        REG->R8_PTR->AH += operand1 + operand2;
        std::cout << "AH = " << static_cast<int>(REG->R8_PTR->AH) << std::endl;
    }

//    static void Create8088(void) {

        //typedef std::tuple<std::string, std::function<void()>, uint8_t> maptup;
        
        std::map<size_t, std::tuple<std::string, std::function<void()>, uint8_t>> instructions;
/*
        instructions = {
            0x37: std::tuple<"AAA", &AAA, 0>,
        }
*/
        //instructions[0x37] = std::tuple<"AAA", &AAA, 0>;

/*
        std::map<size_t, std::pair<std::string, auto, uint8_t> instructions = {
            //{ 0x37, std::make_tuple("AAA", &AAA, 0) },
            //{ 0xD4, std::make_tuple("AAD", &AAD, 0) },
            //{ 0xD5, std::make_tuple("AAM", &AAM, 0) },
            //{ 0xE1, std::make_tuple("TEST", &TEST , 2) },
            { 0xF8, std::make_tuple("CLC", &CLC, 0) },
            { 0xFA, std::make_tuple("CLI", &CLI, 0) },
            { 0xFC, std::make_tuple("CLD", &CLD, 0) },
\
            //{ 0xD50A, std::mmake_tuple("AAD", &AAD), 1 },
        };
*/
        

        // to call function: menu[a]();
    //}
}