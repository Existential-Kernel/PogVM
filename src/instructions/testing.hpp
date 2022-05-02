#include <iostream>

#include "../cpu/flags.hpp"
#include "../cpu/registers.hpp"

namespace iTesting {
    /*
     * Instruction: TEST
     * Description: add 1 to register AH, this is not an actual instruction just to be clear.
     * Opcode(s):   0x01
     */
    inline void TEST(uint8_t operand1 = 1) {
        REGISTER::R8_PTR->AH += operand1;
        std::cout << "AH = " << (int)REGISTER::R8_PTR->AH << std::endl;
    }
}