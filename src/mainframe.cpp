#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <cstring>
#include <vector>
#include <regex>

#include "audit.hpp"
#include "cycle/fetch.cpp"
#include "defs.hpp"

// Check if it's using C++17 or newer
#if __cplusplus < 201703L
	#define CXX17 false
#else
	#define CXX17 true
#endif


int main(int argc, char *argv[]) {
	if (!CXX17) {
		OUTPUT::Error("PogVM requires C++17 or newer to run");
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
			if (ELFFETCH::CheckELF(FETCH::GetFileHexData(argv[1]))) {


				std::vector<unsigned char> hexvector = FETCH::FetchHex(argv[1]);


			} else if (ASSEMBLYFETCH::CheckASM(argv[1])) {


				std::vector<std::vector<std::string>> assemblyvector = FETCH::FetchAssembly(argv[1]);


			} else {
				OUTPUT::Error("Please provide an executable file or an assembly file to virtualise");
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
			if (!strcmp(argv[2], "--info")) {
				std::vector<unsigned char> hexvector = FETCH::FetchHex(argv[1]);
				ELFFETCH::OutputELF(); 
			}
			std::vector<std::vector<std::string>> program = FETCH::FetchAssembly(argv[1]);
		}
	}

    return 0;
}