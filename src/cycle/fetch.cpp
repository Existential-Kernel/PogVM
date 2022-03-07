#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include <array>
#include <cctype>
#include <regex>
#include <thread>

#include "../cpu/registers.hpp"
//#include "src/cpu/registers.hpp"

class FETCH {
    private:
        static std::vector<std::string> Preprocess(std::string &line, std::vector<std::string> &codeVector, bool verbose) {
            if (line.find(';')) {
                std::string filter(line.begin(), std::find(line.begin(), line.end(), ';'));
                line = filter;
            }

            // Remove trailing spaces at beginning and end of string
            line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");

            std::stringstream codestream(line);
            std::string s;

            while (std::getline(codestream, s, ' ')) {
                if (s.length() != 0) {
                    /*
                    if (s.find(',') != std::string::npos) {
                        int index = s.find(',');
                        if (s[index + 1] == ' ') {
                            
                        }
                    }
                    */
    
                    if (s[s.length() - 1] == ',') {
                        s.resize(s.size() - 1);
                    }
                    codeVector.push_back(s);
                }
            }

            if (verbose) {
                std::cout << "string: " << line << "\n";
                for (auto &string: codeVector) {
                    std::cout << "element: " << string << '\n';
                }
                std::cout << "======================" << "\n";
            }

            return codeVector;
        }

    public:
        // Get the line of code
        void FetchLine(void) {
            std::fstream file;
            std::string line;
            std::vector<std::vector<std::string>> program;
            std::vector<std::string> code;

            // Open the file
            file.open("src/cycle/test2.asm", std::ios::in);
            if (file.is_open()) {

                while (std::getline(file, line)) {
                    // Prefiltering unnecessary assembly lines
                    if ((int)line[0] == 0) { continue; }
                    if (line[0] == ';') { continue; }
                    if (!std::any_of(std::begin(line), std::end(line), ::isalpha)) { continue; }

                    code = Preprocess(line, code, true);
                }

                for (auto &string: code) {
                    std::cout << "element code: " << string << '\n';
                    std::cout << "================" << '\n';
                }

                file.close();
            }
        }
} FETCH;
