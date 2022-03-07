#include <iostream>
#include <cstdint>
#include <cmath>
#include <math.h>

#ifndef MEM
#define MEM

using u32 = unsigned int;

namespace MEMORY {
    static constexpr u32 MAX_MEM = 1024 * 64; // 2^32 bits of memory
    unsigned char memory[MAX_MEM];

    bool Initialise(void) {
        try {
            for (u32 i = 0; i < MAX_MEM; i++) {
                memory[i] = 0;
            }
            return true;
        } catch (...) {
            return false;
        }
    }
};

#endif