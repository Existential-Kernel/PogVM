#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <tuple>
#include <string>
#include <sstream>
#include <cstring>

#include "cpu/registers.hpp"
#include "cpu/memory.hpp"
#include "tests/assembly.hpp"

namespace ANSI {
    static const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    static const char *RED = "\x1B[38;2;255;0;0m";
    static const char *GREEN = "\x1B[38;2;0;255;0m";

    static std::ostream &BOLD(std::ostream& log) { return log << "\e[1m"; }
    static std::ostream &NOBOLD(std::ostream& log) { return log << "\e[0m"; }

    static const char *EXIT = "\x1B[0m";
}

namespace CORE {
    // Check if there's at least 4 threads in the user's CPU for pipelining
    static bool ThreadCheck(void) {
        try {
            const unsigned int processorCount = std::thread::hardware_concurrency();
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
    static bool CoreCheck(void) {
        try {
            const unsigned int processorCount = std::thread::hardware_concurrency();
            if (processorCount != 0) {
                return true;
            }

            return false; 
        } catch (...) {
            return false;
        }
    }

// TODO: Fix the ResetAll() function
/*
    // Reset all registers to 0
    bool ResetAll(void) {
        try {
            memset(&R64, 0, sizeof R64);
            memset(&SREG, 0, sizeof SREG);
            memset(&PREG, 0, sizeof PREG);

            return true;
        } catch (...) {
            return false;
        }
    }
*/
}

namespace AUDIT {

    // Log the process if it succeeded or failed
    static void AuditLog(bool result, const std::string &message) {
        if (result) {
            std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::NOBOLD << std::endl;
        } else {
            std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::NOBOLD << std::endl;
        }
    }

    // Checks all the necessary processes and data needed to run PogCPU
    void AuditCheck(void) {
        AuditLog(MEMORY::Initialise(), "2^32 bits of memory space allocated");
        //AuditLog(REGISTER.ResetAll(), "All registers have been reset");
        AuditLog(CORE::CoreCheck(), "CPU working as expected");
        AuditLog(CORE::ThreadCheck(), "Verified for necessary thread count for pipeline processing");
        AuditLog(ASSEMBLY.AssemblyTest(), "Tested x86 assembly code");
    }
};