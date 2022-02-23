#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <tuple>
#include <string>

#include "CPU/registers.hpp"
#include "CPU/memory.hpp"

namespace ANSI {
    static const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    static const char *RED = "\x1B[38;2;255;0;0m";
    static const char *GREEN = "\x1B[38;2;0;255;0m";
    static const char *TERMINATE = "\x1B[0m";
}

class AUDIT {
    private:
        std::tuple<bool, std::string> static AuditLog(bool result, std::string message) {
            if (result) { 
                std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::TERMINATE << "] " << message << std::endl;
            } else {
                std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::TERMINATE << "] " << message << std::endl;
            }
        }

    public:
        void AuditCheck(void) {
            AuditLog(REGISTER.ResetAll(), "All registers have been reset");
            AuditLog(MEMORY.Initialise(), "2^32 memory space allocated");
        }
} AUDIT;