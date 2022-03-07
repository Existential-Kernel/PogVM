#include <iostream>

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
    [[noreturn]] void HelpMenu(void) {
        Version(true);
        std::cout << "Usage: " << ANSI::BOLD << "lol" << ANSI::NOBOLD << std::endl;
        std::exit(0);
    }
}

#endif