#include <iostream>
#include <string>
#include <algorithm>

class DECODE {
    private:

    public:
        void Decode(const std::string &opcode, std::string &operand1, std::string &operand2, bool interpreted) {
            if (interpreted) {
                transform(opcode.begin(), opcode.end(), opcode.begin(), ::tolower);
                uint16_t hex;
                if (opcode == "mov") { }

                if (opcode == "clc") { hex = 0xF8; }
                if (opcode == "cld") { hex = 0xFC; }
                if (opcode == "cli") { hex = 0xFA; }
            }

        }
} DECODE;