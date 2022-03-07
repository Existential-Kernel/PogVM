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

// Reset all registers to 0
bool REGISTER::ResetAll(void) {
    try {
        memset(&REGISTER::GPR, 0, sizeof(REGISTER::GPR));
        memset(&REGISTER::SREG, 0, sizeof(REGISTER::SREG));
        memset(&REGISTER::PREG, 0, sizeof(REGISTER::PREG));
        EFLAGS::flagcode = 0;
        return true;
    } catch (...) {
        return false;
    }
}

// Check if there's at least 4 threads in the user's CPU for pipelining
bool ThreadCheck(void) {
    try {
        const auto processorCount = std::thread::hardware_concurrency();
        const unsigned int threadCount = processorCount * 2;
        if (threadCount >= 4) {
            return true;
        }

        return false; 
    } catch (...) {
        return false;
    }
}

// Check if CPU cores are working as expected
bool CoreCheck(void) {
    try {
        const auto processorCount = std::thread::hardware_concurrency();
        if (processorCount != 0) {
            return true;
        }

        return false; 
    } catch (...) {
        return false;
    }
}

namespace AUDIT {
    static void AuditLog(bool result, std::string message) {
        result \
            ? std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::NOBOLD << std::endl
            : std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::NOBOLD << std::endl;
    }

    void AuditCheck(void) {
        AuditLog(REGISTER::ResetAll(), "All registers have been reset");
        AuditLog(MEMORY::Initialise(), "2^32 bits of memory space allocated");
        AuditLog(CoreCheck(), "CPU working as expected");
        AuditLog(ThreadCheck(), "There are enough threads for pipeline processing");
        //AuditLog(ASSEMBLY.AssemblyTest(), "Tested x86 assembly code");
    }
};