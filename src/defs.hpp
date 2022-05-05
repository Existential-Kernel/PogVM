#include <iostream>
#include <fstream>
#include <filesystem>

#ifndef DEFS_HPP
#define DEFS_HPP

namespace fs = std::filesystem;

namespace INFO {
    std::string program = "PogVM";
    char major = '1';
    char minor = '0';
    std::string link = "https://github.com/Existential-Kernel/PogVM";

    static const std::string version = program + " version " + major + "." + minor;
    const std::string information = program + " version " + major + "." + minor \
    + "\nMade by Existential-Kernel (" + link \
    + ")\nCopyright (C) 2022 Existential-Kernel\nLicense: WTFPL";
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

class OUTPUT {
    public:
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
    [[noreturn]] static void Error(std::string error, uint8_t code) {
        std::cerr 
            << ANSI::RED << ANSI::BOLD << "FATAL: " << ANSI::EXIT 
            << ANSI::BOLD << error << ANSI::EXIT << "\n"
            << ANSI::GREY << "(Error code " << 100 + (int)code << ")" << ANSI::EXIT << std::endl;
        std::exit(1);
    }
};

// For miscellaneous functions used throughout the program
namespace UTILITY {
    static inline void ClearConsole() {
        #ifdef _WIN32 
            std::system("cls");
        #else 
            std::system("clear");
        #endif
    }

    static inline bool FileExists(const fs::path& path, fs::file_status status = fs::file_status{}) {
        return (fs::status_known(status) ? fs::exists(status) : fs::exists(path));
    }

    // This is strictly used only during development for debugging purposes. (BP = breakpoint)
    [[noreturn]] static inline void BP(const std::string &message = "BREAKPOINT") {
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
/*
    static std::string IntToHex(const uint64_t &integer) {
        std::stringstream stream;
        stream << std::hex << integer;
        return stream.str();
    }
*/
};

#endif