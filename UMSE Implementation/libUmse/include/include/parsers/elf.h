#ifndef ELF_H_
#define ELF_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 7000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.7 or later is required"
#endif

class elf_t : public kaitai::kstruct {

public:
    class endian_elf_t;

    enum endian_t {
        ENDIAN_LE = 1,
        ENDIAN_BE = 2
    };

    enum sh_type_t {
        SH_TYPE_NULL_TYPE = 0,
        SH_TYPE_PROGBITS = 1,
        SH_TYPE_SYMTAB = 2,
        SH_TYPE_STRTAB = 3,
        SH_TYPE_RELA = 4,
        SH_TYPE_HASH = 5,
        SH_TYPE_DYNAMIC = 6,
        SH_TYPE_NOTE = 7,
        SH_TYPE_NOBITS = 8,
        SH_TYPE_REL = 9,
        SH_TYPE_SHLIB = 10,
        SH_TYPE_DYNSYM = 11,
        SH_TYPE_INIT_ARRAY = 14,
        SH_TYPE_FINI_ARRAY = 15,
        SH_TYPE_PREINIT_ARRAY = 16,
        SH_TYPE_GROUP = 17,
        SH_TYPE_SYMTAB_SHNDX = 18,
        SH_TYPE_SUNW_CAPCHAIN = 1879048175,
        SH_TYPE_SUNW_CAPINFO = 1879048176,
        SH_TYPE_SUNW_SYMSORT = 1879048177,
        SH_TYPE_SUNW_TLSSORT = 1879048178,
        SH_TYPE_SUNW_LDYNSYM = 1879048179,
        SH_TYPE_SUNW_DOF = 1879048180,
        SH_TYPE_SUNW_CAP = 1879048181,
        SH_TYPE_SUNW_SIGNATURE = 1879048182,
        SH_TYPE_SUNW_ANNOTATE = 1879048183,
        SH_TYPE_SUNW_DEBUGSTR = 1879048184,
        SH_TYPE_SUNW_DEBUG = 1879048185,
        SH_TYPE_SUNW_MOVE = 1879048186,
        SH_TYPE_SUNW_COMDAT = 1879048187,
        SH_TYPE_SUNW_SYMINFO = 1879048188,
        SH_TYPE_SUNW_VERDEF = 1879048189,
        SH_TYPE_SUNW_VERNEED = 1879048190,
        SH_TYPE_SUNW_VERSYM = 1879048191,
        SH_TYPE_SPARC_GOTDATA = 1879048192,
        SH_TYPE_AMD64_UNWIND = 1879048193
    };

    enum os_abi_t {
        OS_ABI_SYSTEM_V = 0,
        OS_ABI_HP_UX = 1,
        OS_ABI_NETBSD = 2,
        OS_ABI_GNU = 3,
        OS_ABI_SOLARIS = 6,
        OS_ABI_AIX = 7,
        OS_ABI_IRIX = 8,
        OS_ABI_FREEBSD = 9,
        OS_ABI_TRU64 = 10,
        OS_ABI_MODESTO = 11,
        OS_ABI_OPENBSD = 12,
        OS_ABI_OPENVMS = 13,
        OS_ABI_NSK = 14,
        OS_ABI_AROS = 15,
        OS_ABI_FENIXOS = 16,
        OS_ABI_CLOUDABI = 17,
        OS_ABI_OPENVOS = 18
    };

    enum machine_t {
        MACHINE_NOT_SET = 0,
        MACHINE_SPARC = 2,
        MACHINE_X86 = 3,
        MACHINE_MIPS = 8,
        MACHINE_POWERPC = 20,
        MACHINE_ARM = 40,
        MACHINE_SUPERH = 42,
        MACHINE_IA_64 = 50,
        MACHINE_X86_64 = 62,
        MACHINE_AARCH64 = 183
    };

    enum bits_t {
        BITS_B32 = 1,
        BITS_B64 = 2
    };

    enum ph_type_t {
        PH_TYPE_NULL_TYPE = 0,
        PH_TYPE_LOAD = 1,
        PH_TYPE_DYNAMIC = 2,
        PH_TYPE_INTERP = 3,
        PH_TYPE_NOTE = 4,
        PH_TYPE_SHLIB = 5,
        PH_TYPE_PHDR = 6,
        PH_TYPE_TLS = 7,
        PH_TYPE_GNU_EH_FRAME = 1685382480,
        PH_TYPE_GNU_STACK = 1685382481,
        PH_TYPE_GNU_RELRO = 1685382482,
        PH_TYPE_PAX_FLAGS = 1694766464,
        PH_TYPE_HIOS = 1879048191
    };

    enum obj_type_t {
        OBJ_TYPE_RELOCATABLE = 1,
        OBJ_TYPE_EXECUTABLE = 2,
        OBJ_TYPE_SHARED = 3,
        OBJ_TYPE_CORE = 4
    };

    elf_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, elf_t* p__root = 0);

private:
    void _read();

public:
    ~elf_t();

    class endian_elf_t : public kaitai::kstruct {

    public:
        class program_header_t;
        class section_header_t;
        class strings_struct_t;

        endian_elf_t(kaitai::kstream* p__io, elf_t* p__parent = 0, elf_t* p__root = 0);

    private:
        int m__is_le;

    public:

    private:
        void _read();

    public:

    private:
        void _read_le();

    public:

    private:
        void _read_be();

    public:
        ~endian_elf_t();

        class program_header_t : public kaitai::kstruct {

        public:

            program_header_t(kaitai::kstream* p__io, elf_t::endian_elf_t* p__parent = 0, elf_t* p__root = 0, int p_is_le = -1);

        private:
            int m__is_le;

        public:

        private:
            void _read();

        public:

        private:
            void _read_le();

        public:

        private:
            void _read_be();

        public:
            ~program_header_t();

        private:
            ph_type_t m_type;
            uint32_t m_flags64;
            bool n_flags64;

        public:
            bool _is_null_flags64() { flags64(); return n_flags64; };

        private:
            uint64_t m_offset;
            bool n_offset;

        public:
            bool _is_null_offset() { offset(); return n_offset; };

        private:
            uint64_t m_vaddr;
            bool n_vaddr;

        public:
            bool _is_null_vaddr() { vaddr(); return n_vaddr; };

        private:
            uint64_t m_paddr;
            bool n_paddr;

        public:
            bool _is_null_paddr() { paddr(); return n_paddr; };

        private:
            uint64_t m_filesz;
            bool n_filesz;

        public:
            bool _is_null_filesz() { filesz(); return n_filesz; };

        private:
            uint64_t m_memsz;
            bool n_memsz;

        public:
            bool _is_null_memsz() { memsz(); return n_memsz; };

        private:
            uint32_t m_flags32;
            bool n_flags32;

        public:
            bool _is_null_flags32() { flags32(); return n_flags32; };

        private:
            uint64_t m_align;
            bool n_align;

        public:
            bool _is_null_align() { align(); return n_align; };

        private:
            elf_t* m__root;
            elf_t::endian_elf_t* m__parent;

        public:
            ph_type_t type() const { return m_type; }
            uint32_t flags64() const { return m_flags64; }
            uint64_t offset() const { return m_offset; }
            uint64_t vaddr() const { return m_vaddr; }
            uint64_t paddr() const { return m_paddr; }
            uint64_t filesz() const { return m_filesz; }
            uint64_t memsz() const { return m_memsz; }
            uint32_t flags32() const { return m_flags32; }
            uint64_t align() const { return m_align; }
            elf_t* _root() const { return m__root; }
            elf_t::endian_elf_t* _parent() const { return m__parent; }
        };

        class section_header_t : public kaitai::kstruct {

        public:

            section_header_t(kaitai::kstream* p__io, elf_t::endian_elf_t* p__parent = 0, elf_t* p__root = 0, int p_is_le = -1);

        private:
            int m__is_le;

        public:

        private:
            void _read();

        public:

        private:
            void _read_le();

        public:

        private:
            void _read_be();

        public:
            ~section_header_t();

        private:
            bool f_body;
            std::string m_body;

        public:
            std::string body();

        private:
            bool f_name;
            std::string m_name;

        public:
            std::string name();

        private:
            uint32_t m_name_offset;
            sh_type_t m_type;
            uint64_t m_flags;
            bool n_flags;

        public:
            bool _is_null_flags() { flags(); return n_flags; };

        private:
            uint64_t m_addr;
            bool n_addr;

        public:
            bool _is_null_addr() { addr(); return n_addr; };

        private:
            uint64_t m_offset;
            bool n_offset;

        public:
            bool _is_null_offset() { offset(); return n_offset; };

        private:
            uint64_t m_size;
            bool n_size;

        public:
            bool _is_null_size() { size(); return n_size; };

        private:
            uint32_t m_linked_section_idx;
            std::string m_info;
            uint64_t m_align;
            bool n_align;

        public:
            bool _is_null_align() { align(); return n_align; };

        private:
            uint64_t m_entry_size;
            bool n_entry_size;

        public:
            bool _is_null_entry_size() { entry_size(); return n_entry_size; };

        private:
            elf_t* m__root;
            elf_t::endian_elf_t* m__parent;

        public:
            uint32_t name_offset() const { return m_name_offset; }
            sh_type_t type() const { return m_type; }
            uint64_t flags() const { return m_flags; }
            uint64_t addr() const { return m_addr; }
            uint64_t offset() const { return m_offset; }
            uint64_t size() const { return m_size; }
            uint32_t linked_section_idx() const { return m_linked_section_idx; }
            std::string info() const { return m_info; }
            uint64_t align() const { return m_align; }
            uint64_t entry_size() const { return m_entry_size; }
            elf_t* _root() const { return m__root; }
            elf_t::endian_elf_t* _parent() const { return m__parent; }
        };

        class strings_struct_t : public kaitai::kstruct {

        public:

            strings_struct_t(kaitai::kstream* p__io, elf_t::endian_elf_t* p__parent = 0, elf_t* p__root = 0, int p_is_le = -1);

        private:
            int m__is_le;

        public:

        private:
            void _read();

        public:

        private:
            void _read_le();

        public:

        private:
            void _read_be();

        public:
            ~strings_struct_t();

        private:
            std::vector<std::string>* m_entries;
            elf_t* m__root;
            elf_t::endian_elf_t* m__parent;

        public:
            std::vector<std::string>* entries() const { return m_entries; }
            elf_t* _root() const { return m__root; }
            elf_t::endian_elf_t* _parent() const { return m__parent; }
        };

    private:
        bool f_program_headers;
        std::vector<program_header_t*>* m_program_headers;

    public:
        std::vector<program_header_t*>* program_headers();

    private:
        bool f_section_headers;
        std::vector<section_header_t*>* m_section_headers;

    public:
        std::vector<section_header_t*>* section_headers();

    private:
        bool f_strings;
        strings_struct_t* m_strings;

    public:
        strings_struct_t* strings();

    private:
        obj_type_t m_e_type;
        machine_t m_machine;
        uint32_t m_e_version;
        uint64_t m_entry_point;
        bool n_entry_point;

    public:
        bool _is_null_entry_point() { entry_point(); return n_entry_point; };

    private:
        uint64_t m_program_header_offset;
        bool n_program_header_offset;

    public:
        bool _is_null_program_header_offset() { program_header_offset(); return n_program_header_offset; };

    private:
        uint64_t m_section_header_offset;
        bool n_section_header_offset;

    public:
        bool _is_null_section_header_offset() { section_header_offset(); return n_section_header_offset; };

    private:
        std::string m_flags;
        uint16_t m_e_ehsize;
        uint16_t m_program_header_entry_size;
        uint16_t m_qty_program_header;
        uint16_t m_section_header_entry_size;
        uint16_t m_qty_section_header;
        uint16_t m_section_names_idx;
        elf_t* m__root;
        elf_t* m__parent;
        std::vector<std::string>* m__raw_program_headers;
        std::vector<kaitai::kstream*>* m__io__raw_program_headers;
        std::vector<std::string>* m__raw_section_headers;
        std::vector<kaitai::kstream*>* m__io__raw_section_headers;
        std::string m__raw_strings;
        kaitai::kstream* m__io__raw_strings;

    public:
        obj_type_t e_type() const { return m_e_type; }
        machine_t machine() const { return m_machine; }
        uint32_t e_version() const { return m_e_version; }
        uint64_t entry_point() const { return m_entry_point; }
        uint64_t program_header_offset() const { return m_program_header_offset; }
        uint64_t section_header_offset() const { return m_section_header_offset; }
        std::string flags() const { return m_flags; }
        uint16_t e_ehsize() const { return m_e_ehsize; }
        uint16_t program_header_entry_size() const { return m_program_header_entry_size; }
        uint16_t qty_program_header() const { return m_qty_program_header; }
        uint16_t section_header_entry_size() const { return m_section_header_entry_size; }
        uint16_t qty_section_header() const { return m_qty_section_header; }
        uint16_t section_names_idx() const { return m_section_names_idx; }
        elf_t* _root() const { return m__root; }
        elf_t* _parent() const { return m__parent; }
        std::vector<std::string>* _raw_program_headers() const { return m__raw_program_headers; }
        std::vector<kaitai::kstream*>* _io__raw_program_headers() const { return m__io__raw_program_headers; }
        std::vector<std::string>* _raw_section_headers() const { return m__raw_section_headers; }
        std::vector<kaitai::kstream*>* _io__raw_section_headers() const { return m__io__raw_section_headers; }
        std::string _raw_strings() const { return m__raw_strings; }
        kaitai::kstream* _io__raw_strings() const { return m__io__raw_strings; }
    };

private:
    std::string m_magic;
    bits_t m_bits;
    endian_t m_endian;
    uint8_t m_ei_version;
    os_abi_t m_abi;
    uint8_t m_abi_version;
    std::string m_pad;
    endian_elf_t* m_header;
    elf_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * File identification, must be 0x7f + "ELF".
     */
    std::string magic() const { return m_magic; }

    /**
     * File class: designates target machine word size (32 or 64
     * bits). The size of many integer fields in this format will
     * depend on this setting.
     */
    bits_t bits() const { return m_bits; }

    /**
     * Endianness used for all integers.
     */
    endian_t endian() const { return m_endian; }

    /**
     * ELF header version.
     */
    uint8_t ei_version() const { return m_ei_version; }

    /**
     * Specifies which OS- and ABI-related extensions will be used
     * in this ELF file.
     */
    os_abi_t abi() const { return m_abi; }

    /**
     * Version of ABI targeted by this ELF file. Interpretation
     * depends on `abi` attribute.
     */
    uint8_t abi_version() const { return m_abi_version; }
    std::string pad() const { return m_pad; }
    endian_elf_t* header() const { return m_header; }
    elf_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // ELF_H_
