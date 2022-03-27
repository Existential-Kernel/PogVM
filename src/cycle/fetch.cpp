#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <regex>
#include <thread>
#include <filesystem>
#include <stdio.h>
#include <ios>
#include <iomanip>

#include "../cpu/registers.hpp"

class STRINGFETCH {
    private:
        // Macros
        #define WHITESPACE " \n\r\t\f\v"
        #define SEPARATOR "======================"
        typedef std::vector<std::string> svec;                // string vector
        typedef std::vector<std::vector<std::string>> dsvec;  // double string vector
        typedef std::string string;

        // Filter for things like comments and commas for simplicity
        static string Filter(string string) {
            // TODO: also filter for '#' comments in certain assembly syntaxes
            if (string.find(';') != string::npos || string.find(',') != string::npos || string.find('#') != string::npos) {
                std::string filter(string.begin(), std::find(string.begin(), string.end(), ';'));
                filter.erase(std::remove(filter.begin(), filter.end(), ','), filter.end());
                string = filter;
            }
            return string;
        }

        // Remove leading, trailing, and inbetween whitespace/spaces
        static string Trim(const string &string) {
            std::string trimstring;
            size_t start = string.find_first_not_of(WHITESPACE);
            size_t end = string.find_last_not_of(WHITESPACE);
            trimstring = (start == string::npos) ? "" : string.substr(start);
            trimstring = (end == string::npos) ? "" : string.substr(0, end + 1);
    
            // Double check for any missed whitespace and inbetween the string too
            trimstring = std::regex_replace(trimstring, std::regex("^ +| +$|( ) +"), "$1");
            trimstring = std::regex_replace(trimstring, std::regex("[' ']{2,}"), " ");

            // Check and remove for inbetween extra spaces
            if (trimstring.find("  ") != string::npos) {
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
        static svec Split(string string){
            svec vector;
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

        // Convert string into a huge vector with packaged vectors of assembly instructions
        static svec Preprocess(string &line, bool verbose) {
            if (verbose) { std::cout << "sample:     '" << line << "'\n"; }

            svec codevector;
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
        static dsvec FetchCode(string location, bool verbose) {
            std::fstream file;
            std::string line;
            dsvec programvector;

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
            //REGISTER.AREG_PTR->PC++;
            return programvector;
        }
};


class HEXFETCH {
    private:
        // Macros
        typedef std::vector<std::string> hvec;                // hex vector
        typedef std::vector<std::vector<std::string>> dhvec;  // double hex vector

    public:
        // Get hex data of file and store in vector (using copilot)
        static void GetFileHexData(const std::string &filename, std::vector<unsigned char> &v, bool verbose) {
            std::ifstream file(filename, std::ios::binary);
            if (file) {
                file.seekg(0, std::ios::end);
                v.resize(file.tellg());
                file.seekg(0, std::ios::beg);
                file.read((char*)&v[0], v.size());

                if (verbose) {
                    for (auto &string: v) {
                        std::cout << "element:    '0x" << std::hex << (int)string << "'\n";
                        printf("%s\n", SEPARATOR);
                    }
                }
            }
            file.close();
        }

        static std::vector<unsigned char> FetchHex(std::string location, bool verbose) {
            std::vector<unsigned char> vector;
            GetFileHexData(location, vector, verbose);
            //CheckELF(vector);
            return vector;
        }
};

class CHECKS {
    public:
        // Check if the file is an ELF file
        static bool CheckELF(std::vector<unsigned char> hexvector) {
            if (hexvector[0] == 0x7F && hexvector[1] == 0x45 && hexvector[2] == 0x4C && hexvector[3] == 0x46) {
                return true;
            } else {
                return false;
            }
        }

        // check if string ends with .asm or .s file extension
        static bool CheckASM(std::string file) {
            std::string extension = file.substr(file.find_last_of(".") + 1);
            if (extension == "asm" || extension == "s") {
                return true;
            } else {
                return false;
            }
        }
};


class FETCH : public STRINGFETCH, public HEXFETCH {
    public:


} FETCH;