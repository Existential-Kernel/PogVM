//#include <future>
#include <memory>
#include <vector>
#include <set>
#include <iterator>

//#include "defs.hpp"

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

		static bool CheckIfBufferIsEmpty(const std::deque<uint8_t> &buffer) {
			for (std::deque<uint8_t>::const_iterator ptr = buffer.begin(); ptr != buffer.end(); ptr++) {
				if (*ptr == 0) {
					return false;
				}
			}
			return true;
		}

    public:
	    GNU_HOT static void Kernel(const std::string &argv, const uint8_t &bits, const uint8_t &mode, const uint8_t &processor) {
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
							case 2: // direct mode (emulation)
								{
									//std::vector<uint8_t> hexvector = FETCH::MassFetch(argv);
									std::vector<uint8_t> hexvector = FETCH_PTR->GetCode();
									DECODE_PTR->MassDecode(hexvector, instructions, bits, processor);
									//std::system()
								}
								break;
	
							case 1: // compiled mode (virtualisation)
								{
									//std::vector<uint8_t> hexvector = FETCH::MassFetch(argv);
									std::vector<uint8_t> hexvector = FETCH_PTR->GetCode();
									DECODE_PTR->MassDecode(hexvector, instructions, bits, processor);
									EXECUTE_PTR->MassExecute(&Registers, &Stack, instructions);
								}
								break;

							case 0: // threading mode (virtualisation)
								{
									//std::deque<uint8_t> hexvector = FETCH_PTR->MassFetch(argv);
									
									std::vector<uint8_t> tempvec = FETCH_PTR->GetCode();
									std::deque<uint8_t> hexqueue;
									for (size_t i = 0; i < tempvec.size(); i++) {
										hexqueue.push_back(tempvec.at(i));
									}
									std::deque<uint8_t> buffer{};
									std::vector<uint8_t> instruction{};

									FETCH_PTR->Fetch(hexqueue, buffer);

									do {

/*										multithreading in C++ makes me want to kill myself

										std::thread tfetch(FETCH_PTR->Fetch, hexqueue, buffer);
										std::thread tdecode(DECODE_PTR->Decode, buffer, instruction, bits, processor);
										std::thread texecute(EXECUTE_PTR->Execute, &Registers, &Stack, instruction);
*/										
										FETCH_PTR->Fetch(hexqueue, buffer);
										DECODE_PTR->Decode(buffer, instruction, bits, processor);
										EXECUTE_PTR->Execute(&Registers, &Stack, instruction);
									} while (CheckIfBufferIsEmpty(buffer));
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
