#include <iostream>
#include <cstdint>
#include <tuple>
#include <string>
#include <sstream>
#include <cstring>

#include "cpu/registers.hpp"
#include "cpu/memory.hpp"
//#include "tests/assembly.hpp"
#include "defs.hpp"


// TODO: Fix the ResetAll() function
/*
    // Reset all registers to 0
    bool ResetAll(void) {
        try {
            memset(&R64, 0, sizeof R64);
            memset(&SREG, 0, sizeof SREG);
            memset(&PREG, 0, sizeof PREG);

            return true;
        } catch (...) {
            return false;
        }
    }
*/

