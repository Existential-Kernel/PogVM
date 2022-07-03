#include <thread>
#include <memory>

#include "cycle/fetch.cpp"
#include "cycle/decode.cpp"
#include "cycle/execute.cpp"
#include "defs.hpp"
#include "cpu/memory.hpp"
#include "cpu/registers.hpp"

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
       #ifdef __linux__       // use polymorphism whenever i have the time
			[[gnu::hot]] 
	   #endif 
	   static void Kernel(const std::string &argv, const uint8_t &bits, const bool &mode, const uint8_t &processor) {
			if (UTIL::FileExists(argv)) {
				if (ELF::CheckELF(argv)) {
					{
						// fuck the new and delete keywords, all my homies use smart pointers
						std::unique_ptr<FETCH>FETCH_PTR = std::make_unique<FETCH>();
						std::unique_ptr<DECODE>DECODE_PTR = std::make_unique<DECODE>();
						std::unique_ptr<EXECUTE>EXECUTE_PTR = std::make_unique<EXECUTE>();

						std::vector<uint8_t> resultvector{};
						std::vector<std::vector<uint8_t>> instructions{};

						REGISTER Reg;

						switch (mode) {
							case true: // compiled mode
								{
									//std::vector<uint8_t> hexvector = FETCH::MassFetchHex(argv);
									std::vector<uint8_t> hexvector = FETCH_PTR->GetCode();
									DECODE_PTR->MassDecode(hexvector, instructions, bits, processor);
									EXECUTE_PTR->MassExecute(&Reg, instructions);
								}
								break;

							case false: // threading mode
								{
									std::vector<uint8_t> hexvector = FETCH_PTR->MassFetchHex(argv);
									std::array<uint8_t, 10> queue{};
									std::vector<uint8_t> instructions{};
									for (;;) {
										//std::thread tfetch(FETCH_PTR->FetchHex, hexvector, queue, offset);   <= done
										//std::thread tdecode(DECODE_PTR->Decode, queue, instructions);        <= done
										//std::thread texecute(EXECUTE_PTR->Execute, &Reg, instructions);      <= done
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
