#include <thread>
#include <typeinfo>

#include "cycle/fetch.cpp"
#include "cycle/decode.cpp"
#include "cycle/execute.cpp"
#include "defs.hpp"
#include "cpu/memory.hpp"

//https://www.cplusplus.com/reference/thread/thread/?kw=thread

class KERNEL : public FETCH, public DECODE, public EXECUTE {
    public:
		// 
        static void Kernel(const std::string &argv, const bool &mode = false) { // REVISION NEEDED: change mode if needed
			std::vector<u_char> resultvector;
			std::vector<std::vector<u_char>> instructions;
			if (UTILITY::FileExists(argv)) {

				// check if file is an ELF file. Else, check if it's an assembly file
				if (ELF::CheckELF(argv)) {

					if (mode) { // compiled mode
					/**************** FETCH STAGE ****************/		
						//std::vector<u_char> hexvector = FETCH::FetchHex(argv);
						std::vector<u_char> hexvector = FETCH::GetCode();

					/**************** DECODE STAGE ****************/		
						std::vector<u_char> tempvector;
						size_t adjust = 6;

						//if (hexvector.size() < 6) { adjust = hexvector.size(); }
						for (size_t index = 0; (index < hexvector.size());) {
							std::cout << "index: " << index << std::endl;
							std::cout << "size: " << hexvector.size() << std::endl;
							if (hexvector.at(index) == 0x00) { index += 1; continue; }
							tempvector.insert(tempvector.begin(), hexvector.begin() + index, hexvector.begin() + (index + adjust));
							DECODE::Decode(tempvector, resultvector);
							index = resultvector.size();

							instructions.push_back(resultvector);
							tempvector.clear();
							if (index == hexvector.size()) { break; }
						}

					/**************** EXECUTE STAGE ****************/	
						std::cout << "size :" << instructions.size() << std::endl;
						for (size_t x = 0; x < instructions.size(); ++x) {
							EXECUTE::Execute(instructions.at(x));
						}
					} else { // interpreter mode

					}

				} else if (ASSEMBLY::CheckASM(argv)) {
					std::vector<std::vector<std::string>> assemblyvector = FETCH::FetchAssembly(argv);
				} else {
					OUTPUT::Error("Please provide an executable file or an assembly file to virtualise", 0x0C);
				}
			} else {
				if (argv[0] == '-') {
					OUTPUT::Error("Unrecognized flag option", 0x0B);
				} else {
					OUTPUT::Error("The file provided is not valid or does not exist", 0x0A);
				}
			}

/*
			if (!MEMORY::Initialise()) {
				OUTPUT::Error("Memory initialisation failed", 0x11);
			}
*/
		}
} KERNEL;