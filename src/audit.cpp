#include <iostream>
#include <immintrin.h>
#include <future>

#include "cpu/memory.hpp"
#include "defs.hpp"
#include "ansi.hpp"

#include "audit.hpp"

// Log the initialisation process if it succeeded or failed
constexpr void AUDIT::AuditLog(const uint8_t &result, const std::string &message) {
    switch (result) {
        case 1: std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT << std::endl; break;
        /*
        case 2: std::cout << "┌─[" << ANSI::BLACK_BG << ANSI::ORANGE << "WARNING" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT << std::endl;
                std::cout << "└───>" << ANSI::BOLD << warnmessage << ANSI::EXIT << std::endl;
        */
        case 0: std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "]  " << ANSI::BOLD << message << ANSI::EXIT << std::endl; std::exit(1); break;
    }
}

[[nodiscard]] constexpr inline bool AUDIT::ArchCheck(void) {
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
[[nodiscard]] inline bool AUDIT::CPUThreadCheck(void) {
    try {
        return (std::thread::hardware_concurrency() * 2 >= 4);
    } catch (...) {
        return false;
    }
}

// Check if CPU cores are working as expected
[[nodiscard]] inline bool AUDIT::CPUCoreCheck(void) {
    try {
        return (std::thread::hardware_concurrency() != 0); 
    } catch (...) {
        return false;
    }
}

[[nodiscard]] inline bool AUDIT::CPUClockSpeedCheck(void) {
    try {
        return (UTIL::getClockSpeed() > 16000);
    } catch (...) {
        return false;
    }
}

// Checks all the necessary processes and data needed to run the machine
void AUDIT::AuditCheck(void) {

    // The CPUClockSpeedCheck function takes a long time to process so I'm executing it first on a different thread
    std::future<bool> asyncClockSpeed = std::async(std::launch::async, AUDIT::CPUClockSpeedCheck);
    
    AuditLog(AUDIT::CPUCoreCheck(), "Checking CPU compatibility...");
    AuditLog(AUDIT::CPUThreadCheck(), "Checking threading compatibility...");
    AuditLog(AUDIT::ArchCheck(), "Checking for architecture compatibility...");
    AuditLog(MEMORY::Initialise(), "Allocating 2^16 bits of memory space...");
    AuditLog(asyncClockSpeed.get(), "Checking CPU clock speed compatibility...");
}


AUDIT::AUDIT()
{
};

AUDIT::~AUDIT()
{
};