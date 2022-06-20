#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <cstring>
#include <vector>

#include <thread>

#include "audit.hpp"
#include "cycle/fetch.cpp"
#include "vcore.cpp"
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
			// TODO: make this into a switch statement somehow, this looks awful
			if (!strcmp(argv[1], "-h")) { OUTPUT::HelpMenu(); }
			if (!strcmp(argv[1], "--help")) { OUTPUT::HelpMenu(); }
			if (!strcmp(argv[1], "-v")) { OUTPUT::Version(); }
			if (!strcmp(argv[1], "--version")) { OUTPUT::Version(); }
			if (!strcmp(argv[1], "-a")) { AUDIT::AuditCheck(); }
			if (!strcmp(argv[1], "--audit")) { AUDIT::AuditCheck(); std::exit(0); }

			if (UTILITY::FileExists(argv[1])) {
				KERNEL::Kernel(argv[1], true, 32, 1); // REVISION NEEDED: change default bool value if i find out which mode is more stable
				break;
			}

			if (argv[1][0] == '-') {
				OUTPUT::Error("Unrecognized flag option", 0x0B); 
			} else { 
				OUTPUT::Error("The file provided is not valid or does not exist", 0x0A);
			}
			break;

		case 3:
			if (UTILITY::FileExists(argv[2])) {
/*
				{
					std::unique_ptr<ELF>ELF_PTR = std::make_unique<ELF>();
					std::vector<uint8_t>hexvector = ELF_PTR->FetchHex(argv[2]);

					// TODO: make this into a switch statement too
					if (!strcmp(argv[1], "-hd") || !strcmp(argv[1], "--header")) { ELF_PTR->OutputELF(0b00, hexvector); }
					if (!strcmp(argv[1], "-p") || !strcmp(argv[1], "--program")) { ELF_PTR->OutputELF(0b01, hexvector); }
					if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--sections")) { ELF_PTR->OutputELF(0b10, hexvector); }
					if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--info")) { ELF_PTR->OutputELF(0b11, hexvector); }
				}
*/

				{
					std::vector<uint8_t>hexvector = ELF::MassFetchHex(argv[2]);

					// TODO: make this into a switch statement too
					if (!strcmp(argv[1], "-hd") || !strcmp(argv[1], "--header")) { ELF::OutputELF(0b00, hexvector); }
					if (!strcmp(argv[1], "-p") || !strcmp(argv[1], "--program")) { ELF::OutputELF(0b01, hexvector); }
					if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--sections")) { ELF::OutputELF(0b10, hexvector); }
					if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--info")) { ELF::OutputELF(0b11, hexvector); }
				}
				bool mode = true;
				if (!strcmp(argv[1], "--interpreted")) { mode = false; }
				else if (!strcmp(argv[1], "--compiled")) { mode = true; }

				uint8_t bitclass{};
				if (!strcmp(argv[1], "--64-bit")) { bitclass = 64; }
				else if (!strcmp(argv[1], "--32-bit")) { bitclass = 32; }
				else { bitclass = 32; }   

				uint8_t processorID{};
				if (!strcmp(argv[1], "--8086") || !strcmp(argv[1], "--8088")) { processorID = 1; }
				else if (!strcmp(argv[1], "--80186") || !strcmp(argv[1], "--80188")) { processorID = 2; }
				else if (!strcmp(argv[1], "--nec-v")) { processorID = 3; }
				else if (!strcmp(argv[1], "--80286")) { processorID = 4; }
				else if (!strcmp(argv[1], "--80386")) { processorID = 5; }
				else if (!strcmp(argv[1], "--80486")) { processorID = 6; }
				else if (!strcmp(argv[1], "--pentium")) { processorID = 7; }
				else if (!strcmp(argv[1], "--pentium-mmx")) { processorID = 8; }
				else if (!strcmp(argv[1], "--amd-k6")) { processorID = 9; }
				else if (!strcmp(argv[1], "--pentium-pro")) { processorID = 10; }
				else if (!strcmp(argv[1], "--pentium-II")) { processorID = 11; }
				else if (!strcmp(argv[1], "--intel-itanium")) { processorID = 12; }
				else if (!strcmp(argv[1], "--cyrix-geode")) { processorID = 13; }
				else { processorID = 13; }

				KERNEL::Kernel(argv[2], mode, bitclass, processorID);

				




			} else {
				if (argv[1][0] == '-') {
					OUTPUT::Error("Unrecognized flag option", 0x0B);
				} else {
					OUTPUT::Error("The file provided is not valid or does not exist", 0x0A);
				}
			}
			break;

		case 4:
			break;
	}
    return 0;
}