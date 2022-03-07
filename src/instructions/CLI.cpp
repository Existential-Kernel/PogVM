#include <bitset>
#include "../cpu/registers.hpp"

// CLI
// Clear interrupt flag
// 0xFA

void toberenamed () {
    REGISTER::EFLAGS.flagcode[10] = 0;
}