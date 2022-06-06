#include <iostream>

#include "../cpu/flags.hpp"
#include "../cpu/registers.hpp"


namespace iTesting {
    /*
     * Instruction: TEST
     * Description: add 1 to register AH, this is not an actual instruction just to be clear.
     * Opcode(s):   0x01
     */
    inline void TEST(uint8_t operand1 = 1, uint8_t operand2 = 1) {
        std::unique_ptr<REGISTER>REG(new REGISTER);
        REG->R8_PTR->AH += operand1 + operand2;
        std::cout << "AH = " << static_cast<int>(REG->R8_PTR->AH) << std::endl;
    }
}