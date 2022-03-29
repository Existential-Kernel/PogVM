#include <iostream>
#include <fstream>
#include <filesystem>

#ifndef DEFS
#define DEFS

namespace fs = std::filesystem;

namespace ANSI {
    static const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    static const char *RED = "\x1B[38;2;255;0;0m";
    static const char *GREEN = "\x1B[38;2;0;255;0m";

    static std::ostream &BOLD(std::ostream& log) { return log << "\e[1m"; }

    static const char *EXIT = "\x1B[0m";
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

    // Get the amount of RAM depending on OS
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

};

#endif