#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

#include "../defs.hpp"
#include "../instructions/8086-8088.hpp"
#include "../instructions/testing.hpp"

#pragma once

class EXECUTE {
    public:
        EXECUTE();
        ~EXECUTE();

    private:
        #define sec 0x55  // sections
        #define sub 0x11  // subelements

    public:
        static void MassExecute(class REGISTER *Reg, const std::vector<std::vector<uint8_t>> &v);
        static void Execute(class REGISTER *Reg, const std::vector<uint8_t> &v);
};