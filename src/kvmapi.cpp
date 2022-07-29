#include <sys/vm86.h>

// I honestly don't know what I'm doing here, i'll maybe come back to this clusterfucked vm86 lib thingy idk

class VM {
    int vm86(unsigned long fn, struct vm86plus_struct *v86);
};





//https://zserge.com/posts/kvm/
