#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <cctype>
#include <regex>
#include <thread>
#include <filesystem>
#include <stdio.h>

#include "../cpu/registers.hpp"


// Macros
#define WHITESPACE " \n\r\t\f\v"
#define SEPARATOR "======================"
typedef std::vector<std::string> vec;
typedef std::vector<std::vector<std::string>> doublevec;


class FETCH {
    private:

        // Filter for things like comments and commas for simplicity
        static std::string Filter(std::string string) {
            // TODO: also filter for '#' comments in certain assembly syntaxes
            if (string.find(';') != std::string::npos || string.find(',') != std::string::npos || string.find('#') != std::string::npos) {
                std::string filter(string.begin(), std::find(string.begin(), string.end(), ';'));
                filter.erase(std::remove(filter.begin(), filter.end(), ','), filter.end());
                string = filter;
            }
            return string;
        }


        // Remove leading, trailing, and inbetween whitespace/spaces
        static std::string Trim(const std::string &string) {
            std::string trimstring;
            size_t start = string.find_first_not_of(WHITESPACE);
            size_t end = string.find_last_not_of(WHITESPACE);
            trimstring = (start == std::string::npos) ? "" : string.substr(start);
            trimstring = (end == std::string::npos) ? "" : string.substr(0, end + 1);
    
            // Double check for any missed whitespace and inbetween the string too
            trimstring = std::regex_replace(trimstring, std::regex("^ +| +$|( ) +"), "$1");
            trimstring = std::regex_replace(trimstring, std::regex("[' ']{2,}"), " ");

            // Check and remove for inbetween extra spaces
            if (trimstring.find("  ") != std::string::npos) {
                std::string inputstring = "";
                inputstring += trimstring[0];
                for (size_t i = 1; i < trimstring.length(); ++i) {
                    if (trimstring[i] == ' ' && trimstring[i] == trimstring[i-1]) {
                        continue;
                    } else {
                        inputstring += trimstring[i];
                    }
                    trimstring = inputstring;
                }
            }

            return trimstring;
        }


        // Split string argument with spaces into a vector 
        static vec Split(std::string string){
            vec vector;
            std::string nullstring = "";

            for (size_t i = 0; i < string.size(); ++i) {
                if (string[i] == ' ') {
                    vector.push_back(nullstring);
                    nullstring = "";
                } else {
                    nullstring.push_back(string[i]);
                }
            }
            
            vector.push_back(nullstring);
            return vector;
        }

        // Convert string into a massive vector with packaged vectors of assembly instructions
        static vec Preprocess(std::string &line, bool verbose) {
            if (verbose) { std::cout << "sample:     '" << line << "'\n"; }

            vec codevector;
            line = Filter(line);
            line = Trim(line);
            codevector = Split(line);

            if (verbose) {
                std::cout << "preprocess: '" << line << "'\n";
                for (auto &string: codevector) {
                    std::cout << "element:    '" << string << "'\n";
                }
                printf("%s\n", SEPARATOR);
            }

            return codevector;
        }

    public:
        // Get the line of code
        static doublevec FetchCode(std::string location, bool verbose) {
            std::fstream file;
            std::string line;
            doublevec programvector;

            // Open the file
            file.open((location), std::ios::in);
            if (file.is_open()) {
                while (std::getline(file, line)) {
                    // Prefiltering unnecessary assembly lines
                    if ((int)line[0] == 0) { continue; }
                    if (line[0] == ';') { continue; }
                    if (!std::any_of(std::begin(line), std::end(line), ::isalpha)) { continue; }

                    programvector.push_back(Preprocess(line, verbose));
                }
                file.close();
            }
            REGISTER.AREG_PTR->PC++;
            return programvector;
        }
} FETCH;