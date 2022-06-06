#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <filesystem>
#include <stdio.h>
#include <ios>
#include <iomanip>
#include <elf.h>  // https://www.man7.org/linux/man-pages/man5/elf.5.html

#include "../defs.hpp"
#include "../cpu/registers.hpp"

#pragma once

class ASSEMBLY {
    private:
        // Macros
        #define WHITESPACE " \n\r\t\f\v"
        typedef std::vector<std::string> svec;                // string vector
        typedef std::vector<std::vector<std::string>> dsvec;  // double string vector

        static std::string Filter(const std::string &string);
        static std::string Trim(const std::string &string);
        static svec Split(const std::string &string);
        static svec Preprocess(std::string &line);

    public:
        // check if string ends with .asm or .s file extension
        static bool CheckASM(const std::string &file);

        // Get the line of assembly
        static dsvec FetchAssembly(const std::string &location) {
            std::fstream file{};
            std::string line{};
            dsvec programvector;

            // Open the file
            file.open((location), std::ios::in);
            if (file.is_open()) [[likely]] {
                while (std::getline(file, line)) {
                    // Prefiltering unnecessary assembly lines
                    if ((int)line[0] == 0) { continue; }
                    if (line[0] == ';') { continue; }
                    if (!std::any_of(std::begin(line), std::end(line), ::isalpha)) { continue; }

                    programvector.push_back(Preprocess(line));
                }
                file.close();
            }
            return programvector;
        }
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
        static void GetELFProgram(const std::vector<unsigned char> &hex, const uint64_t &offset);

    private:
        ELF_SECTION_STRUCT *ELFSEC_PTR = &ELF_SECTION;
        ELF_HEADER_STRUCT *ELF_HEADER_PTR = &ELF_HEADER;
        ELF_PROGRAM_STRUCT *ELF_PROGRAM_PTR = &ELF_PROGRAM;

        // Output the ELF header information
        static void OutputELFHeader(void);
        static void OutputELFProgram(const std::vector<unsigned char> &header);

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
        static void GetELFHeader(const std::vector<unsigned char> &hex);

        // Output the ELF information
        [[noreturn]] static void OutputELF(const uint8_t &option, const std::vector<unsigned char> &header);

        //static std::vector<u_char> GetCode(std::vector<u_char> & code) {}
        static std::vector<uint8_t> GetCode(void);
};


class ELF : public ELFHEADER {
    private:
        // Macros
        typedef std::vector<unsigned char> hvec;   // hex vector
        typedef std::vector<unsigned char> dhvec;  // double hex vector

    public:
        // Check if the file is an ELF file
        inline static bool CheckELF(const std::string &filename);

        // Get hex data of file and return as vector
        static std::vector<unsigned char> FetchHex(const std::string &filename);
};

class FETCH : public ASSEMBLY, public ELF {

};
