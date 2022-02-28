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
        size_t Split(const std::string &text, std::vector<std::string> &code, unsigned char ch) {
            size_t pos = text.find(ch);
            size_t start = 0;
            code.clear();

            while (pos != std::string::npos) {
                code.push_back(text.substr(start, pos - start));
                start = pos + 1;

                pos = text.find(ch, start);
            }

            code.push_back(text.substr(start, std::min(pos, text.size()) - start + 1));
            return code.size();
        }

        std::string Preprocess(std::fstream &filestream, std::string &line, bool verbose) {
            while(getline(filestream, line)) {
                if (line[0] == ';') { continue; }
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

                std::istringstream iss(line);

                if (verbose == true) {
                    std::cout << line << "\n";
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
                std::vector<std::string> assemblyArray;

                Split(line, assemblyArray, ' ');

                line = Preprocess(file, line, true);
                std::cout << "test: " << line << std::endl;
                file.close();
            }
        }
} FETCH;


// TODO:
// - create the vector functionality so the vector elements will be the assembly code elements
