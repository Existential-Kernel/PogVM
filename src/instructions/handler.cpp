#include <iostream>
#include <functional>
#include "../cpu/flags.hpp"
#include "../cpu/registers.hpp"

template <typename Op>
void RegOperation(Op&& op) {
    op(a, b);
}
