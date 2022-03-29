#include <iostream>
#include <cstdint>
#include <cmath>
#include <math.h>
//#include <climits>

#ifndef MEM
#define MEM

using u32 = unsigned int;

namespace MEMORY {
    static constexpr u32 MAX_MEM = 65536; // 2^16 bits of memory
    unsigned char memory[MAX_MEM];

    inline bool Initialise(void) {
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