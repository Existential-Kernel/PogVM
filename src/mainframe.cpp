#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <cstring>
#include <thread>
#include <regex>

#include "audit.hpp"
#include "cycle/fetch.cpp"
#include "defs.hpp"

namespace INFO {
    #define major "1"
    #define minor "0"
    #define link "https://github.com/Existential-nonce/PogVM"
    std::string version = "program version " major "." minor " (" link ") ";
}

namespace OUTPUT {
	// Output the version of the program
    [[noreturn]] static void Version(void) {
		std::cout << INFO::version << std::endl;
		std::exit(0);
    }

    // Display the help menu
    [[noreturn]] static void HelpMenu(void) {
        std::cout << INFO::version << "\n" << ANSI::BOLD << "Usage: " << ANSI::EXIT << 
			"pogvm <file location> [flags]\n\
			Example: pogvm ./test --info"
		<< std::endl;
        std::exit(0);
    }

    // Log errors
    [[noreturn]] static void Error(std::string error) {
        std::cerr << ANSI::RED << ANSI::BOLD << "FATAL: " << ANSI::EXIT << ANSI::BOLD << error << ANSI::EXIT << std::endl;
        std::exit(1);
    }
};

int main(int argc, char *argv[]) {
	// TODO: make this into a switch statement somehow

	if (argc == 1) {
		OUTPUT::HelpMenu();
	} else if (argc == 2) {
		if (!strcmp(argv[1], "--help")) { OUTPUT::HelpMenu(); }
		if (!strcmp(argv[1], "--v")) { OUTPUT::Version(); }
		if (!strcmp(argv[1], "--version")) { OUTPUT::Version(); }
		if (!strcmp(argv[1], "--audit")) { AUDIT::AuditCheck(); }
		if (FUNCTIONS::FileExists(argv[1])) {
			std::vector<unsigned char> hexvector = FETCH::FetchHex(argv[1], false);


			// check if file is an ELF file. Else, check if it's an assembly file
			if (CHECKS::CheckELF(hexvector)) {
				// do stuff
			} else if (CHECKS::CheckASM(argv[1])) {
				// do stuff
			}
			


			//std::vector<std::vector<std::string>> program = FETCH::FetchCode(argv[1], true);
			//std::vector<unsigned char> v = FETCH::GetFileHexData(argv[1], v, false)
			//FETCH::GetFileHexData(argv[1], v, true);
		} else {
			OUTPUT::Error("The file provided is not valid.");
		}

	} else if (argc == 3) {
		if (FUNCTIONS::FileExists(argv[1])) {
			if (!strcmp(argv[2], "--info")) {  }
			std::vector<std::vector<std::string>> program = FETCH::FetchCode(argv[1], true);
		}
	}

    return 0;
}