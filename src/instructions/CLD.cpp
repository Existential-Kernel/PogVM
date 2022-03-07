#include <bitset>
#include "../cpu/registers.hpp"

// CLD
// Clear direction flag
// 0xFC

void toberenamed () {
    REGISTER::EFLAGS.flagcode[11] = 0;
}