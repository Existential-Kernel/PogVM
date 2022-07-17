#include <iostream>
#include <fstream>
#include <filesystem>

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#pragma once

#if __cpp_attributes 
    #if __has_cpp_attribute(gnu::hot)
        #define GNU_HOT [[gnu::hot]]
    #else
        #define GNU_HOT
    #endif

    #if __has_cpp_attribute(gnu::always_inline)
        #define GNU_INLINE [[gnu::always_inline]]
    #else
        #define GNU_INLINE
    #endif
#else
	#define GNU_HOT
    #define GNU_INLINE
#endif

namespace INFO {
    std::string program = "PogVM";
    char major       = 1;
    char minor       = 0;
    std::string link    = "https://github.com/Existential-Kernel/PogVM";

    const std::string version = program + " version " + major + "." + minor;
    const std::string information = version \
    + "\nMade by Existential-Kernel (" + link \
    + ")\nCopyright 2022 Existential-Kernel\nLicense: WTFPL";
};

namespace ANSI {
    const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    const char *RED_BG   = "\x1B[48;2;255;0;0m";

    const char *RED      = "\x1B[38;2;255;0;0m";
    const char *ORANGE   = "\x1B[38;2;255;180;5m";
    const char *GREEN    = "\x1B[38;2;0;255;0m";
    const char *GREY     = "\x1B[38;2;70;70;70m";
    const char *EXIT     = "\x1B[0m";
    std::ostream &BOLD(std::ostream& log) { return log << "\033[1m"; }
}

namespace OUTPUT {
	// Output the version of the program
    [[noreturn]] static void Version(void) {
		std::cout << INFO::version;
		std::exit(0);
    }

    // Display the help menu
    [[noreturn]] static void HelpMenu(void) {
        std::cout << INFO::information;
        std::cout << "\n" << ANSI::BOLD << "Usage: " << ANSI::EXIT << 
"pogvm [flags] [file location]\n \
  Example: pogvm --info ./test\n";
        std::exit(0);
    }

    // Log errors
    [[noreturn]] static void Error(const std::string &error, const uint8_t &code, const std::string &arg = "") {
        std::cerr 
            << ANSI::RED << ANSI::BOLD << "FATAL: " << ANSI::EXIT 
            << ANSI::BOLD << arg << error << ANSI::EXIT << "\n"
            << ANSI::GREY << "(Error code " << 100 + code << ")" << ANSI::EXIT << std::endl;
        std::exit(1);
    }

    // Abort log
    [[noreturn]] static void Abort(const std::string &error) {
        std::cerr 
            << ANSI::RED << ANSI::BOLD << "ABORTED: " << ANSI::EXIT 
            << ANSI::BOLD << error << ANSI::EXIT << "\n";
        std::exit(1);
    }
};

namespace UTIL {
    [[nodiscard]] static inline bool FileExists(const std::filesystem::path &path, const std::filesystem::file_status &status = std::filesystem::file_status{}) {
        return (std::filesystem::status_known(status) ? std::filesystem::exists(status) : std::filesystem::exists(path));
    }

    [[nodiscard]] static inline uint64_t getCycles(void) {
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

    [[nodiscard]] static inline uint32_t getMillisecondCounter(void) {
        struct timespec t;
        clock_gettime (CLOCK_MONOTONIC, &t);

        return static_cast<uint32_t>(t.tv_sec * 1000 + t.tv_nsec / 1000000);
    }

    // clock speed in kilohertz
    [[nodiscard]] volatile static inline uint64_t getClockSpeed(void) {
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
}

// For debugging or development purposes only
namespace DEV {
    [[maybe_unused]] static inline void ClearConsole(void) {
        #ifdef _WIN32 
            std::system("cls");
        #else 
            std::system("clear");
        #endif
    }

    // BP = breakpoint
    [[maybe_unused, noreturn]] static void BP(const std::string &message = "BREAKPOINT") {
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

    [[maybe_unused]] static std::string IntToHex(const uint64_t &integer) {
        std::stringstream stream;
        stream << std::hex << integer;
        return stream.str();
    }

};