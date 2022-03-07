#include <iostream>
#include <cstdlib>
#include <stdint.h>
//#include <intrin.h>

//#include "CPU/registers.hpp"
//#include "CPU/memory.hpp"

class ASSEMBLY {
    public:
        bool AssemblyTest(void) {
            try {
                __asm__ __volatile__ (
                    "mov eax, ebx"
                );
                return true;
            } catch (...) {
                return false;
            }
        }
} ASSEMBLY;