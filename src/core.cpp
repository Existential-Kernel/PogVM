#include <thread>
#include <typeinfo>

#include "cycle/fetch.cpp"
#include "cycle/decode.cpp"
#include "cycle/execute.cpp"
#include "defs.hpp"
#include "cpu/memory.hpp"

//https://www.cplusplus.com/reference/thread/thread/?kw=thread
/* 
Check if CPU virtualisation support is enabled
	mov eax,1
	cpuid
	bt ecx,5
	jc VMX_Supported
	jmp VMX_NotSupported    
*/

class KERNEL : public FETCH, public DECODE, public EXECUTE {
	private:
		static void InitHardware(void) {
			if (!MEMORY::Initialise()) {
				OUTPUT::Error("Memory initialisation failed", 0x11);
			}
		}

    public:
        static void Kernel(const std::string &argv, const uint8_t &bits, const bool &mode, const uint8_t &processor) {
			std::vector<u_char> resultvector;
			std::vector<std::vector<u_char>> instructions;
			if (UTILITY::FileExists(argv)) {

				// check if file is an ELF file. Else, check if it's an assembly file
				if (ELF::CheckELF(argv)) {

					if (mode) { // compiled mode
						//std::vector<u_char> hexvector = FETCH::FetchHex(argv);
						std::vector<u_char> hexvector = FETCH::GetCode();
						DECODE::Decode(hexvector, instructions, bits, processor);
						EXECUTE::Execute(instructions);

					} else { // threading mode

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
		}
} KERNEL;