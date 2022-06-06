#include <sys/vm86.h>

// I honestly don't know what I'm doing here, i'll maybe come back to this clusterfucked vm86 lib thingy idk

class VM {
    int vm86(unsigned long fn, struct vm86plus_struct *v86);
/*
	Check if CPU virtualisation support is enabled
	__asm__ {
		mov eax, 1
		cpuid
		bt ecx,5
		jc VMX_Supported
		jmp VMX_NotSupported   
	}
*/
};
