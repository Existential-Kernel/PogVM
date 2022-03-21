#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <cstring>
#include <thread>
#include <regex>

//#include "cpu/registers.hpp"
//#include "cpu/memory.hpp"
#include "audit.hpp"
#include "cycle/fetch.cpp"
#include "defs.hpp"

namespace OUTPUT {
    // Not sure if adding [[noreturn]] is helpful but I'll keep it anyway ¯\_(ツ)_/¯

	// Output the version of the program
    [[noreturn]] static void Version(void) {
		std::cout << INFO::version << std::endl;
		std::exit(0);
    }

    // Display the help menu
    [[noreturn]] static void HelpMenu(void) {
        
        std::cout << INFO::version << std::endl << ANSI::BOLD << "Usage: " << ANSI::EXIT << 
			"pogcpu <file location> [flags]\n\
			Example: pogcpu ./test --verbose"
		<< std::endl;
        std::exit(0);
    }

    // Log errors
    [[noreturn]] static void Error(std::string error) {
        std::cerr << ANSI::RED << ANSI::BOLD << "FATAL: " << ANSI::EXIT << error << std::endl;
        std::exit(1);
    }
};

int main(int argc, char *argv[]) {
	// TODO: make argv into a switch statement
/*
	if (argc == 1) {
		OUTPUT::HelpMenu();
	}

	else */ if (argc == 2) {
		if (!strcmp(argv[1], "--help")) { OUTPUT::HelpMenu(); }
		if (!strcmp(argv[1], "--v")) { OUTPUT::Version(); }
		if (!strcmp(argv[1], "--version")) { OUTPUT::Version(); }
		if (!strcmp(argv[1], "--audit")) { AUDIT::AuditCheck(); }
		if (FUNCTIONS::FileExists(argv[1])) {
			std::vector<std::vector<std::string>> program = FETCH::FetchCode(argv[1], true);
		}

	} else if (argc == 3) {
		if (!strcmp(argv[1], "--")) { }
	}

    return 0;
}

// TODO: Fix this shit
/*
static bool Compare(const char *argv, const char *arg) {
	if (!strcmp(&argv[1], arg)) {
		return true;
	} else {
		return false;
	}
}
*/