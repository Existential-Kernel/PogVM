#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <cstring>
#include <vector>
#include <regex>

#include "audit.hpp"
#include "cycle/fetch.cpp"
#include "core.cpp"
#include "defs.hpp"

int main(int argc, char *argv[]) {
	#if __cplusplus < 201703L
		OUTPUT::Error("PogVM requires C++17 or newer to run", 0x0D);
		exit(1);
	#endif

	switch(argc) {
		case 1:
			OUTPUT::HelpMenu();
			break;

		case 2:
			// TODO: make this into a switch statement somehow, this looks awful
			if (!strcmp(argv[1], "-h")) { OUTPUT::HelpMenu(); }
			if (!strcmp(argv[1], "--help")) { OUTPUT::HelpMenu(); }
			if (!strcmp(argv[1], "-v")) { OUTPUT::Version(); }
			if (!strcmp(argv[1], "--version")) { OUTPUT::Version(); }
			if (!strcmp(argv[1], "-a")) { AUDIT::AuditCheck(); }
			if (!strcmp(argv[1], "--audit")) { AUDIT::AuditCheck(); }

			if (UTILITY::FileExists(argv[1])) {
				KERNEL::Kernel(argv[1], true); // REVISION NEEDED: change default bool value if i find out which mode is more stable
			}
			break;

		case 3:
			if (UTILITY::FileExists(argv[2])) {
				std::vector<u_char> hexvector = FETCH::FetchHex(argv[2]);

				// TODO: make this into a switch statement too
				if (!strcmp(argv[1], "-hd")) { ELF::OutputELF(0b00, hexvector); }
				if (!strcmp(argv[1], "-p")) { ELF::OutputELF(0b01, hexvector); }
				if (!strcmp(argv[1], "-s")) { ELF::OutputELF(0b10, hexvector); }
				if (!strcmp(argv[1], "-i")) { ELF::OutputELF(0b11, hexvector); }
				if (!strcmp(argv[1], "--header")) { ELF::OutputELF(0b00, hexvector); }
				if (!strcmp(argv[1], "--program")) { ELF::OutputELF(0b01, hexvector); }
				if (!strcmp(argv[1], "--sections")) { ELF::OutputELF(0b10, hexvector); }
				if (!strcmp(argv[1], "--info")) { ELF::OutputELF(0b11, hexvector); }

				if (!strcmp(argv[1], "--interpreted")) { KERNEL::Kernel(argv[2], false); }
				if (!strcmp(argv[1], "--compiled")) { KERNEL::Kernel(argv[2], true); }
			} else {
				if (argv[1][0] == '-') {
					OUTPUT::Error("Unrecognized flag option", 0x0B);
				} else {
					OUTPUT::Error("The file provided is not valid or does not exist", 0x0A);
				}
			}
			break;
	}

    return 0;
}