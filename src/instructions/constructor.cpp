#include <iostream>

// https://stackoverflow.com/questions/19848437/constructors-with-functions-as-arguments-in-c

class Construct {
    public:
        double size;
        

    template<typename F>
    explicit Construct(std::string opcode, unsigned char hex, F&& f) : size(f()) {

    };
};