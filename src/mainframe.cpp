#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <cstring>

//#include "CPU/registers.hpp"
//#include "CPU/memory.hpp"
#include "audit.hpp"
#include "cycle/fetch.cpp"

#define major 1
#define minor 0
#define version major.minor

namespace CPU
{
	using SByte = char;
	using Byte = unsigned char;
	using Word = unsigned short;

	using u32 = unsigned int;
	using s32 = signed int;

	struct Mem;
	struct CPU;
	struct StatusFlags;
}

int main(int argc, char *argv[]) {
	if (argc >= 2) {
		// TODO: make the arguments into a switch statement

		if (!strcmp(argv[1], "--audit")) { AUDIT.AuditCheck(); }
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