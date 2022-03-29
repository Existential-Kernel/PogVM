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

// Check if the program is using C++17 or newer
#if __cplusplus < 201703L
	#define CXX17 false
#else
	#define CXX17 true
#endif


namespace INFO {
	#define name "pogvm"
    #define major "1"
    #define minor "0"
    #define link "https://github.com/Existential-nonce/PogVM"
    std::string information = name " version " major "." minor " (" link ") ";
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

int main(int argc, char *argv[]) {
	if (!CXX17) {
		OUTPUT::Error("This program requires C++17 or newer to run.");
	}

	// TODO: make this into a switch statement with strings somehow, this looks awful lol
	if (argc == 1) {
		OUTPUT::HelpMenu();
	} else if (argc == 2) {
		if (!strcmp(argv[1], "--help")) { OUTPUT::HelpMenu(); }
		if (!strcmp(argv[1], "--v")) { OUTPUT::Version(); }
		if (!strcmp(argv[1], "--version")) { OUTPUT::Version(); }
		if (!strcmp(argv[1], "--audit")) { AUDIT::AuditCheck(); }
		if (FUNCTIONS::FileExists(argv[1])) {

			// check if file is an ELF file. Else, check if it's an assembly file
			if (HEXFETCH::CheckELF(FETCH::GetFileHexData(argv[1]))) {


				std::vector<unsigned char> hexvector = FETCH::FetchHex(argv[1]);

	
			} else if (ASSEMBLYFETCH::CheckASM(argv[1])) {


				std::vector<std::vector<std::string>> assemblyvector = FETCH::FetchAssembly(argv[1]);


			} else {
				OUTPUT::Error("Please provide an executable file or an assembly file to virtualise!");
			}
			
		} else {
			std::regex r(argv[1]);
			if (std::regex_search("--", r)) {
				OUTPUT::Error("Unrecognized flag option");
			} else {
				OUTPUT::Error("The file provided is not valid");
			}
		}

	} else if (argc == 3) {
		if (FUNCTIONS::FileExists(argv[1])) {
			if (!strcmp(argv[2], "--info")) {  }
			std::vector<std::vector<std::string>> program = FETCH::FetchAssembly(argv[1]);
		}
	}

    return 0;
}