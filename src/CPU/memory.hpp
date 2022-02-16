#include <iostream>
#include <cstdint>

using u32 = unsigned int;

struct MEMORY {
    static constexpr u32 MAX_MEM = 1024 * 64;
    unsigned char memory[MAX_MEM];

    void INITIALISE() {
        for (u32 i = 0; i < MAX_MEM; i++) {
            memory[i] = 0;
        }
    }
};