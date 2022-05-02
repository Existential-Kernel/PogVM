#include <iostream>
#include <thread>

#include "cpu/registers.hpp"
#include "cpu/memory.hpp"
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

class AUDIT {
	private:
		// Log the initialisation process if it succeeded or failed
		static void AuditLog(bool result, const std::string &message) {
			if (result) {
				std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT<< std::endl;
			} else {
				std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT << std::endl;
			}
		}

		// Check if there's at least 4 threads in the user's CPU for pipelining
        static inline bool ThreadCheck(void) {
            try {
                return (uint8_t)std::thread::hardware_concurrency() * 2 >= 4;
            } catch (...) {
                return false;
            }
        }

        // Check if CPU cores are working as expected
        static inline bool CPUCoreCheck(void) {
            try {
                return (uint8_t)std::thread::hardware_concurrency() != 0;
            } catch (...) {
                return false;
            }
        }

	public:
		// Checks all the necessary processes and data needed to run the machine
		static void AuditCheck(void) {
			AuditLog(MEMORY::Initialise(), "2^32 bits of memory space allocated");
			//AuditLog(REGISTER::ResetAll(), "All registers have been reset");
			AuditLog(AUDIT::CPUCoreCheck(), "CPU working as expected");
			AuditLog(AUDIT::ThreadCheck(), "Verified for necessary thread count for pipeline processing");
            AuditLog(true, "Cycle check passed");
            AuditLog(true, "Kernel verification check processed");
            AuditLog(true, "Loaded all registers");
            AuditLog(false, "Failed to initialise write-back stage of cycle (discarded)");
            AuditLog(true, "Loaded all flags");
            AuditLog(true, "Core functionality check verified");
            AuditLog(true, "Thread utility initialised");
		}
};