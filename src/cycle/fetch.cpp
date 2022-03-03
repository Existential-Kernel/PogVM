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

#include "src/CPU/registers.hpp"

class FETCH {
    private:
        static void Split(std::string const &code, const char prefix, std::vector<std::string> &codeVector) { 
            std::stringstream codestream(code);
            std::string s;

            while (std::getline(codestream, s, prefix)) { 
                codeVector.push_back(s);
            }
        } 

        static std::string Preprocess(std::fstream &filestream, std::string &line, bool verbose) {
            while(getline(filestream, line)) {
                if ((int)line[0] == 0) { continue; }
                if (line.find(';')) {
                    if (line[0] == ';') { continue; }


                    //line.erase(line.length(), strchr(line.c_str(), ';'));
                    std::string line(line.begin(), std::find(line.begin(), line.end(), ';'));
                    //std::cout << "prefix index: " << strchr(line.c_str(), ';') << std::endl;
                    std::cout << "filtered : " << line << std::endl;

                    
                }
                if (std::isspace(line[0])) {
                    int length = line.length();
                    int spaceCount;

                    for (int i = 0; i < length; i++) {
                        if (std::isspace(line[i])) {
                            spaceCount++;
                        } else {
                            break;
                        }
                    }

                    line = line.erase(0, spaceCount);
                    spaceCount = 0;
                }
                if (!std::isalpha(line[0])) { continue; }


                // more preprocessing to be added...
                // - Add comment remover if written after instruction code

                std::vector<std::string> codeVector;
                Split(line, ' ', codeVector);

<<<<<<< HEAD
                //REGISTER::CUSREG.IR = line;

                if (verbose == true) {
=======
                if (verbose) {
>>>>>>> 77e842bdab1931f36fd3e2e0d1499966016427f2
                    std::cout << line << "\n";
                    for (auto &string: codeVector) {
                        std::cout << "element: " << string << '\n';
                    }
                    std::cout << "======================" << "\n";
                }
            }
            return line;
        }

    public:
        // Get the line of code
        void FetchLine(void) {
            std::fstream file;

            // Open the file
            file.open("src/cycle/test2.asm", std::ios::in);
            if (file.is_open()) {
                std::string line;



                line = Preprocess(file, line, true);

                std::cout << "test: " << line << std::endl;
                file.close();
            }
        }
} FETCH;


// TODO:
// - create the vector functionality so the vector elements will be the assembly code elements
