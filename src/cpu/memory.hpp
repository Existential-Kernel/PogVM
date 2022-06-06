#include <iostream>
#include <cstdint>
#include <cmath>

#pragma once

namespace MEMORY {
    using u32 = unsigned int;
    static constexpr u32 MAX_MEM = 1 << 16; // 2^16 bits of memory
    static unsigned char memory[MAX_MEM];

    static inline bool Initialise(void) {
        try {
            for (u32 i = 0; i < MAX_MEM; ++i) {
                memory[i] = 0;
            }
            return true;
        } catch (...) {
            return false;
        }
    }
};