#include <iostream>
#include <fstream>
#include <filesystem>

#pragma once

namespace INFO {
    std::string program = "PogVM";
    char major = '1';
    char minor = '0';
    std::string link = "https://github.com/Existential-Kernel/PogVM";

    const std::string version = program + " version " + major + "." + minor;
    const std::string information = program + " version " + major + "." + minor \
    + "\nMade by Existential-Kernel (" + link \
    + ")\nCopyright 2022 Existential-Kernel\nLicense: WTFPL";
};

namespace ANSI {
    const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    const char *RED_BG   = "\x1B[48;2;255;0;0m";

    const char *RED      = "\x1B[38;2;255;0;0m";
    const char *GREEN    = "\x1B[38;2;0;255;0m";
    const char *GREY     = "\x1B[38;2;70;70;70m";
    const char *EXIT     = "\x1B[0m";
    std::ostream &BOLD(std::ostream& log) { return log << "\033[1m"; }
}

namespace OUTPUT {
	// Output the version of the program
    [[noreturn]] static void Version(void) {
		std::cout << INFO::version << std::endl;
		std::exit(0);
    }

    // Display the help menu
    [[noreturn]] static void HelpMenu(void) {
        std::cout << INFO::information << "\n" << ANSI::BOLD << "Usage: " << ANSI::EXIT << 
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

// For miscellaneous functions used throughout the program
namespace UTILITY {
    static inline void ClearConsole(void) {
        #ifdef _WIN32 
            std::system("cls");
        #else 
            std::system("clear");
        #endif
    }

    [[gnu::always_inline]] [[nodiscard]] static inline bool FileExists(const std::filesystem::path &path, const std::filesystem::file_status &status = std::filesystem::file_status{}) {
        return (std::filesystem::status_known(status) ? std::filesystem::exists(status) : std::filesystem::exists(path));
    }
/*
    // This is strictly used only during development for debugging purposes. (BP = breakpoint)
    [[noreturn]] static void BP(const std::string &message = "BREAKPOINT") {
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
*/

/*
    static std::string IntToHex(const uint64_t &integer) {
        std::stringstream stream;
        stream << std::hex << integer;
        return stream.str();
    }
*/
};