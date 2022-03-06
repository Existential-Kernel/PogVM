#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <tuple>
#include <string>
#include <sstream>

#include "cpu/registers.hpp"
#include "cpu/memory.hpp"
#include "tests/assembly.hpp"

namespace ANSI {
    static const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    static const char *RED = "\x1B[38;2;255;0;0m";
    static const char *GREEN = "\x1B[38;2;0;255;0m";
    static const char *EXIT = "\x1B[0m";

    static std::ostream &BOLD(std::ostream& log) { return log << "\e[1m"; }
    static std::ostream &NOBOLD(std::ostream& log) { return log << "\e[0m"; }
}

class AUDIT {
    private:
        static void AuditLog(bool result, std::string message) {
            result \
                ? std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::NOBOLD << std::endl
                : std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::NOBOLD << std::endl;
        }

    public:
        void AuditCheck(void) {
            AuditLog(REGISTER::ResetAll(), "All registers have been reset");
            AuditLog(MEMORY.Initialise(), "2^32 bits of memory space allocated");
            //AuditLog(ASSEMBLY.AssemblyTest(), "Tested x86 assembly code");
        }
} AUDIT;