#include <iostream>
#include <fstream>
#include <filesystem>
#include <future>

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "defs.hpp"
#include "ansi.hpp"



// Output the version of the program
[[noreturn]] static void OUTPUT::Version(void) {
    std::cout << INFO::version;
    std::exit(0);
}

// Display the help menu
[[noreturn]] static void OUTPUT::HelpMenu(void) {
    std::cout << INFO::information;
    std::cout << "\n" << ANSI::BOLD << "Usage: " << ANSI::EXIT << 
"pogvm [flags] [file location]\n \
  Example: pogvm --info ./test\n";
    std::exit(0);
}

[[noreturn]] static void OUTPUT::Abort(const std::string &error) {
    std::cerr 
        << ANSI::RED << ANSI::BOLD << "ABORTED: " << ANSI::EXIT 
        << ANSI::BOLD << error << ANSI::EXIT << "\n";
    std::exit(1);
}

// Log errors
[[noreturn]] static void OUTPUT::Error(const std::string &error, const uint8_t &code, const std::string &arg) {
    std::cerr 
        << ANSI::RED << ANSI::BOLD << "FATAL: " << ANSI::EXIT 
        << ANSI::BOLD << arg << error << ANSI::EXIT << "\n"
        << ANSI::GREY << "(Error code " << 100 + code << ")" << ANSI::EXIT << std::endl;
    std::exit(1);
}




[[nodiscard]] bool UTIL::FileExists(const std::filesystem::path &path, const std::filesystem::file_status &status) {
    return (std::filesystem::status_known(status) ? std::filesystem::exists(status) : std::filesystem::exists(path));
}

[[nodiscard]] static bool UTIL::CheckExtension(const std::string &file, const std::string &extension) {
    std::string fileExtension = file.substr(file.find_last_of(".") + 1);
    return (fileExtension == extension);
}

void UTIL::PogVM_Preprocess(void) {
    if (FileExists("/usr/bin/objcopy")) {    // i gotta write it this way because C++ precompiled conditions are syntax nazis sometimes
        return;
    } else {
        std::future<void> result = std::async(std::launch::async, [](){
                try {
                    std::system("git clone git://sourceware.org/git/binutils-gdb.git");
                } catch (...) {
                    OUTPUT::Error("There was an error in downloading the necessary dependencies to run PogVM. Please check if you have git installed or check your internet connection", 0x13);
                }
            }
        );
        std::cout << ANSI::BLACK_BG << ANSI::ORANGE << "NOTICE" << ANSI::EXIT << "] " << ANSI::BOLD << "Downloading necessary dependencies..." << ANSI::EXIT << std::endl;
        result.get();
    }
}

[[nodiscard]] static inline uint64_t UTIL::getCycles(void) {
    #if defined(__ARM_ARCH_7A__)
        uint32_t r;
        __asm__ __volatile__("mrc p15, 0, %0, c9, c13, 0\t\n" : "=r" (r)); /* Read PMCCNTR       */
        return (static_cast<uint64_t>(r)) << 6;                                 /* 1 tick = 64 clocks */
    #elif defined(__x86_64__)
        unsigned a, d;
        __asm__ __volatile__("rdtsc" : "=a" (a), "=d" (d));
        return (static_cast<uint64_t>(a)) | ((static_cast<uint64_t>(d)) << 32);
    #elif defined(__i386__)
        uint64_t ret;
        __asm__ __volatile__("rdtsc": "=A" (ret));
        return ret;
    #else
        OUTPUT::Error("Unknown architecture detected", 0x12)
    #endif
}

[[nodiscard]] static inline uint32_t UTIL::getMillisecondCounter(void) {
    struct timespec t;
    clock_gettime (CLOCK_MONOTONIC, &t);

    return static_cast<uint32_t>(t.tv_sec * 1000 + t.tv_nsec / 1000000);
}

// clock speed in kilohertz
[[nodiscard]] volatile static inline uint64_t UTIL::getClockSpeed(void) {
    const uint64_t cycles = getCycles();
    const uint32_t millis = getMillisecondCounter();
    int lastResult = 0;

    for (;;) {
        volatile int n = 1000000;
        while (--n > 0) {}

        const uint32_t millisElapsed = getMillisecondCounter() - millis;
        const uint64_t cyclesNow = getCycles();

        if (millisElapsed > 80) {
            const int newResult = static_cast<int>((cyclesNow - cycles) / millisElapsed);

            if (millisElapsed > 500 || (lastResult == newResult && newResult > 100)) {
                return newResult;
            }

            lastResult = newResult;
        }
    }
}


























[[maybe_unused]] static inline void DEV::ClearConsole(void) {
    #ifdef _WIN32 
        std::system("cls");
    #else 
        std::system("clear");
    #endif
}

// BP = breakpoint
[[maybe_unused, noreturn]] static void DEV::BP(const std::string &message = "BREAKPOINT") {
    std::cout 
        << "\n" 
        << ANSI::BLACK_BG 
        << "===============" 
        << ANSI::RED_BG 
        << "[ "  << message << " ]" 
        <<  ANSI::BLACK_BG 
        << "===============" 
        << ANSI::EXIT 
        << "\n" << std::endl;
    std::exit(0);
}

[[maybe_unused]] static std::string DEV::IntToHex(const uint64_t &integer) {
    std::stringstream stream;
    stream << std::hex << integer;
    return stream.str();
}
