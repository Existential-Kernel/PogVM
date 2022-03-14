#include <iostream>
#include <thread>
#include <fstream>

#define major 1
#define minor 0
#define link "https://github.com/Existential-nonce/PogCPU"

#ifndef DEFS
#define DEFS

namespace OUTPUT {
    void Version(bool fallthrough) {
        std::cout << "PogCPU version " << major << "." << minor << " (" << link << ") " << std::endl;
        if (!fallthrough) { std::exit(0); }
    }


    // Not sure if adding [[noreturn]] is helpful but I'll keep it anyway ¯\_(ツ)_/¯

    // Display the help menu
    [[noreturn]] inline void HelpMenu(void) {
        Version(true);
        std::cout << "Usage: " << ANSI::BOLD << "lol" << ANSI::NOBOLD << std::endl;
        std::exit(0);
    }

    // Log errors
    [[noreturn]] inline void Error(std::string error) {
        std::cerr << ANSI::RED << ANSI::BOLD << "FATAL: " << ANSI::NOBOLD << ANSI::EXIT << error << std::endl;
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
}



namespace CHECK {
    
    namespace fs = std::filesystem;

    // Checks if the file exists
    bool FileExists(const fs::path& path, fs::file_status status = fs::file_status{}) {
        if (fs::status_known(status) ? fs::exists(status) : fs::exists(path)) {
            return true;
        } else {
            return false;
        }
    }
}

#endif