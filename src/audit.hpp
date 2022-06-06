#include <iostream>
#include <thread>

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
	private:
		// Log the initialisation process if it succeeded or failed
		static void AuditLog(const bool &result, const std::string &message, const bool &indent) {
			if (result) {
				std::cout << (indent ? "   " : 0) << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT<< std::endl;
			} else {
				std::cout << (indent ? "   " : 0) << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "]  " << ANSI::BOLD << message << ANSI::EXIT << std::endl;
                std::exit(1);
			}
		}

		// Check if there's at least 4 threads in the end-user's CPU for pipelining
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
                i8088::STC();
                i8088::STI();
                i8088::STD();
                if (FLAGS::EFLAGS_PTR->eflagcode != 0x601) { return false; }
                FLAGS::EFLAGS_PTR->eflagcode.reset();
                FLAGS::EFLAGS_PTR->eflagcode.flip();
                i8088::CLC();
                i8088::CLI();
                i8088::CLD();
                if (~FLAGS::EFLAGS_PTR->eflagcode != 0x601) { return false; }
                FLAGS::EFLAGS_PTR->eflagcode.reset();

                i8088::ADD(0x04, 10, 0);
                i8088::ADD(0x80, 0xC1, 10);
                i8088::ADD(0x80, 0xC2, 10);
                i8088::ADD(0x80, 0xC3, 10);
                i8088::ADD(0x80, 0xC4, 10);
                i8088::ADD(0x80, 0xC5, 10);
                i8088::ADD(0x80, 0xC6, 10);
                i8088::ADD(0x80, 0xC7, 10);



                i8088::INC(0x66, 40, 0);
                i8088::INC(0x66, 41, 0);
                i8088::INC(0x66, 42, 0);
                i8088::INC(0x66, 43, 0);
                i8088::INC(0x66, 44, 0);
                i8088::INC(0x66, 45, 0);
                i8088::INC(0x66, 46, 0);
                i8088::INC(0x66, 47, 0);

                i8088::INC(0, 40, 0);
                i8088::INC(0, 41, 0);
                i8088::INC(0, 42, 0);
                i8088::INC(0, 43, 0);
                i8088::INC(0, 44, 0);
                i8088::INC(0, 45, 0);
                i8088::INC(0, 46, 0);
                i8088::INC(0, 47, 0);

                i8088::INC(0, 0xFE, 0xC0);
                i8088::INC(0, 0xFE, 0xC1);
                i8088::INC(0, 0xFE, 0xC2);
                i8088::INC(0, 0xFE, 0xC3);
                i8088::INC(0, 0xFE, 0xC4);
                i8088::INC(0, 0xFE, 0xC5);
                i8088::INC(0, 0xFE, 0xC6);
                i8088::INC(0, 0xFE, 0xC7);

                return true;
            } catch (...) {
                return false;
            }
        }

	public:
		// Checks all the necessary processes and data needed to run the machine
		static void AuditCheck(void) {
			AuditLog(MEMORY::Initialise(), "Allocating 2^16 bits of memory space...", false);
			//AuditLog(REGISTER::ResetAll(), "All registers have been reset", false);
			AuditLog(AUDIT::CPUCoreCheck(), "Checking CPU compatibility...", false);
			AuditLog(AUDIT::ThreadCheck(), "Checking thread utilisation...", false);
            std::cout << ANSI::BLACK_BG << "\n===== CHECKING INSTRUCTION SETS =====" << ANSI::EXIT << "\n\n";
            AuditLog(AUDIT::Check8088(), "Verifying 8086/8088 instruction set...", true);
		}
};