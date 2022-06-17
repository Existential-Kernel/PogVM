#include <stack>
#include <variant>
#include <stdint.h>

#pragma once
// https://www.geeksforgeeks.org/stack-in-cpp-stl/

class STACK {
    public:
        std::stack<std::variant<__uint8_t, __uint16_t, __uint32_t, __uint64_t /*, __uint128_t*/, size_t>> stack; 
};