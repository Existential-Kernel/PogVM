#include <thread>

#include "cycle/fetch.cpp"
#include "cycle/decode.cpp"
#include "cycle/execute.cpp"
#include "defs.hpp"
#include "cpu/memory.hpp"

class KERNEL : public FETCH, public DECODE, public EXECUTE {
    private:
        /*
        * STEP 1: fetch the file hex data or the assembly instructions
        * STEP 2: decode the assembly instructions into hex if an assembly file was inputted
        * STEP 3: execute the instructions based on their opcode
        */

    public:
	    // Check if there's at least 4 threads in the user's CPU for pipelining
        static inline bool ThreadCheck(void) {
            try {
               return (uint8_t)std::thread::hardware_concurrency() * 2 >= 4;
            } catch (...) {
                return false;
            }
        }

        // Check if CPU cores are working as expected
        static inline bool CoreCheck(void) {
            try {
                return (uint8_t)std::thread::hardware_concurrency() != 0;
            } catch (...) {
                return false;
            }
        }

        static void Kernel(const std::string &argv) {
            if (FUNCTIONS::FileExists(argv)) {
				// check if file is an ELF file. Else, check if it's an assembly file
				if (ELF::CheckELF(FETCH::GetFileHexData(argv))) {

					std::vector<std::vector<u_char> instructions = DECODE::Decode(FETCH::FetchHex(argv));
					EXECUTE::Execute(instructions);




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

			// start shit here assuming the file is valid
			if (!MEMORY::Initialise()) {
				OUTPUT::Error("Memory initialisation failed", 0x11);
			}
        }
} KERNEL;