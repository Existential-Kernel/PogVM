#include <iostream>
#include <cstdint>

using u32 = unsigned int;

class MEMORY {
    private:
        static constexpr u32 MAX_MEM = 1024 * 64;
        unsigned char memory[MAX_MEM];

    public:
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
} MEMORY;