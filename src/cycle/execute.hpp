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
        [[gnu::hot]] static void MassExecute(const std::vector<std::vector<uint8_t>> &v);
        [[gnu::hot]] static void Execute(const std::vector<uint8_t> &v);
};