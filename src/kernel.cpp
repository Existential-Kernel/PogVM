#include <thread>

#include "cycle/fetch.cpp"
#include "cycle/decode.cpp"
#include "cycle/execute.cpp"
#include "defs.hpp"
#include "cpu/memory.hpp"

class AUDIT {
	private:
		// Log the initialisation process if it succeeded or failed
		static void AuditLog(bool result, const std::string &message) {
			if (result) {
				std::cout << "[" << ANSI::BLACK_BG << ANSI::GREEN << "SUCCESS" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT<< std::endl;
			} else {
				std::cout << "[" << ANSI::BLACK_BG << ANSI::RED << "FAILED" << ANSI::EXIT << "] " << ANSI::BOLD << message << ANSI::EXIT << std::endl;
			}
		}

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

	public:
		// Checks all the necessary processes and data needed to run the machine
		static void AuditCheck(void) {
			AuditLog(MEMORY::Initialise(), "2^32 bits of memory space allocated");
			//AuditLog(REGISTER::ResetAll(), "All registers have been reset");
			AuditLog(AUDIT::CoreCheck(), "CPU working as expected");
			AuditLog(AUDIT::ThreadCheck(), "Verified for necessary thread count for pipeline processing");
			//AuditLog(ASSEMBLY::AssemblyTest(), "Tested x86 assembly code");
		}
};

class KERNEL : public FETCH, public DECODE, public EXECUTE {
    private:
        /*
        * STEP 1: fetch the file hex data or the assembly instructions
        * STEP 2: decode the assembly instructions into hex if an assembly file was inputted
        * STEP 3: execute the instructions based on their opcode
        */

    public:
		// 
        static void Kernel(const std::string &argv) {
            if (FUNCTIONS::FileExists(argv)) {
				// check if file is an ELF file. Else, check if it's an assembly file
				if (ELF::CheckELF(FETCH::FetchHex(argv))) {
					std::vector<u_char> hexvector = FETCH::FetchHex(argv);
					std::vector<u_char> testvector = FETCH::GetCode();
					std::vector<std::vector<u_char>> instructions = DECODE::Decode(testvector);

					for (size_t i = 0; i < instructions.size(); i++) {
						EXECUTE::Execute(
							instructions.at(i).at(0),
							instructions.at(i).at(1),
							instructions.at(i).at(2),
							instructions.at(i).at(3),
							instructions.at(i).at(4)
						);
					}

					/*
					std::vector<std::vector<u_char> instructions = DECODE::Decode(FETCH::FetchHex(argv));
					EXECUTE::Execute(instructions);
					*/


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