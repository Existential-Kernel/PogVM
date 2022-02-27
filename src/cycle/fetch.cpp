#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include <array>
#define prefix ";"

class FETCH {
    private:
    
    public:
        // Get the line of code
        void FetchLine(void) {
            std::fstream file;

            // Open the file
            file.open("src/cycle/test.asm", std::ios::in);
            if (file.is_open()) {
                std::string line;
                while(getline(file, line)) {
                    if (line[0] == ';') { continue; }
                    if ((int)line[0] == 0) { continue; }
                    if (line[0] == ' ') {
                        int length = line.length();
                        int spaceCount;
                        std::cout << "length: " << length << std::endl;
                        for (int i = 0; i < length; i++) {
                            if ((int)line[i] == 32) {
                                spaceCount++;
                            } else {
                                break;
                            }
                            std::cout << "spacecount: " << spaceCount << std::endl;
                        }
                        remove(line.begin(), line.begin() + spaceCount, ' ');
                    }

                    std::cout << line << std::endl;
                    //std::cout << (int)line[0] << std::endl;

                    //std::cout << line << std::endl;
                }
                file.close();
            }
        }
} FETCH;