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


int main(int argc, char *argv[]) {
	#if __cplusplus < 201703L
		OUTPUT::Error("PogVM requires C++17 or newer to run", 0x0D);
	#endif

	switch(argc) {
		case 1:
			OUTPUT::HelpMenu();
			break;

		case 2:
			// TODO: make this into a switch statement somehow, this looks awful lol
			if (!strcmp(argv[1], "-h")) { OUTPUT::HelpMenu(); }
			if (!strcmp(argv[1], "--help")) { OUTPUT::HelpMenu(); }
			if (!strcmp(argv[1], "-v")) { OUTPUT::Version(); }
			if (!strcmp(argv[1], "--version")) { OUTPUT::Version(); }
			if (!strcmp(argv[1], "-a")) { AUDIT::AuditCheck(); }
			if (!strcmp(argv[1], "--audit")) { AUDIT::AuditCheck(); }
	
			if (FUNCTIONS::FileExists(argv[1])) {
				// check if file is an ELF file. Else, check if it's an assembly file
				if (ELF::CheckELF(FETCH::GetFileHexData(argv[1]))) {
					std::vector<unsigned char> hexvector = FETCH::FetchHex(argv[1]);
				} else if (ASSEMBLY::CheckASM(argv[1])) {
					std::vector<std::vector<std::string>> assemblyvector = FETCH::FetchAssembly(argv[1]);
				} else {
					OUTPUT::Error("Please provide an executable file or an assembly file to virtualise", 0x0C);
				}
			} else {
				if (argv[1][0] == '-') {
					OUTPUT::Error("Unrecognized flag option", 0x0B);
				} else {
					OUTPUT::Error("The file provided is not valid or does not exist", 0x0A);
				}
			}
			break;
		
		case 3:
			if (FUNCTIONS::FileExists(argv[2])) {
				std::vector<unsigned char> hexvector = FETCH::FetchHex(argv[2]);
				// TODO: make this into a switch statement too
				if (!strcmp(argv[1], "-hd")) { ELF::OutputELF(0b01, hexvector); }
				if (!strcmp(argv[1], "--header")) { ELF::OutputELF(0b01, hexvector); }
				if (!strcmp(argv[1], "-s")) { ELF::OutputELF(0b10, hexvector); }
				if (!strcmp(argv[1], "--section")) { ELF::OutputELF(0b10, hexvector); }
				if (!strcmp(argv[1], "-i")) { ELF::OutputELF(0b11, hexvector); }
				if (!strcmp(argv[1], "--info")) { ELF::OutputELF(0b11, hexvector); }
				//std::vector<std::vector<std::string>> program = FETCH::FetchAssembly(argv[2]);
			}
			break;
	}

    return 0;
}