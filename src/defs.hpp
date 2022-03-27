#include <iostream>
#include <fstream>
#include <filesystem>

#ifndef DEFS
#define DEFS

namespace fs = std::filesystem;

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