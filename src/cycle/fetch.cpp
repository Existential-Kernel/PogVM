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

#include "../cpu/registers.hpp"

#define WHITESPACE " \n\r\t\f\v"

class FETCH {
    private:

        // Split strings with spaces into a vector 
        static std::vector<std::string> Split(std::string string){
            std::vector<std::string> vector;
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


        // Remove leading and trailing whitespaces/spaces
        static std::string Trim(const std::string &string) {
            std::string trimstring;
            size_t start = string.find_first_not_of(WHITESPACE);
            size_t end = string.find_last_not_of(WHITESPACE);
            trimstring = (start == std::string::npos) ? "" : string.substr(start);
            trimstring = (end == std::string::npos) ? "" : string.substr(0, end + 1);
    
            // Double check for any missed whitespace
            trimstring = std::regex_replace(trimstring, std::regex("^ +| +$|( ) +"), "$1");

            return trimstring;
        }


        // Convert string into packaged vectors of assembly instructions
        static std::vector<std::string> Preprocess(std::string &line, bool verbose) {
            std::cout << "sample: '" << line << "'" << std::endl;

            std::vector<std::string> codevector;

            if (line.find(';') || line.find(',')) {
                std::string filter(line.begin(), std::find(line.begin(), line.end(), ';'));
                filter.erase(std::remove(filter.begin(), filter.end(), ','), filter.end());
                line = filter;
            }

            line = Trim(line);
            codevector = Split(line);

            std::cout << "processed sample: '" << line << "'" << std::endl;

            if (verbose) {
                for (auto &string: codevector) {
                    std::cout << "element: " << string << '\n';
                }
                std::cout << "======================" << "\n";
            }

            return codevector;
        }

    public:
        // Get the line of code
        std::vector<std::vector<std::string>> FetchCode(std::string location, bool verbose) {
            std::fstream file;
            std::string line;
            std::vector<std::vector<std::string>> programvector;

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

            return programvector;
        }
} FETCH;
