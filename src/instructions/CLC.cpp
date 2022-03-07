#include <bitset>

#include "../cpu/registers.hpp"

// CLC
// Clear carry flag
// 0xF8

void toberenamed () {
    REGISTER::EFLAGS.flagcode[0] = 0; 
}