#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include <array>
#include <ctype.h>
#include <regex>

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
                if (line.find(';')) { 
                    if (line[0] == ';') { continue; }
                    // TODO: fix this shit
                    line.erase(line.length(), strchr(line.c_str(), ';'));
                }
                if ((int)line[0] == 0) { continue; }
                if (isspace(line[0])) {
                    int length = line.length();
                    int spaceCount;

                    for (int i = 0; i < length; i++) {
                        if (isspace(line[i])) {
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

                if (verbose == true) {
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
