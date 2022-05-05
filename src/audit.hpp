#include <iostream>
#include <thread>

#include "cpu/registers.hpp"
#include "cpu/memory.hpp"
#include "defs.hpp"
#include "instructions/8086-8088.hpp"


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
				std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "]  " << ANSI::BOLD << message << ANSI::EXIT << std::endl;
                std::exit(1);
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

        static bool Check8088(void) {
            try {
                // Cancel out the flag code 
                i8088::STC(); i8088::CLC();
                i8088::STI(); i8088::CLI();
                i8088::STD(); i8088::CLD();
                if (FLAGS::EFLAGS_PTR->eflagcode != 0) { return false; }
                FLAGS::EFLAGS_PTR->Reset();

                return true;
            } catch (...) {
                return false;
            }
        }

	public:
		// Checks all the necessary processes and data needed to run the machine
		static void AuditCheck(void) {
			AuditLog(MEMORY::Initialise(), "Allocating 2^16 bits of memory space...");
			//AuditLog(REGISTER::ResetAll(), "All registers have been reset");
			AuditLog(AUDIT::CPUCoreCheck(), "Checking CPU compatibility...");
			AuditLog(AUDIT::ThreadCheck(), "Checking thread utilisation...");
            AuditLog(AUDIT::Check8088(), "Verifying 8086/8088 instruction set...");
		}
};