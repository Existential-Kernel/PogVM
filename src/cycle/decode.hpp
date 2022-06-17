#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "../defs.hpp"

#pragma once

// https://stackoverflow.com/questions/30443501/why-do-these-two-instructions-have-the-same-opcode

class DECODE {
    public:
        DECODE();
        ~DECODE();

    private:
        #define sec 0x55  // sections
        #define sub 0x11  // subelements

        [[gnu::always_inline]] static inline void SinglePush(std::vector<uint8_t> &v, const uint8_t &s, std::vector<std::vector<uint8_t>> &instructions) noexcept;
        [[gnu::always_inline]] static inline void Push(std::vector<uint8_t> &v, const uint8_t &s, uint8_t &arg, const uint8_t &count) noexcept;
        static void CheckBits(const uint8_t &acceptablebits, const uint8_t &kernelbits, const uint8_t &hex) noexcept;
        static void CheckProc(const uint8_t &acceptableproc, const uint8_t &kernelproc) noexcept;

    public:
        static void Decode(const std::vector<uint8_t> &hexvector, std::vector<std::vector<uint8_t>> &resultvector, const uint8_t &bits, const uint8_t &processor);

};