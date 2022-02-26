#include <iostream>
#include <cstdlib>
#include <stdint.h>

//#include "CPU/registers.hpp"
//#include "CPU/memory.hpp"
#include "audit.hpp"
#include "cycle/fetch.cpp"

#define major 1
#define minor 0
#define version major.minor

namespace POGCPU
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
	if (argc == 1 && argv[0] == "--audit") {
		AUDIT.AuditCheck();	
	}

	FETCH.FetchLine();
    return 0;
}