#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

#define prefix ";"

class FETCH {
    private:
        // Get the first character in a string mainly to check for comments
        static char GetFirstChar(std::string s) {
            char *letter = &s[0];
            return *letter;
        }
    
    public:
        // Get the line of code
        void FetchLine(void) {
            std::fstream file;

            file.open("src/cycle/test.asm", std::ios::in);
            if (file.is_open()) {
                std::string line;
                while(getline(file, line)) {

                    // Check if the line is a comment and skip
                    if (GetFirstChar(line) == *prefix) {
                        continue;
                    }
                }
                file.close();
            }
        }
} FETCH;