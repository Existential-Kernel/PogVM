#include <iostream>
#include <cstdlib>
#include <stdint.h>
//#include <intrin.h>

//#include "CPU/registers.hpp"
//#include "CPU/memory.hpp"

class ASSEMBLY {
    public:
        bool AssemblyTest(void) {
            //__asm__ (
            //    "mov eax, ebx"
            //);
            try {
                __asm__ __volatile__ ("section .text;"
                       "global _start;"

                    "section .data"
                    "msg db  'Hello, world!', 0xa"
                    "len equ $ - msg"

                    "section .text"

                    "_start:"
                        "mov edx, len"
                        "mov ecx, msg"
                        "mov ebx, 1"
                        "mov eax, 4"
                        "int 0x80"

                        "mov ebx, 0"
                        "mov eax, 1"
                        "int 0x80"

                );
                return true;
            } catch (...) {
                return false;
            }
        }
} ASSEMBLY;
