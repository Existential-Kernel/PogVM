#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>

// Macros
namespace fs = std::filesystem;

#ifndef DEFS
#define DEFS

namespace INFO {
    #define major 1
    #define minor 0
    #define link "https://github.com/Existential-nonce/PogCPU"
    std::string version = std::string("program version ") + std::to_string(major) + '.' + std::to_string(minor) + " (" + link + ") ";
}

namespace FUNCTIONS {
    inline void ClearConsole() {
        #ifdef _WIN32 
            std::system("cls");
        #else 
            std::system("clear");
        #endif
    }

    inline bool FileExists(const fs::path& path, fs::file_status status = fs::file_status{}) {
        if (fs::status_known(status) ? fs::exists(status) : fs::exists(path)) {
            return true;
        } else { 
            return false;
        }
    }

};

#endif