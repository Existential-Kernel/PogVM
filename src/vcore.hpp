#pragma once

#include "cycle/fetch.hpp"
#include "cycle/decode.hpp"
#include "cycle/execute.hpp"

#include "cpu/memory.hpp"

//https://www.cplusplus.com/reference/thread/thread/?kw=thread

class KERNEL final : public FETCH, public DECODE, public EXECUTE {
	public:
		KERNEL();
		~KERNEL();

	private:
		static constexpr void InitHardware(void);

		static bool CheckIfBufferIsEmpty(const std::deque<uint8_t> &buffer);

    public:
	    static void Kernel(const std::string &argv, const uint8_t &bits, const uint8_t &mode, const uint8_t &processor);
};

constexpr void KERNEL::InitHardware(void) {
    if (!MEMORY::Initialise()) {
        OUTPUT::Error("Memory initialisation failed", 0x11);
    }
}

bool KERNEL::CheckIfBufferIsEmpty(const std::deque<uint8_t> &buffer) {
    for (std::deque<uint8_t>::const_reverse_iterator ptr = buffer.rbegin(); ptr != buffer.rend(); ++ptr) {
        if (*ptr != 0) { return true; }
    }
    return false;
}

void KERNEL::Kernel(const std::string &argv, const uint8_t &bits, const uint8_t &mode, const uint8_t &processor) {
	if (UTIL::FileExists(argv, std::filesystem::file_status{})) {
		if (ELF::CheckELF(argv)) {

            // NOTE: This is really bad code, improve it or write my own ELF to BIN converter when I have time
            std::string ELF_file = "objcopy -O binary ";
            ELF_file += argv;
            ELF_file += " ./src/bin/thingy.bin";
            std::system(ELF_file.c_str());

            {
                std::unique_ptr<FETCH>FETCH_PTR     = std::make_unique<FETCH>();
                std::unique_ptr<DECODE>DECODE_PTR   = std::make_unique<DECODE>();
                std::unique_ptr<EXECUTE>EXECUTE_PTR = std::make_unique<EXECUTE>();

                std::vector<std::vector<uint8_t>> instructions{};

                REGISTER Registers;
                STACK Stack;

                switch (mode) {
                    case 3: // VMX mode (actual virtualisation ran on hardware using VMX)
                        {

                        }

                    case 2: // direct mode (bad hardware emulation)
                        {
                            //std::vector<uint8_t> hexvector = FETCH::MassFetch(argv);
                            std::vector<uint8_t> hexvector = FETCH_PTR->GetCode();
                            std::cout << "==== STARTING EMULATION ====\n";
							DECODE_PTR->MassDecode(hexvector, instructions, bits, processor);
                            std::system("./src/tests/elf/helloworld");
                            std::cout << "\n====  ENDING EMULATION  ====\n";
                        }
                        break;

                    case 1: // compiled mode (practical virtualisation)
                        {
                            //std::vector<uint8_t> hexvector = FETCH::MassFetch(argv);
                            std::vector<uint8_t> hexvector = FETCH_PTR->GetCode();
                            DECODE_PTR->MassDecode(hexvector, instructions, bits, processor);
                            EXECUTE_PTR->MassExecute(&Registers, &Stack, instructions);
                        }
                        break;

                    case 0: // threading mode (practical virtualisation)
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

/*							    multithreading in C++ makes me want to kill myself

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
                    default:
                        std::cout << "what the fuck are you doing";

                }
            }

        } else if (UTIL::CheckExtension(argv, "asm") || UTIL::CheckExtension(argv, "s")) {
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

KERNEL::KERNEL()
{
}

KERNEL::~KERNEL()
{
}