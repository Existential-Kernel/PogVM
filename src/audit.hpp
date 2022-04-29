#include <iostream>
#include <cstdint>
#include <tuple>
#include <string>
#include <sstream>
#include <cstring>

#include "cpu/registers.hpp"
#include "cpu/memory.hpp"
//#include "tests/assembly.hpp"
#include "defs.hpp"


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

namespace AUDIT {
    // Log the initialisation process if it succeeded or failed
    static void AuditLog(bool result, const std::string &message) {
        if (result) {
            std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT<< std::endl;
        } else {
            std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT << std::endl;
        }
    }

    // Checks all the necessary processes and data needed to run the machine
    void AuditCheck(void) {
        AuditLog(MEMORY::Initialise(), "2^32 bits of memory space allocated");
        //AuditLog(REGISTER.ResetAll(), "All registers have been reset");
        AuditLog(KERNEL::CoreCheck(), "CPU working as expected");
        AuditLog(KERNEL::ThreadCheck(), "Verified for necessary thread count for pipeline processing");
        //AuditLog(ASSEMBLY::AssemblyTest(), "Tested x86 assembly code");
    }
};
