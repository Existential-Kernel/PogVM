#include <thread>
#include <memory>
#include <vector>

#include "defs.hpp"

#include "cycle/fetch.cpp"
#include "cycle/decode.cpp"
#include "cycle/execute.cpp"

#include "cpu/memory.hpp"
#include "cpu/registers.hpp"
#include "cpu/stack.hpp"

//https://www.cplusplus.com/reference/thread/thread/?kw=thread

class KERNEL final : public FETCH, public DECODE, public EXECUTE {
	public:
		KERNEL() {};
		~KERNEL() {};

	private:
		static constexpr void InitHardware(void) {
			if (!MEMORY::Initialise()) {
				OUTPUT::Error("Memory initialisation failed", 0x11);
			}
		}

    public:
	    GNU_HOT static void Kernel(const std::string &argv, const uint8_t &bits, const bool &mode, const uint8_t &processor) {
			if (UTIL::FileExists(argv)) {
				if (ELF::CheckELF(argv)) {
					{
						// fuck the new and delete keywords, all my homies use smart pointers
						std::unique_ptr<FETCH>FETCH_PTR = std::make_unique<FETCH>();
						std::unique_ptr<DECODE>DECODE_PTR = std::make_unique<DECODE>();
						std::unique_ptr<EXECUTE>EXECUTE_PTR = std::make_unique<EXECUTE>();

						std::vector<uint8_t> resultvector{};
						std::vector<std::vector<uint8_t>> instructions{};

						REGISTER Registers;
						STACK Stack;

						switch (mode) {
							case true: // compiled mode
								{
									//std::vector<uint8_t> hexvector = FETCH::MassFetch(argv);
									std::vector<uint8_t> hexvector = FETCH_PTR->GetCode();
									DECODE_PTR->MassDecode(hexvector, instructions, bits, processor);
									EXECUTE_PTR->MassExecute(&Registers, &Stack, instructions);
								}
								break;

							case false: // threading mode
								{
									std::deque<uint8_t> hexvector = FETCH_PTR->MassFetch(argv);
									std::deque<uint8_t> queue{};
									std::vector<uint8_t> instruction{};

									for (;;) {
/*
										std::thread tfetch(FETCH_PTR->FetchHex, hexvector, queue, offset);                   <=
										std::thread tdecode(DECODE_PTR->Decode, queue, instruction, bits, processor);        <=
										std::thread texecute(EXECUTE_PTR->Execute, &Reg, &Stack, instruction);               <=
*/
/*									
										FETCH_PTR->Fetch(hexvector, queue);                         // <= done
										DECODE_PTR->Decode(queue, instruction, bits, processor);    // <=
										EXECUTE_PTR->Execute(&Registers, &Stack, instruction);      // <=
*/
									}

								}
								break;

						}
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
};
