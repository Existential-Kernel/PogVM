#include <iostream>
#include <fstream>
#include <filesystem>

#ifndef DEFS
#define DEFS

namespace fs = std::filesystem;

namespace INFO {
   	#define name "PogVM"
    #define major "1"
    #define minor "0"
    #define link "https://github.com/Existential-nonce/PogVM"
    std::string information = name " version " major "." minor \
    "\nWritten by Existential-nonce (" link \
    ")\nCopyright (C) 2022 Normie devs\nLicense: WTFPL";

}

namespace ANSI {
    const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    const char *RED      = "\x1B[38;2;255;0;0m";
    const char *GREEN    = "\x1B[38;2;0;255;0m";
    const char *GREY     = "\x1B[38;2;70;70;70m";
    const char *EXIT     = "\x1B[0m";
    std::ostream &BOLD(std::ostream& log) { return log << "\033[1m"; }
}

namespace OUTPUT {
	// Output the version of the program
    [[noreturn]] static void Version(void) {
		std::cout << INFO::information << std::endl;
		std::exit(0);
    }

    // Display the help menu
    [[noreturn]] static void HelpMenu(void) {
        std::cout << INFO::information << "\n" << ANSI::BOLD << "Usage: " << ANSI::EXIT << 
			"pogvm <file location> [flags]\n \
			Example: pogvm ./test --info\n";
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

namespace FUNCTIONS {
    static inline void ClearConsole() {
        #ifdef _WIN32 
            std::system("cls");
        #else 
            std::system("clear");
        #endif
    }

    static inline bool FileExists(const fs::path& path, fs::file_status status = fs::file_status{}) {
        bool result = (fs::status_known(status) ? fs::exists(status) : fs::exists(path));
        return result;
    }

    std::string IntToHex(const uint64_t &integer) {
        std::stringstream stream;
        stream << std::hex << integer;
        return stream.str();
    }
};

#endif