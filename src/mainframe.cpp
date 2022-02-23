#include <iostream>
#include <cstdlib>
#include <stdint.h>

//#include "CPU/registers.hpp"
//#include "CPU/memory.hpp"
#include "audit.hpp"

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

int main(void) {
	AUDIT.AuditCheck();
    return 0;
}