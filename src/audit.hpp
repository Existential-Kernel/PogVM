#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <tuple>
#include <string>

#include "CPU/registers.hpp"
#include "CPU/memory.hpp"
#include "tests/assembly.hpp"

namespace ANSI {
    static const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    static const char *RED = "\x1B[38;2;255;0;0m";
    static const char *GREEN = "\x1B[38;2;0;255;0m";
    static const char *TERMINATE = "\x1B[0m";
    //static const char *BOLD = "\e[1m";
    //static const char *NOTBOLD = "\e[0m";
}

class AUDIT {
    private:
        static void AuditLog(bool result, std::string message) {
            if (result) { 
                std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::TERMINATE << "] " << message << std::endl;
            } else {
                std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::TERMINATE << "] " << message << std::endl;
            }
        }

    public:
        void AuditCheck(void) {
            AuditLog(REGISTER.ResetAll(), "\e[1mAll registers have been reset\e[0m");
            AuditLog(MEMORY.Initialise(), "\e[1m2^32 memory space allocated\e[0m");
            //AuditLog(ASSEMBLY.AssemblyTest(), "Tested x86 assembly code");
        }
} AUDIT;