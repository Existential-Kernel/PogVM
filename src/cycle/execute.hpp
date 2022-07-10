#pragma once

class EXECUTE {
    public:
        EXECUTE();
        ~EXECUTE();

    public:
        static void MassExecute(class REGISTER *Reg, class STACK *Stack, const std::vector<std::vector<uint8_t>> &v);
        static void Execute(class REGISTER *Reg, class STACK *Stack, const std::vector<uint8_t> &v);
};