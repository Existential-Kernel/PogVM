#include <sys/vm86.h>

class VM {
    int vm86(unsigned long fn, struct vm86plus_struct *v86);
};