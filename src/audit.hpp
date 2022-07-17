#include <iostream>
#include <thread>
#include <immintrin.h>

#include "cpu/registers.hpp"
#include "cpu/memory.hpp"
#include "defs.hpp"
#include "instructions/8086-8088.hpp"

#pragma once

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
    public:
        AUDIT() {};
        ~AUDIT() {};

	private:
		// Log the initialisation process if it succeeded or failed
		constexpr static void AuditLog(const uint8_t &result, const std::string &message, const std::string &warnmessage = "") {
			switch (result) {
                case 1: std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT << std::endl; break;
                case 2: std::cout << "┌─[" << ANSI::BLACK_BG << ANSI::ORANGE << "WARNING" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT << std::endl;
                        std::cout << "└───>" << ANSI::BOLD << warnmessage << ANSI::EXIT << std::endl;
                case 0: std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "]  " << ANSI::BOLD << message << ANSI::EXIT << std::endl; std::exit(1); break;
            }
		}

        [[nodiscard]] constexpr static inline bool ArchCheck(void) {
            bool knownArch = false;
            #if defined(__ARM_ARCH_7A__)
                knownArch = true;
            #elif defined(__x86_64__)
                knownArch = true;
            #elif defined(__i386__)
                knownArch = true;
            #endif
            return knownArch;
        }

		// Check if there's at least 4 threads in the end-user's CPU for pipelining
        [[nodiscard]] static inline bool ThreadCheck(void) {
            try {
                return (std::thread::hardware_concurrency() * 2 >= 4);
            } catch (...) {
                return false;
            }
        }

        // Check if CPU cores are working as expected
        [[nodiscard]] static inline bool CPUCoreCheck(void) {
            try {
                return (std::thread::hardware_concurrency() != 0); 
            } catch (...) {
                return false;
            }
        }

        [[nodiscard]] static inline bool CPUClockSpeedCheck(void) {
            try {
                return (UTIL::getClockSpeed() > 16000);
            } catch (...) {
                return false;
            }
        }

	public:
		// Checks all the necessary processes and data needed to run the machine
		static void AuditCheck(void) {
			AuditLog(MEMORY::Initialise(), "Allocating 2^16 bits of memory space...");
            AuditLog(AUDIT::ArchCheck(), "Checking for architecture compatibility...");
			//AuditLog(REGISTER::ResetAll(), "All registers have been reset", false);
			AuditLog(AUDIT::CPUCoreCheck(), "Checking CPU compatibility...");
			AuditLog(AUDIT::ThreadCheck(), "Checking threading compatibility...");
            AuditLog(AUDIT::CPUClockSpeedCheck(), "Checking CPU clock speed compatibility...");
		}
};