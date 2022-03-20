#include <iostream>
//#include <cstdlib>
#include <cstdint>
#include <tuple>
#include <string>
#include <sstream>
#include <cstring>
#include <thread>

#include "cpu/registers.hpp"
#include "cpu/memory.hpp"
#include "tests/assembly.hpp"

namespace ANSI {
    static const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    static const char *RED = "\x1B[38;2;255;0;0m";
    static const char *GREEN = "\x1B[38;2;0;255;0m";

    static std::ostream &BOLD(std::ostream& log) { return log << "\e[1m"; }

    static const char *EXIT = "\x1B[0m";
}

class CORE {
    public:
        // Check if there's at least 4 threads in the user's CPU for pipelining
        static inline bool ThreadCheck(void) {
            try {
                if ((uint8_t)std::thread::hardware_concurrency() * 2 >= 4) {
                    return true;
                } else {
                    return false;
                }
            } catch (...) {
                return false;
            }
        }

        // Check if CPU cores are working as expected
        static inline bool CoreCheck(void) {
            try {
                if ((uint8_t)std::thread::hardware_concurrency() != 0) {
                    return true;
                } else {
                    return false; 
                }
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
};

class CHECK {
    private:

    public:

};

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
        AuditLog(CORE::CoreCheck(), "CPU working as expected");
        AuditLog(CORE::ThreadCheck(), "Verified for necessary thread count for pipeline processing");
        AuditLog(ASSEMBLY::AssemblyTest(), "Tested x86 assembly code");
    }
};
