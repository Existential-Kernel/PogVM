//#include <string>


#include "../defs.hpp"

#include <vector>
#include <regex>
//#include <filesystem>
//#include <ios>
//#include <iomanip>

#include "fetch.hpp"
#include "../cpu/registers.hpp"

// Filter for things like comments and commas for simplicity
[[nodiscard]] std::string ASSEMBLY::Filter(const std::string &string) {
    // TODO: also filter for '#' comments in certain assembly syntaxes
    std::string filter{};
    if (string.find(';') != std::string::npos || string.find(',') != std::string::npos || string.find('#') != std::string::npos) {
        std::string commentfilter(string.begin(), std::find(string.begin(), string.end(), ';'));
        filter = commentfilter;
        filter.erase(std::remove(filter.begin(), filter.end(), ','), filter.end());
    }
    return filter;
}

// Remove leading, trailing, and inbetween whitespace/spaces
[[nodiscard]] std::string ASSEMBLY::Trim(const std::string &string) {
    std::string trimstring{};
    size_t start = string.find_first_not_of(WHITESPACE);
    size_t end = string.find_last_not_of(WHITESPACE);
    trimstring = (start == std::string::npos) ? "" : string.substr(start);
    trimstring = (end == std::string::npos) ? "" : string.substr(0, end + 1);

    // Double check for any missed whitespace, also check between the string too
    trimstring = std::regex_replace(trimstring, std::regex("^ +| +$|( ) +"), "$1");
    trimstring = std::regex_replace(trimstring, std::regex("[' ']{2,}"), " ");

    // Check and remove for inbetween extra spaces
    std::string inputstring{};
    if (trimstring.find("  ") != std::string::npos) [[unlikely]] {
        inputstring += trimstring[0];
        for (size_t i = 1; i < trimstring.length(); ++i) {
            if (trimstring[i] == ' ' && trimstring[i] == trimstring[i-1]) { continue; }
            else { inputstring += trimstring[i]; }
        }
    }
    return inputstring;
}

// Split string argument with spaces into a vector 
[[nodiscard]] std::vector<std::string> ASSEMBLY::Split(const std::string &string) {
    std::vector<std::string> vector{};
    std::string nullstring{};

    for (size_t i = 0; i < string.size(); ++i) {
        if (string[i] == ' ') {
            vector.push_back(nullstring);
            nullstring = "";
        } else {
            nullstring.push_back(string[i]);
        }
    }
    
    vector.push_back(nullstring);
    return vector;
}

// Convert string into a huge vector with packaged vectors of assembly instructions
[[nodiscard]] std::vector<std::string> ASSEMBLY::Preprocess(std::string &line) {
    std::vector<std::string> codevector;
    line = Filter(line);
    line = Trim(line);
    codevector = Split(line);
    return codevector;
}

[[nodiscard]] std::vector<std::vector<std::string>> ASSEMBLY::FetchAssembly(const std::string &location) {
    std::fstream file{};
    std::string line{};
    std::vector<std::vector<std::string>> programvector{};

    // Open the file
    file.open((location), std::ios::in);
    if (file.is_open()) [[likely]] {
        while (std::getline(file, line)) {
            // Prefiltering unnecessary assembly lines
            if (static_cast<uint>(line[0]) == 0) { continue; }
            if (line[0] == ';') { continue; }
            if (!std::any_of(std::begin(line), std::end(line), ::isalpha)) { continue; }

            programvector.push_back(Preprocess(line));
        }
        file.close();
    }
    return programvector;
}

[[nodiscard]] bool ASSEMBLY::CheckASM(const std::string &file) {
    std::string extension = file.substr(file.find_last_of(".") + 1);
    return (extension == "asm" || extension == "s");
}

void ELFHEADER::GetELFProgram(const std::vector<unsigned char> &hex, const uint64_t &offset) {
    unsigned char program[0x38];
    for (uint16_t x = offset, i = 0; x < offset + 0x38; ++x, ++i) { program[i] = hex.at(x); }

    // Get the program type
    ELF_PROGRAM.ph_type = program[0x03] << 24 | program[0x02] << 16 | program[0x01] << 8 | program[0x00];
    switch (ELF_PROGRAM.ph_type) {
        case 0x00: ELF_PROGRAM.ph_typename = "Unused table entry"; break;
        case 0x01: ELF_PROGRAM.ph_typename = "Loadable segment"; break;
        case 0x02: ELF_PROGRAM.ph_typename = "Dynamic linking information"; break;
        case 0x03: ELF_PROGRAM.ph_typename = "Interpreter info"; break;
        case 0x04: ELF_PROGRAM.ph_typename = "Auxiliary information"; break;
        case 0x05: ELF_PROGRAM.ph_typename = "Reserved"; break;
        case 0x06: ELF_PROGRAM.ph_typename = "Contained program header table"; break;
        case 0x07: ELF_PROGRAM.ph_typename = "Thread-Local storage template"; break;
        default:
            if (ELF_PROGRAM.ph_type >= 0x60000000 && ELF_PROGRAM.ph_type <= 0x6FFFFFFF) {
                OUTPUT::Error("Operating system specific inclusive ranges for program header type have not yet been implemented for PogVM as of now.", 0x06);
            } else if (ELF_PROGRAM.ph_type >= 0x70000000 && ELF_PROGRAM.ph_type <= 0x7FFFFFFF) {
                OUTPUT::Error("Processor specific inclusive ranges for program header type have not yet been implemented for PogVM as of now.", 0x0E);
            } else {
                OUTPUT::Error("Unknown program header type.", 0x0F);
            }
    }

    // Get the program flags and stuff like that
    if (ELF_HEADER.bits) {
        ELF_PROGRAM.ph_flags  = program[0x07] << 24 | program[0x06] << 16 | program[0x05] << 8 | program[0x04];
        ELF_PROGRAM.ph_offset = program[0x0B] << 24 | program[0x0A] << 16 | program[0x09] << 8 | program[0x08];
        ELF_PROGRAM.ph_vaddr  = program[0x13] << 24 | program[0x12] << 16 | program[0x11] << 8 | program[0x10];
        ELF_PROGRAM.ph_paddr  = program[0x1B] << 24 | program[0x1A] << 16 | program[0x19] << 8 | program[0x18];
        ELF_PROGRAM.ph_filesz = program[0x23] << 24 | program[0x22] << 16 | program[0x21] << 8 | program[0x20];
        ELF_PROGRAM.ph_memsz  = program[0x2B] << 24 | program[0x2A] << 16 | program[0x29] << 8 | program[0x28];
        ELF_PROGRAM.ph_align  = program[0x33] << 24 | program[0x32] << 16 | program[0x31] << 8 | program[0x30];
    } else {
        ELF_PROGRAM.ph_flags  = program[0x1B] << 24 | program[0x1A] << 16 | program[0x19] << 8 | program[0x18];
        ELF_PROGRAM.ph_offset = program[0x07] << 24 | program[0x06] << 16 | program[0x05] << 8 | program[0x04];
        ELF_PROGRAM.ph_vaddr  = program[0x0B] << 24 | program[0x0A] << 16 | program[0x09] << 8 | program[0x08];
        ELF_PROGRAM.ph_paddr  = program[0x0F] << 24 | program[0x0E] << 16 | program[0x0D] << 8 | program[0x0C];
        ELF_PROGRAM.ph_filesz = program[0x13] << 24 | program[0x12] << 16 | program[0x11] << 8 | program[0x10];
        ELF_PROGRAM.ph_memsz  = program[0x17] << 24 | program[0x16] << 16 | program[0x15] << 8 | program[0x14];
        ELF_PROGRAM.ph_align  = program[0x1F] << 24 | program[0x1E] << 16 | program[0x1D] << 8 | program[0x1C];
    }

    // TODO: fix this part
    switch (ELF_PROGRAM.ph_flags) {
        case 0x01: ELF_PROGRAM.ph_flagsname = "Executable"; break;
        case 0x02: ELF_PROGRAM.ph_flagsname = "Writable"; break;
        case 0x04: ELF_PROGRAM.ph_flagsname = "Readable"; break;
    }
}

void ELFHEADER::OutputELFHeader(void) noexcept {
    std::cout << ANSI::BOLD << "Magic:                    " << ANSI::EXIT;
    for (int i = 0; i < 16; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ELF_HEADER.e_ident[i]) << " ";
    }
    std::cout 
        << "\n"
        << ANSI::BOLD << "Bit class:                " << ANSI::EXIT << (ELF_HEADER.bits ? "64-bit" : "32-bit") << "\n"
        << ANSI::BOLD << "Data encoding:            " << ANSI::EXIT << ELF_HEADER.data << "\n"
        << ANSI::BOLD << "OS/ABI:                   " << ANSI::EXIT << ELF_HEADER.OSABI << "\n"
        << ANSI::BOLD << "ABI version:              " << ANSI::EXIT << static_cast<uint8_t>(ELF_HEADER.ABIversion) << "\n"
        << ANSI::BOLD << "Type:                     " << ANSI::EXIT << ELF_HEADER.type << "\n"
        << ANSI::BOLD << "Machine:                  " << ANSI::EXIT << ELF_HEADER.machine << "\n"
        << ANSI::BOLD << "Version:                  " << ANSI::EXIT << ELF_HEADER.version << "\n"
        << ANSI::BOLD << "Entry point:              " << ANSI::EXIT << "0x" << ELF_HEADER.entry << "\n"
        << ANSI::BOLD << "Program header offset:    " << ANSI::EXIT << std::dec << ELF_HEADER.phoff << "\n"
        << ANSI::BOLD << "Section header offset:    " << ANSI::EXIT << ELF_HEADER.shoff << "\n"
        << ANSI::BOLD << "Flags:                    " << ANSI::EXIT << "0x" << ELF_HEADER.flags << "\n"
        << ANSI::BOLD << "ELF header size:          " << ANSI::EXIT << ELF_HEADER.ehsize << "\n"
        << ANSI::BOLD << "Program header size:      " << ANSI::EXIT << ELF_HEADER.phentsize << "\n"
        << ANSI::BOLD << "Program header count:     " << ANSI::EXIT << ELF_HEADER.phnum << "\n"
        << ANSI::BOLD << "Section header size:      " << ANSI::EXIT << ELF_HEADER.shentsize << "\n"
        << ANSI::BOLD << "Section header count:     " << ANSI::EXIT << ELF_HEADER.shnum << "\n"
        << ANSI::BOLD << "Section header string:    " << ANSI::EXIT << ELF_HEADER.shstrndx << "\n"
    << "\n";
}

void ELFHEADER::OutputELFProgram(const std::vector<unsigned char> &header) noexcept {
    GetELFProgram(header, ELF_HEADER.phoff);
    std::cout << "\n"
        << ANSI::BOLD << "Program segment type:        " << ANSI::EXIT << ELF_PROGRAM.ph_typename << "\n"
        << ANSI::BOLD << "Segment-dependent flags:     " << ANSI::EXIT << ELF_PROGRAM.ph_flagsname << "\n"
        << ANSI::BOLD << "Segment offset:              " << ANSI::EXIT << ELF_PROGRAM.ph_offset << "\n"
        << ANSI::BOLD << "Virtual segment address:     " << ANSI::EXIT << ELF_PROGRAM.ph_vaddr << "\n"
        << ANSI::BOLD << "Physical segment address:    " << ANSI::EXIT << ELF_PROGRAM.ph_paddr << "\n"
        << ANSI::BOLD << "Segment size in file image:  " << ANSI::EXIT << ELF_PROGRAM.ph_filesz << "\n"
        << ANSI::BOLD << "Segment size in memory:      " << ANSI::EXIT << ELF_PROGRAM.ph_memsz << "\n"
        << ANSI::BOLD << "Program segment align:       " << ANSI::EXIT << ELF_PROGRAM.ph_align << "\n"
    << "\n";
}

void ELFHEADER::GetELFHeader(const std::vector<uint8_t> &hex) noexcept {
    // Get the ELF file's first 16 bytes
    unsigned char header[0x40];
    for (size_t x = 0; x < 0x40; ++x) { 
        header[x] = hex.at(x);
        if (x < 16) { ELF_HEADER.e_ident[x] = hex.at(x); }
    }

    // Get the ELF bit class (true = 64-bit, false = 32-bit)
    switch (header[0x04]) {
                     case 0x01: ELF_HEADER.bits = false; break;
        [[likely]]   case 0x02: ELF_HEADER.bits = true; break;
        [[unlikely]] default: OUTPUT::Error("ELF class is invalid. 5th hex of identification header list must be 0x01 or 0x02", 0x09); break;
    };

    // Get endianness
    switch (header[0x05]) {
        [[likely]]   case 0x01: ELF_HEADER.data = "Least Significant Bit (Little Endian)"; break;
                     case 0x02: ELF_HEADER.data = "Most Significant Bit (Big Endian)"; break;
        [[unlikely]] default: OUTPUT::Error("ELF data is invalid. 6th hex of identification header list must be 0x01 or 0x02", 0x08); break;
    };

    // Get the OS/ABI system
    switch (header[0x07]) {
        [[likely]]   case 0x00: ELF_HEADER.OSABI = "System V"; break;
        [[unlikely]] case 0x01: ELF_HEADER.OSABI = "HP-UX"; break;
        [[unlikely]] case 0x02: ELF_HEADER.OSABI = "NetBSD"; break;
                     case 0x03: ELF_HEADER.OSABI = "Linux"; break;
        [[unlikely]] case 0x04: ELF_HEADER.OSABI = "GNU Hurd"; break;
                     case 0x06: ELF_HEADER.OSABI = "Sun Solaris"; break;
        [[unlikely]] case 0x07: ELF_HEADER.OSABI = "AIX"; break;
        [[unlikely]] case 0x08: ELF_HEADER.OSABI = "IRIX"; break;
        [[unlikely]] case 0x09: ELF_HEADER.OSABI = "FreeBSD"; break;
        [[unlikely]] case 0x0A: ELF_HEADER.OSABI = "Compaq TRU64 UNIX"; break;
        [[unlikely]] case 0x0B: ELF_HEADER.OSABI = "Novell Modesto"; break;
                     case 0x0C: ELF_HEADER.OSABI = "OpenBSD"; break;
        [[unlikely]] case 0x0D: ELF_HEADER.OSABI = "OpenVMS"; break;
        [[unlikely]] case 0x0E: ELF_HEADER.OSABI = "HP NonStop Kernel"; break;
        [[unlikely]] case 0x0F: ELF_HEADER.OSABI = "AROS"; break;
        [[unlikely]] case 0x10: ELF_HEADER.OSABI = "Fenix OS"; break;
        [[unlikely]] case 0x11: ELF_HEADER.OSABI = "CloudABI"; break;
        [[unlikely]] case 0x12: ELF_HEADER.OSABI = "Stratus Technologies OpenVOS"; break;
        [[unlikely]] default: 
            if (header[0x07] >= 0x40) {
                OUTPUT::Error("Architecure specific value ranges have not yet been implemented for PogVM as of now.", 0x07);
                break;
            } else {
                OUTPUT::Error("Invalid OS ABI value", 0x05); 
                break;
            }
    };

    // Get the ABI version
    ELF_HEADER.ABIversion = header[0x08];

    // Get the ELF file type
    switch (header[0x10]) {
        [[unlikely]] case 0x00: ELF_HEADER.type = "Unknown file type"; break;
        [[unlikely]] case 0x01: ELF_HEADER.type = "Relocatable file"; break;
        [[likely]]   case 0x02: ELF_HEADER.type = "Executable file"; break;
                     case 0x03: ELF_HEADER.type = "Shared object file"; break;
        [[unlikely]] case 0x04: ELF_HEADER.type = "Core file"; break;
        [[unlikely]] default:
            const uint16_t type = header[16] << 8 | header[17];
            if (type >= 0xFE00 && type <= 0xFEFF) {
                OUTPUT::Error("OS specific inclusive ranges in ELF header type value have not yet been implemented for PogVM as of now.", 0x04);
            } else if (type >= 0xFF00) {
                OUTPUT::Error("Processor specific inclusive ranges in ELF header type value have not yet been implemented for PogVM as of now.", 0x03);
            } else {
                OUTPUT::Error("Invalid file type", 0x02);
            }
    }

    // Determine the processor name, This will evaluate the most common processors first
    switch (header[0x12]) {
        [[likely]]   case 0x03: ELF_HEADER.machine = "x86"; break;
                     case 0x28: ELF_HEADER.machine = "Advanced RISC Machines ARM"; break;
        [[likely]]   case 0x3E: ELF_HEADER.machine = "AMD x86-64 architecture"; break;
                     case 0xB7: ELF_HEADER.machine = "ARM 64-bits (ARMv8/Aarch64)"; break;
        [[unlikely]] case 0x08: ELF_HEADER.machine = "MIPS I Architecture"; break;
        [[unlikely]] case 0x15: ELF_HEADER.machine = "64-bit PowerPC "; break;
        [[unlikely]] case 0xF3: ELF_HEADER.machine = "RISC-V"; break;
        default:
            /*
            * Evaluate rare or legacy processors, this is added as a default case in the above switch 
            * statement for the purpose of code compartmentalisation, if that's even a word ¯\_(ツ)_/¯
            */
            switch (header[0x12]) {
                case 0x01: ELF_HEADER.machine = "AT&T WE 32100"; break;
                case 0x02: ELF_HEADER.machine = "SPARC"; break;
                case 0x04: ELF_HEADER.machine = "Motorola 68000"; break;
                case 0x05: ELF_HEADER.machine = "Motorola 88000"; break;
                case 0x07: ELF_HEADER.machine = "Intel 80860"; break;
                case 0x09: ELF_HEADER.machine = "IBM System/370 Processor"; break;
                case 0x0A: ELF_HEADER.machine = "MIPS RS3000 Little-endian"; break;
                case 0x0E: ELF_HEADER.machine = "Hewlett-Packard PA-RISC"; break;
                case 0x13: ELF_HEADER.machine = "Intel 80960"; break;
                case 0x14: ELF_HEADER.machine = "PowerPC"; break;
                case 0x16: ELF_HEADER.machine = "S390, including S390x "; break;
                case 0x17: ELF_HEADER.machine = "IBM SPU/SPC "; break; 
                case 0x24: ELF_HEADER.machine = "NEC V800"; break;
                case 0x25: ELF_HEADER.machine = "Fujitsu FR20"; break;
                case 0x26: ELF_HEADER.machine = "TRW RH-32"; break;
                case 0x27: ELF_HEADER.machine = "Motorola RCE"; break;
                case 0x29: ELF_HEADER.machine = "Digital Alpha"; break;
                case 0x2A: ELF_HEADER.machine = "Hitachi SH"; break;
                case 0x2B: ELF_HEADER.machine = "SPARC Version 9"; break;
                case 0x2C: ELF_HEADER.machine = "Siemens TriCore embedded processor"; break;
                case 0x2D: ELF_HEADER.machine = "Argonaut RISC Core, Argonaut Technologie Inc."; break;
                case 0x2E: ELF_HEADER.machine = "Hitachi H8/300"; break;
                case 0x2F: ELF_HEADER.machine = "Hitachi H8/300H"; break;
                case 0x30: ELF_HEADER.machine = "Hitachi H8S"; break;
                case 0x31: ELF_HEADER.machine = "Hitachi H8/500"; break;
                case 0x32: ELF_HEADER.machine = "Intel IA-64 processor architecture"; break;
                case 0x33: ELF_HEADER.machine = "Stanford MIPS-X"; break;
                case 0x34: ELF_HEADER.machine = "Motorola ColdFire"; break;
                case 0x35: ELF_HEADER.machine = "Motorola M68HC12"; break;
                case 0x36: ELF_HEADER.machine = "Fujitsu MMA Multimedia Accelerator"; break;
                case 0x37: ELF_HEADER.machine = "Siemens PCP"; break;
                case 0x38: ELF_HEADER.machine = "Sony nCPU embedded RISC processor"; break;
                case 0x39: ELF_HEADER.machine = "Denso NDR1 microprocessor"; break;
                case 0x3A: ELF_HEADER.machine = "Motorola Star*Core processor"; break;
                case 0x3B: ELF_HEADER.machine = "Toyota ME16 processor"; break;
                case 0x3C: ELF_HEADER.machine = "STMicroelectronics ST100 processor"; break;
                case 0x3D: ELF_HEADER.machine = "Advanced Logic Corp. TinyJ embedded processor"; break;
                case 0x3F: ELF_HEADER.machine = "Sony DSP Processor"; break;
                case 0x40: ELF_HEADER.machine = "Digital Equipment Corp. PDP-10"; break;
                case 0x41: ELF_HEADER.machine = "Digital Equipment Corp. PDP-11"; break;
                case 0x42: ELF_HEADER.machine = "Siemens FX66 microcontroller"; break;
                case 0x43: ELF_HEADER.machine = "STMicroelectronics ST9+ 8/16 bit microcontroller"; break;
                case 0x44: ELF_HEADER.machine = "STMicroelectronics ST7 8-bit microcontroller"; break;
                case 0x45: ELF_HEADER.machine = "Motorola MC68HC16 Microcontroller"; break;
                case 0x46: ELF_HEADER.machine = "Motorola MC68HC11 Microcontroller"; break;
                case 0x47: ELF_HEADER.machine = "Motorola MC68HC08 Microcontroller"; break;
                case 0x48: ELF_HEADER.machine = "Motorola MC68HC05 Microcontroller"; break;
                case 0x49: ELF_HEADER.machine = "Silicon Graphics SVx"; break;
                case 0x4A: ELF_HEADER.machine = "STMicroelectronics ST19 8-bit microcontroller"; break;
                case 0x4B: ELF_HEADER.machine = "Digital VAX"; break;
                case 0x4C: ELF_HEADER.machine = "Axis Communications 32-bit embedded processor"; break;
                case 0x4D: ELF_HEADER.machine = "Infineon Technologies 32-bit embedded processor"; break;
                case 0x4E: ELF_HEADER.machine = "Element 14 64-bit DSP Processor"; break;
                case 0x4F: ELF_HEADER.machine = "LSI Logic 16-bit DSP Processor"; break;
                case 0x50: ELF_HEADER.machine = "Donald Knuth's educational 64-bit processor"; break;
                case 0x51: ELF_HEADER.machine = "Harvard University machine-independent object files"; break;
                case 0x52: ELF_HEADER.machine = "SiTera Prism"; break;
                case 0x53: ELF_HEADER.machine = "Atmel AVR 8-bit microcontroller"; break;
                case 0x54: ELF_HEADER.machine = "Fujitsu FR30"; break;
                case 0x55: ELF_HEADER.machine = "Mitsubishi D10V"; break;
                case 0x56: ELF_HEADER.machine = "Mitsubishi D30V"; break;
                case 0x57: ELF_HEADER.machine = "NEC v850"; break;
                case 0x58: ELF_HEADER.machine = "Mitsubishi M32R"; break;
                case 0x59: ELF_HEADER.machine = "Matsushita MN10300"; break;
                case 0x5A: ELF_HEADER.machine = "Matsushita MN10200"; break;
                case 0x5B: ELF_HEADER.machine = "picoJava"; break;
                case 0x5C: ELF_HEADER.machine = "OpenRISC 32-bit embedded processor"; break;
                case 0x5D: ELF_HEADER.machine = "ARC Cores Tangent-A5"; break;
                case 0x5E: ELF_HEADER.machine = "Tensilica Xtensa Architecture"; break;
                case 0x5F: ELF_HEADER.machine = "Alphamosaic VideoCore processor"; break;
                case 0x60: ELF_HEADER.machine = "Thompson Multimedia General Purpose Processor"; break;
                case 0x61: ELF_HEADER.machine = "National Semiconductor 32000 series"; break;
                case 0x62: ELF_HEADER.machine = "Tenor Network TPC processor"; break;
                case 0x63: ELF_HEADER.machine = "Trebia SNP 1000 processor"; break;
                case 0x64: ELF_HEADER.machine = "STMicroelectronics (www.st.com) ST200"; break;
                case 0x8C: ELF_HEADER.machine = "TMS320C6000 Family"; break;
                case 0xAF: ELF_HEADER.machine = "MCST Elbrus e2k"; break;
                case 0xF7: ELF_HEADER.machine = "Berkeley Packet Filter"; break;
                default: OUTPUT::Error("Invalid/unknown machine type", 0x01); break;
            }
    }

    // Set version to 1
    ELF_HEADER.version = 1;

    // Get entry point address
    ELF_HEADER.entry = header[0x1B] << 24 | header[0x1A] << 16 | header[0x19] << 8 | header[0x18];

    // Get program header offset, section header offset, flags, basically everything
    if (ELF_HEADER.bits) [[likely]] {
        // 64-bit
        ELF_HEADER.phoff     = header[0x23] << 24 | header[0x22] << 16 | header[0x21] << 8 | header[0x20];
        ELF_HEADER.shoff     = header[0x2B] << 24 | header[0x2A] << 16 | header[0x29] << 8 | header[0x28];
        ELF_HEADER.flags     = header[0x33] << 24 | header[0x32] << 16 | header[0x31] << 8 | header[0x30];
        ELF_HEADER.ehsize    = header[0x35] << 8 | header[0x34];
        ELF_HEADER.phentsize = header[0x37] << 8 | header[0x36];
        ELF_HEADER.phnum     = header[0x39] << 8 | header[0x38];
        ELF_HEADER.shentsize = header[0x3B] << 8 | header[0x3A];
        ELF_HEADER.shnum     = header[0x3D] << 8 | header[0x3C];
        ELF_HEADER.shstrndx  = header[0x3F] << 8 | header[0x3E];
    } else {
        // 32-bit
        ELF_HEADER.phoff    = header[0x1F] << 24 | header[0x1E] << 16 | header[0x1D] << 8 | header[0x1C];
        ELF_HEADER.shoff    = header[0x23] << 24 | header[0x22] << 16 | header[0x21] << 8 | header[0x20];
        ELF_HEADER.flags    = header[0x27] << 24 | header[0x26] << 16 | header[0x25] << 8 | header[0x24]; 
        ELF_HEADER.ehsize    = header[0x29] << 8 | header[0x28];
        ELF_HEADER.phentsize = header[0x2B] << 8 | header[0x2A];
        ELF_HEADER.phnum     = header[0x2D] << 8 | header[0x2C];
        ELF_HEADER.shentsize = header[0x2F] << 8 | header[0x2E];
        ELF_HEADER.shnum     = header[0x31] << 8 | header[0x30];
        ELF_HEADER.shstrndx  = header[0x33] << 8 | header[0x32];
    }
}

[[noreturn]] void ELFHEADER::OutputELF(const uint8_t &option, const std::vector<unsigned char> &header) noexcept {
    GetELFHeader(header);

    switch (option) {
        case 0x00: OutputELFHeader(); break;
        case 0x01: OutputELFProgram(header); break;
        case 0x02: OutputELFSections(); break;
        case 0x03: OutputELFHeader(); OutputELFProgram(header); OutputELFSections(); break; 
    }
    std::exit(0);
}


[[nodiscard]] std::vector<uint8_t> ELFHEADER::GetCode(void) noexcept {
    const std::vector<uint8_t> code = {
        0x8B, 0x15, 0x00, 0x00, 0x00, 0x00,  // mov    edx,DWORD PTR ds:0x0
        0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00,  // mov    ecx,DWORD PTR ds:0x0
        0xBB, 0x01, 0x00, 0x00, 0x00,        // mov    ebx,0x1
        0xB8, 0x04, 0x00, 0x00, 0x00,        // mov    eax,0x4
        0xCD, 0x80,                          // int    0x80
        0xB8, 0x01, 0x00, 0x00, 0x00,        // mov    eax,0x1
        0xCD, 0x80,                          // int    0x80
    };

    const std::vector<uint8_t> code2 = {
        0x8B, 0x15, 0x00, 0x00, 0x00,        // mov    edx,DWORD PTR ds:0x0
        0x8B, 0x0D, 0x00, 0x00, 0x00,        // mov    ecx,DWORD PTR ds:0x0
        0xBB, 0x01, 0x00, 0x00, 0x00,        // mov    ebx,0x1
        0xB8, 0x04, 0x00, 0x00, 0x00,        // mov    eax,0x4
        0xCD, 0x80,                          // int    0x80
        0xB8, 0x01, 0x00, 0x00, 0x00,        // mov    eax,0x1
        0xCD, 0x80,                          // int    0x80
    };

    const std::vector<uint8_t> code3 = {
        0xF8,  // clc
        0xFA,  // cli
        0xFC,  // cld
        0xF9,
        0xFB,
        0xFD
    };

    const std::vector<uint8_t> code4 = {
        0x0E, 0x01, 0x02, 
        0x0E, 0x03, 0x04,
        0x0E, 0x10, 0x10,
    };

    const std::vector<uint8_t> code5 = {
        0x02, 0x02, 0x02,
    };
    return code4;
}

[[nodiscard]] inline bool ELF::CheckELF(const std::string &filename) {
    std::ifstream file{filename, std::ios::binary};
    std::vector<uint8_t> magicvector;

    if (file) {
        file.seekg(0, std::ios::beg);
        magicvector.resize(4);
        file.read((char*)&magicvector[0], magicvector.size());
    } else {
        OUTPUT::Error("This file is not open", 0x0E);
    }
    file.close();

    return (
        (magicvector[0] == 0x7F) &&
        (magicvector[1] == 0x45) &&
        (magicvector[2] == 0x4C) &&
        (magicvector[3] == 0x46)
    );
}



/*
    std::ifstream file{filename, std::ios::binary};
    std::array<uint8_t, 10> arr;

    file.seekg(0, std::ios::beg);
    file.read((char*)&arr[0], arr.size());
*/

[[nodiscard]] std::vector<uint8_t> ELF::FetchHeader(const std::string &filename) {
    std::ifstream file{filename, std::ios::binary};
    std::vector<uint8_t> hexvector;

    if (file) {
        file.seekg(0, std::ios::beg);
        hexvector.resize(500);
        file.read((char*)&hexvector[0], hexvector.size());
    } else {
        OUTPUT::Error("This file is not open", 0x0E);
    }
    file.close();
    return hexvector;
}




void FETCH::Fetch(std::deque<uint8_t> &hexqueue, std::deque<uint8_t> &buffer) {
    for (;buffer.size() != 10;) {
        buffer.push_back(hexqueue[0]);
        hexqueue.pop_front();
    }
}


[[nodiscard]] std::deque<uint8_t> FETCH::MassFetch(const std::string &filename) {
    std::ifstream file{filename, std::ios::binary};
    std::deque<uint8_t> hexdeque{};
    if (file) {
        file.seekg(0, std::ios::end);
        hexdeque.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read((char*)&hexdeque[0], hexdeque.size());
    }
    file.close();
    return hexdeque;
}

FETCH::FETCH() 
{
}

FETCH::~FETCH()
{
}
