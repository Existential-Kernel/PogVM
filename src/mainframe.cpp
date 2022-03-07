#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <cstring>
#include <thread>

//#include "CPU/registers.hpp"
//#include "CPU/memory.hpp"
#include "audit.hpp"
#include "cycle/fetch.cpp"
#include "defs.hpp"


int main(int argc, char *argv[]) {
	// TODO: make argv into a switch statement

	if (argc == 1) {
		OUTPUT::HelpMenu();
	}

	if (argc == 2) {
		if (!strcmp(argv[1], "--help")) { OUTPUT::HelpMenu(); }
		if (!strcmp(argv[1], "--v")) { OUTPUT::Version(false); }
		if (!strcmp(argv[1], "--version")) { OUTPUT::Version(false); }
	}

	if (argc > 2) {
		if (!strcmp(argv[1], "--audit")) { AUDIT::AuditCheck(); }
		if (!strcmp(argv[1], "--tobeadded")) { }
	}

	FETCH.FetchLine();
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