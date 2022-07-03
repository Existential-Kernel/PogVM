#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <filesystem>
#include <stdio.h>
#include <ios>
#include <iomanip>
#include <array>
#include <elf.h>  // https://www.man7.org/linux/man-pages/man5/elf.5.html

#include "../defs.hpp"
#include "../cpu/registers.hpp"

#pragma once

class ASSEMBLY {
    private:
        // Macros
        #define WHITESPACE " \n\r\t\f\v"

        static std::string Filter(const std::string &string);
        static std::string Trim(const std::string &string);
        static std::vector<std::string> Split(const std::string &string);
        static std::vector<std::string> Preprocess(std::string &line);

    public:
        // check if string ends with .asm or .s file extension
        [[nodiscard]] static bool CheckASM(const std::string &file);

        // Get the line of assembly
        [[nodiscard]] static std::vector<std::vector<std::string>> FetchAssembly(const std::string &location);
};

class ELF_HEADER_STRUCT {
    public:
        unsigned char e_ident[16];
        bool bits; // true = 64-bit, false = 32-bit
        std::string data;
        std::string type;
        std::string machine;
        bool version;
        uint8_t ABIversion;
        std::string OSABI;

        uint64_t entry;
        uint64_t phoff;
        uint64_t shoff;

        uint32_t flags;
        uint16_t ehsize;
        uint16_t phentsize;
        uint16_t phnum;
        uint16_t shentsize;
        uint16_t shnum;
        uint16_t shstrndx;
} ELF_HEADER;

class ELF_PROGRAM_STRUCT {
    public:
        uint32_t ph_type;
        std::string ph_typename;

        uint32_t ph_flags;
        std::string ph_flagsname;

        uint64_t ph_offset;
        uint64_t ph_vaddr;
        uint64_t ph_paddr;
        uint32_t ph_filesz;
        uint32_t ph_memsz;
        uint32_t ph_align;
} ELF_PROGRAM;

class ELF_SECTION_STRUCT {
    public:
        uint32_t sh_name;
        uint32_t sh_type;
        uint32_t sh_flags;
        uint64_t sh_addr;
        uint64_t sh_offset;
        uint32_t sh_size;
        uint32_t sh_link;
        uint32_t sh_info;
        uint32_t sh_addralign;
        uint32_t sh_entsize;
} ELF_SECTION;

class ELFHEADER : public ELF_HEADER_STRUCT, public ELF_PROGRAM_STRUCT, public ELF_SECTION_STRUCT {
    protected:
        static void GetELFProgram(const std::vector<uint8_t> &hex, const uint64_t &offset);

    private:
        ELF_SECTION_STRUCT *ELFSEC_PTR = &ELF_SECTION;
        ELF_HEADER_STRUCT *ELF_HEADER_PTR = &ELF_HEADER;
        ELF_PROGRAM_STRUCT *ELF_PROGRAM_PTR = &ELF_PROGRAM;

        // Output the ELF header information
        static void OutputELFHeader(void) noexcept;
        static void OutputELFProgram(const std::vector<uint8_t> &header) noexcept;

        static void OutputELFSections(void) {
            /* 
             * TODO: Output ELF sections with their name, type, address,
             * offset, size, entry size, flags, link, info, and align values
             */
        }

        /*
        static void OutputDissassembly(const std::vector<unsigned char> &text) {
            // TODO: create a dissassembler for the ELF text section
        }
        */

    public:
        static void GetELFHeader(const std::vector<uint8_t> &hex) noexcept;

        // Output the ELF information
        [[noreturn]] static void OutputELF(const uint8_t &option, const std::vector<uint8_t> &header) noexcept;

        //static std::vector<uint8_t> GetCode(std::vector<uint8_t> & code) {}
        static std::vector<uint8_t> GetCode(void) noexcept;
};


class ELF : public ELFHEADER {
    public:
        // Check if the file is an ELF file
        static bool CheckELF(const std::string &filename);

        // Get hex data of file and return as vector
        [[nodiscard]] static std::vector<uint8_t> MassFetchHex(const std::string &filename);

        //static std::array<uint8_t, 10> FetchHex(const std::string &filename);
        static void FetchHex(const std::vector<uint8_t> &v, std::array<uint8_t, 10> &a);
};

class FETCH : public ASSEMBLY, public ELF {
    public:
        FETCH();
        ~FETCH();
};