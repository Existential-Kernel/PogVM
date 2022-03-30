#include <iostream>
#include <fstream>
#include <filesystem>

#ifndef DEFS
#define DEFS

namespace fs = std::filesystem;

namespace INFO {
	#define name "pogvm"
    #define major "1"
    #define minor "0"
    #define link "https://github.com/Existential-nonce/PogVM"
    std::string information = name " version " major "." minor " (" link ")";
}

namespace ANSI {
    static const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    static const char *RED = "\x1B[38;2;255;0;0m";
    static const char *GREEN = "\x1B[38;2;0;255;0m";
    static const char *EXIT = "\x1B[0m";
    static std::ostream &BOLD(std::ostream& log) { return log << "\e[1m"; }
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
    [[noreturn]] static void Error(std::string error) {
        std::cerr << ANSI::RED << ANSI::BOLD << "FATAL: " << ANSI::EXIT << ANSI::BOLD << error << ANSI::EXIT << std::endl;
        std::exit(1);
    }
};

namespace FUNCTIONS {
    inline void ClearConsole() {
        #ifdef _WIN32 
            std::system("cls");
        #else 
            std::system("clear");
        #endif
    }

    inline bool FileExists(const fs::path& path, fs::file_status status = fs::file_status{}) {
        bool result = (fs::status_known(status) ? fs::exists(status) : fs::exists(path));
        return result;
    }

    // Get the amount of RAM depending on OS
    /*
    static int GetRAMSize() {
        #ifdef _WIN32
            #include <windows.h>
            MEMORYSTATUSEX statex;
            statex.dwLength = sizeof (statex);
            GlobalMemoryStatusEx (&statex);
            return statex.ullTotalPhys / 1024;
        #else
            #include <sys/sysinfo.h>
            struct sysinfo info;
            sysinfo(&info);
            return info.totalram / 1024;
        #endif
    }
    */

};

#endif