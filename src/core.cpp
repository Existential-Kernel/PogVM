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
						for (size_t index = 0; index < hexvector.size(); ++index) {
							if (hexvector.at(index) == 0x00) { 
								hexvector.erase(hexvector.begin() + index);
								continue; 
							}
						}

						DECODE::Decode(hexvector, instructions);

						std::cout << "Decoded instructions: " << std::endl;
						std::cout << UTILITY::IntToHex(instructions.at(0).at(0)) << std::endl;
						std::cout << UTILITY::IntToHex(instructions.at(1).at(0)) << std::endl;
						std::cout << UTILITY::IntToHex(instructions.at(2).at(0)) << std::endl;

					/**************** EXECUTE STAGE ****************/	
						EXECUTE::Execute(instructions);

						std::cout << FLAGS::EFLAGS.eflagcode << std::endl;
		
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