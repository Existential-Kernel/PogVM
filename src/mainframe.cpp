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



int main(int argc, char *argv[]) {
	// TODO: make argv into a switch statement
/*
	if (argc == 1) {
		OUTPUT::HelpMenu();
	}

	else */ if (argc == 2) {
		if (!strcmp(argv[1], "--help")) { OUTPUT::HelpMenu(); }
		if (!strcmp(argv[1], "--v")) { OUTPUT::Version(false); }
		if (!strcmp(argv[1], "--version")) { OUTPUT::Version(false); }
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