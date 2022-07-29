#pragma once
#include "defs.hpp"
#include "cpu/memory.hpp"

class AUDIT {
    public:
        AUDIT() {};
        ~AUDIT() {};

    private:
        // Log the initialisation process if it succeeded or failed
        static constexpr void AuditLog(const uint8_t &result, const std::string &message) {
            switch (result) {
                case 1: std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT << std::endl; break;
                /*
                case 2: std::cout << "┌─[" << ANSI::BLACK_BG << ANSI::ORANGE << "WARNING" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT << std::endl;
                        std::cout << "└───>" << ANSI::BOLD << warnmessage << ANSI::EXIT << std::endl;
                */
                case 0: std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "]  " << ANSI::BOLD << message << ANSI::EXIT << std::endl; std::exit(1); break;
            }
        }

        // Check if the architecture is recognised
        [[nodiscard]] static constexpr inline bool ArchCheck(void) {
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
        [[nodiscard]] static inline bool CPUThreadCheck(void) {
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

        // Check if the clock speed is fast enough for accurate clock-cycle emulation for old processors
        [[nodiscard]] static inline bool CPUClockSpeedCheck(void) {
            try {
                return (UTIL::getClockSpeed() > 16000);
            } catch (...) {
                return false;
            }
        }

        // Check if objcopy is installed in end-user's system
        [[nodiscard]] static bool objcopyCheck(void) {
            if (UTIL::FileExists("/usr/bin/objcopy")) {
                return true;
            } else {
                std::future<bool> result = std::async(std::launch::async, []()
                    {
                        // TODO: Improve this part, this code is awkward and creaky as fuck
                        try {
                            std::system("cd ./bin/ && git clone git://sourceware.org/git/binutils-gdb.git");
                            return true;
                        } catch (...) {
                            std::cerr << "There was an error in downloading the necessary dependencies to run PogVM. Please check if you have git installed or check your internet connection";
                            return false;
                        }
                    }
                );
                std::cout << "[" << ANSI::BLACK_BG << ANSI::ORANGE << "NOTICE" << ANSI::EXIT << "] " << ANSI::BOLD << "Downloading necessary dependencies..." << ANSI::EXIT << std::endl;
                return result.get();
            }
        }

        [[nodiscard]] static bool CheckVMX(void) {
            bool result;
            __asm__ __volatile__ (
                "mov $1, %%eax;"
                "cpuid;"
                "bt $5, %%ecx;"
                "jc VMX_Supported;"
                "jmp VMX_NotSupported;"

                "VMX_NotSupported: mov $0, %0;"
                "VMX_Supported: mov $1, %0;"
                    : "=r" ( result )
            );
            return result;
        }

    public:
        // Checks all the necessary processes and data needed to run the machine
        static void AuditCheck(void) {
            // The CPUClockSpeedCheck function takes a long time to process so I'm executing it first on a different thread
            std::future<bool> asyncClockSpeed = std::async(std::launch::async, AUDIT::CPUClockSpeedCheck);

            AuditLog(AUDIT::CPUCoreCheck(), "Checking CPU compatibility...");
            AuditLog(AUDIT::CPUThreadCheck(), "Checking threading compatibility...");
            AuditLog(AUDIT::ArchCheck(), "Checking for architecture compatibility...");
            AuditLog(AUDIT::objcopyCheck(), "Checking for binary utility dependency...");
            AuditLog(AUDIT::CheckVMX(), "Checking if VMX is supported...");
            AuditLog(asyncClockSpeed.get(), "Checking CPU clock speed compatibility...");

            AuditLog(MEMORY::Initialise(), "Allocating 2^16 bits of memory space...");
        }
};